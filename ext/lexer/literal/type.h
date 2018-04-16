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
