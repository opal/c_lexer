typedef enum {
  SINGLE_QUOTE,      /* ' */
  DOUBLE_QUOTE,      /* " */
  PERCENT_Q,         /* %q */
  BIG_PERCENT_Q,     /* %Q */
  LSHFT_SINGLE_QUOT, /* <<' */
  LSHFT_DOUBLE_QUOT, /* <<" */
  BARE_PERCENT,      /* % */

  PERCENT_W,         /* %w */
  BIG_PERCENT_W,     /* %W */

  PERCENT_I,         /* %i */
  BIG_PERCENT_I,     /* %I */

  SYM_SINGLE_QUOT,   /* :' */
  SYM_DOUBLE_QUOT,   /* :" */
  PERCENT_S,         /* %s */

  SLASH,             /* / for regexp */
  PERCENT_R,         /* %r */

  PERCENT_X,         /* %x for xstr */
  BACKTICK,          /* ` */
  LSHFT_BACKTICK,    /* <<` */

  INVALID
} str_type;

typedef struct literal {
  struct lexer_state *lexer;
  VALUE buffer;
  int buffer_s;
  int buffer_e;

  int nesting;

  str_type str_type;
  VALUE start_tok;
  int interpolate;

  VALUE start_delim;
  VALUE end_delim;
  VALUE delimiter;

  int heredoc_e;
  int str_s;
  int herebody_s;

  int indent;
  int label_allowed;
  int interp_braces;
  int space_emitted;
  int monolithic;

  int dedent_body;
  int dedent_level;
} literal;

define_stack_type(lit_stack, literal, {0});

static void literal_init(literal*, lexer_state*, VALUE, VALUE, int, int, int, int, int);
static str_type literal_string_to_str_type(VALUE);
static VALUE literal_str_type_to_string(str_type);
static void literal_set_start_tok_and_interpolate(literal*, str_type);
static VALUE literal_get_start_delim(VALUE);
static VALUE literal_get_end_delim(VALUE);
static int  literal_munge_escape_p(literal*, VALUE);
static int  literal_nest_and_close(literal*, VALUE, int, int, VALUE);
static void literal_emit_start_tok(literal*);
static void literal_start_interp_brace(literal*);
static int  literal_end_interp_brace_and_close(literal*);
static void literal_extend_string(literal*, VALUE, int, int);
static void literal_flush_string(literal*);
static void literal_extend_content(literal*);
static void literal_extend_space(literal*, int, int);
static int  literal_words_p(literal*);
static void literal_infer_indent_level(literal*, VALUE);

static void literal_init(literal *lit, lexer_state *lexer, VALUE str_type,
                         VALUE delimiter, int str_s, int heredoc_e, int indent,
                         int dedent_body, int label_allowed)
{
  lit->lexer = lexer;
  lit->nesting = 1;
  lit->str_type = literal_string_to_str_type(str_type);

  if (lit->str_type == INVALID) {
    VALUE hash = rb_hash_new();
    rb_hash_aset(hash, ID2SYM(rb_intern("type")), str_type);
    diagnostic(lexer, severity_error, unexpected_percent_str, hash,
               range(lexer, str_s, str_s + 2), empty_array);
  }

  literal_set_start_tok_and_interpolate(lit, lit->str_type);

  lit->str_s = str_s;

  lit->start_delim = literal_get_start_delim(delimiter);
  lit->end_delim   = literal_get_end_delim(delimiter);
  lit->delimiter   = delimiter;

  lit->herebody_s = 0;
  lit->heredoc_e = heredoc_e;
  lit->indent = indent;
  lit->label_allowed = label_allowed;
  lit->dedent_body = dedent_body;
  lit->dedent_level = -1;
  lit->interp_braces = 0;
  lit->space_emitted = 1;
  lit->monolithic = (lit->start_tok == tSTRING_BEG &&
                     (lit->str_type == SINGLE_QUOTE ||
                      lit->str_type == DOUBLE_QUOTE) &&
                     !heredoc_e);

  lit->buffer   = rb_str_new2("");
  rb_funcall(lit->buffer, rb_intern("force_encoding"), 1, lexer->encoding);

  lit->buffer_s = 0;
  lit->buffer_e = 0;

  if (!lit->monolithic) {
    literal_emit_start_tok(lit);
  }
}

