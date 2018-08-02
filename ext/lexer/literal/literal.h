#ifndef LITERAL_H
#define LITERAL_H

#include "literal/type.h"
typedef struct literal literal;
#include "lexer.h"

struct literal {
  struct lexer_state *lexer;
  VALUE buffer;
  long buffer_s;
  long buffer_e;

  int nesting;

  str_type str_type;
  VALUE start_tok;
  int interpolate;

  VALUE start_delim;
  VALUE end_delim;
  VALUE delimiter;

  long heredoc_e;
  long str_s;
  long herebody_s;

  int indent;
  int label_allowed;
  int interp_braces;
  int space_emitted;
  int monolithic;

  int dedent_body;
  int dedent_level;
};

static void literal_init(literal*, lexer_state*, VALUE, VALUE, long, long, int, int, int);
static str_type literal_string_to_str_type(VALUE);
static VALUE literal_str_type_to_string(str_type);
static void literal_set_start_tok_and_interpolate(literal*, str_type);
static VALUE literal_get_start_delim(VALUE);
static VALUE literal_get_end_delim(VALUE);
static int  literal_munge_escape_p(literal*, VALUE);
static int  literal_nest_and_try_closing(literal*, VALUE, long, long, VALUE);
static void literal_emit_start_tok(literal*);
static void literal_start_interp_brace(literal*);
static int  literal_end_interp_brace_and_try_closing(literal*);
static void literal_extend_string(literal*, VALUE, long, long);
static void literal_flush_string(literal*);
static void literal_extend_content(literal*);
static void literal_extend_space(literal*, long, long);
static int  literal_words_p(literal*);
static int literal_regexp_p(literal*);
static int literal_heredoc_p(literal*);
static int literal_squiggly_heredoc_p(literal*);
static int newline_char_p(VALUE);
static void literal_infer_indent_level(literal*, VALUE);
static int next_state_for_literal(literal*);
static void literal_clear_buffer(literal*);

#endif
