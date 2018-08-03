static VALUE lexer_push_cond_state(VALUE self, VALUE bit)
{
  Lexer* lexer = GET_LEXER(self);
  int bitval = RTEST(bit) ? 1 : 0;
  stack_state_push(&lexer->cond, bitval);
  return Qnil;
}

static VALUE lexer_pop_cond_state(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  stack_state_pop(&lexer->cond);
  return Qnil;
}

static VALUE lexer_lexpop_cond_state(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  stack_state_lexpop(&lexer->cond);
  return Qnil;
}

static VALUE lexer_clear_cond_state(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  stack_state_clear(&lexer->cond);
  return Qnil;
}

static VALUE lexer_cond_state_empty_p(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  return stack_state_empty_p(&lexer->cond) ? Qtrue : Qfalse;
}

static VALUE lexer_cond_state_value(VALUE self)
{
  Lexer* lexer = GET_LEXER(self);
  return INT2NUM(stack_state_value(&lexer->cond));
}

static VALUE lexer_set_cond_state(VALUE self, VALUE value)
{
  Lexer* lexer = GET_LEXER(self);
  stack_set_value(&lexer->cond, NUM2INT(value));
  return Qtrue;
}