static str_type literal_string_to_str_type(VALUE str)
{
  char *p = RSTRING_PTR(str);
  switch (*p) {
  case '%':
    switch (*++p) {
    case 'q':  return PERCENT_Q;
    case 'Q':  return BIG_PERCENT_Q;
    case '\0': return BARE_PERCENT;
    case 'w':  return PERCENT_W;
    case 'W':  return BIG_PERCENT_W;
    case 'i':  return PERCENT_I;
    case 'I':  return BIG_PERCENT_I;
    case 's':  return PERCENT_S;
    case 'r':  return PERCENT_R;
    case 'x':  return PERCENT_X;
    default:   return INVALID;
    }
    break;
  case '"':  return DOUBLE_QUOTE;
  case '\'': return SINGLE_QUOTE;
  case '/':  return SLASH;
  case ':':
    switch (*++p) {
    case '"':  return SYM_DOUBLE_QUOT;
    case '\'': return SYM_SINGLE_QUOT;
    default:   return INVALID;
    }
    break;
  case '`': return BACKTICK;
  case '<':
    if (*++p != '<')
      return INVALID;
    switch (*++p) {
    case '"':  return LSHFT_DOUBLE_QUOT;
    case '\'': return LSHFT_SINGLE_QUOT;
    case '`':  return LSHFT_BACKTICK;
    default:   return INVALID;
    }
  default: return INVALID;
  }
}

static VALUE literal_str_type_to_string(str_type stype)
{
  switch (stype) {
    case SINGLE_QUOTE:      return rb_str_new2("'");
    case DOUBLE_QUOTE:      return rb_str_new2("\"");
    case PERCENT_Q:         return rb_str_new2("%q");
    case BIG_PERCENT_Q:     return rb_str_new2("%Q");
    case LSHFT_SINGLE_QUOT: return rb_str_new2("<<'");
    case LSHFT_DOUBLE_QUOT: return rb_str_new2("<<\"");
    case BARE_PERCENT:      return rb_str_new2("%");
    case PERCENT_W:         return rb_str_new2("%w");
    case BIG_PERCENT_W:     return rb_str_new2("%W");
    case PERCENT_I:         return rb_str_new2("%i");
    case BIG_PERCENT_I:     return rb_str_new2("%I");
    case SYM_SINGLE_QUOT:   return rb_str_new2(":'");
    case SYM_DOUBLE_QUOT:   return rb_str_new2(":\"");
    case PERCENT_S:         return rb_str_new2("%s");
    case SLASH:             return rb_str_new2("/");
    case PERCENT_R:         return rb_str_new2("%r");
    case PERCENT_X:         return rb_str_new2("%x");
    case BACKTICK:          return rb_str_new2("`");
    case LSHFT_BACKTICK:    return rb_str_new2("<<`");
    default:                return Qnil;
  }
}

static void literal_set_start_tok_and_interpolate(literal *lit, str_type stype)
{
  switch(stype) {
  case SINGLE_QUOTE:
  case PERCENT_Q:
  case LSHFT_SINGLE_QUOT:
    lit->start_tok = tSTRING_BEG;
    lit->interpolate = 0;
    break;
  case DOUBLE_QUOTE:
  case BIG_PERCENT_Q:
  case BARE_PERCENT:
  case LSHFT_DOUBLE_QUOT:
    lit->start_tok = tSTRING_BEG;
    lit->interpolate = 1;
    break;
  case PERCENT_W:
    lit->start_tok = tQWORDS_BEG;
    lit->interpolate = 0;
    break;
  case BIG_PERCENT_W:
    lit->start_tok = tWORDS_BEG;
    lit->interpolate = 1;
    break;
  case PERCENT_I:
    lit->start_tok = tQSYMBOLS_BEG;
    lit->interpolate = 0;
    break;
  case BIG_PERCENT_I:
    lit->start_tok = tSYMBOLS_BEG;
    lit->interpolate = 1;
    break;
  case SYM_SINGLE_QUOT:
  case PERCENT_S:
    lit->start_tok = tSYMBEG;
    lit->interpolate = 0;
    break;
  case SYM_DOUBLE_QUOT:
    lit->start_tok = tSYMBEG;
    lit->interpolate = 1;
    break;
  case SLASH:
  case PERCENT_R:
    lit->start_tok = tREGEXP_BEG;
    lit->interpolate = 1;
    break;
  case PERCENT_X:
  case BACKTICK:
  case LSHFT_BACKTICK:
    lit->start_tok = tXSTRING_BEG;
    lit->interpolate = 1;
    break;
  default:
    lit->start_tok = Qnil;
    break;
  }
}

static VALUE literal_get_start_delim(VALUE str)
{
  VALUE end_delim = literal_get_end_delim(str);
  if (end_delim == str)
    return Qnil;
  else
    return str;
}

static VALUE literal_get_end_delim(VALUE str)
{
  char *p = RSTRING_PTR(str);

  switch (*p) {
  case '(': return rb_str_new2(")");
  case '[': return rb_str_new2("]");
  case '{': return rb_str_new2("}");
  case '<': return rb_str_new2(">");
  default:  return str;
  }
}

