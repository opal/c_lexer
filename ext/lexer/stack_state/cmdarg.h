static VALUE lexer_push_cmdarg_state(VALUE self, VALUE bit)
{
  Lexer* lexer = GET_LEXER(self);
  int bitval = RTEST(bit) ? 1 : 0;
  stack_state_push(&lexer->cmdarg, bitval);
  return Qnil;
}

static VALUE lexer_pop_cmdarg_state(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  stack_state_pop(&lexer->cmdarg);
  return Qnil;
}

static VALUE lexer_lexpop_cmdarg_state(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  stack_state_lexpop(&lexer->cmdarg);
  return Qnil;
}

static VALUE lexer_clear_cmdarg_state(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  stack_state_clear(&lexer->cmdarg);
  return Qnil;
}

static VALUE lexer_cmdarg_state_empty_p(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  return stack_state_empty_p(&lexer->cmdarg) ? Qtrue : Qfalse;
}

static VALUE lexer_cmdarg_state_value(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  return INT2NUM(stack_state_value(&lexer->cmdarg));
}

static VALUE lexer_set_cmdarg_state(VALUE self, VALUE value)
{
  Lexer* lexer = GET_LEXER(self);
  stack_set_value(&lexer->cmdarg, NUM2INT(value));
  return Qtrue;
}