static int literal_munge_escape_p(literal *lit, VALUE character)
{
  char *p = RSTRING_PTR(character);

  if (literal_words_p(lit) && (*p == ' '  || *p == '\t' || *p == '\n' ||
                               *p == '\r' || *p == '\v' || *p == '\f')) {
    return 1;
  } else if (*p == '\\' ||
             rb_equal(character, lit->start_delim) ||
             rb_equal(character, lit->end_delim)) {
    return 1;
  } else {
    return 0;
  }
}

static int literal_nest_and_close(literal *lit, VALUE delimiter, int ts, int te,
                                  VALUE lookahead)
{
  if (lit->start_delim != Qnil && rb_equal(lit->start_delim, delimiter)) {
    lit->nesting += 1;
  } else if (lit->indent && rb_equal(lit->end_delim, rb_funcall(delimiter, rb_intern("lstrip"), 0))) {
    lit->nesting -= 1;
  } else if (!lit->indent && rb_equal(lit->end_delim, delimiter)) {
    lit->nesting -= 1;
  }

  if (lit->nesting == 0) {
    if (literal_words_p(lit)) {
      literal_extend_space(lit, ts, ts);
    }

    int quoted_label = 0;

    if (lookahead != Qnil) {
      char *p = RSTRING_PTR(lookahead);
      if (p[0] == ':' && p[1] != ':' && lit->label_allowed && lit->start_tok == tSTRING_BEG)
        quoted_label = 1;
    }

    if (quoted_label) {
      literal_flush_string(lit);
      emit_token(lit->lexer, tLABEL_END, lit->end_delim, ts, te + 1);
    } else if (lit->monolithic) {
      emit_token(lit->lexer, tSTRING, lit->buffer, lit->str_s, te);
    } else {
      if (!lit->heredoc_e) {
        literal_flush_string(lit);
      }
      emit_token(lit->lexer, tSTRING_END, lit->end_delim, ts, te);
    }
    return 1;
  } else {
    return 0;
  }
}

static void literal_emit_start_tok(literal *lit)
{
  VALUE str_type = literal_str_type_to_string(lit->str_type);

  if (*RSTRING_PTR(str_type) == '%')
    rb_str_concat(str_type, lit->delimiter);

  int str_e = lit->heredoc_e;
  if (str_e == 0)
    str_e = lit->str_s + NUM2INT(rb_str_length(str_type));

  emit_token(lit->lexer, lit->start_tok, str_type, lit->str_s, str_e);
}

static void literal_start_interp_brace(literal *lit)
{
  lit->interp_braces += 1;
}

static int literal_end_interp_brace_and_close(literal *lit)
{
  return --lit->interp_braces == 0;
}

static void literal_extend_string(literal *lit, VALUE str, int ts, int te)
{
  if (!lit->buffer_s)
    lit->buffer_s = ts;

  lit->buffer_e = te;
  rb_str_concat(lit->buffer, str);
}

static void literal_flush_string(literal *lit)
{
  if (lit->monolithic) {
    literal_emit_start_tok(lit);
    lit->monolithic = 0;
  }

  if (RSTRING_LEN(lit->buffer) > 0) {
    emit_token(lit->lexer, tSTRING_CONTENT, lit->buffer, lit->buffer_s, lit->buffer_e);
    lit->buffer = rb_str_new2("");
    lit->buffer_s = 0;
    lit->buffer_e = 0;
    lit->space_emitted = 0;
  }
}

static void literal_extend_content(literal *lit)
{
  lit->space_emitted = 0;
}

static void literal_extend_space(literal *lit, int ts, int te)
{
  literal_flush_string(lit);

  if (!lit->space_emitted) {
    emit_token(lit->lexer, tSPACE, Qnil, ts, te);
    lit->space_emitted = 1;
  }
}

static int literal_words_p(literal *lit)
{
  return lit->start_tok == tWORDS_BEG   || lit->start_tok == tQWORDS_BEG ||
         lit->start_tok == tSYMBOLS_BEG || lit->start_tok == tQSYMBOLS_BEG;
}

static void literal_infer_indent_level(literal *lit, VALUE line)
{
  if (!lit->dedent_body)
    return;

  char *p = RSTRING_PTR(line);
  int indent_level = 0;

  while (*p) {
    if (*p == ' ') {
      indent_level += 1;
    } else if (*p == '\t') {
      indent_level += (8 - (indent_level % 8));
    } else {
      if (lit->dedent_level == -1 || lit->dedent_level > indent_level)
        lit->dedent_level = indent_level;
      break;
    }
    p++;
  }
}

