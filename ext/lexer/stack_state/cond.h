static VALUE lexer_push_cond_state(VALUE self, VALUE bit)
{
  INIT_LEXER_STATE(self, state);
  int bitval = RTEST(bit) ? 1 : 0;
  stack_state_push(&state->cond, bitval);
  return Qnil;
}

static VALUE lexer_pop_cond_state(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  stack_state_pop(&state->cond);
  return Qnil;
}

static VALUE lexer_lexpop_cond_state(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  stack_state_lexpop(&state->cond);
  return Qnil;
}

static VALUE lexer_clear_cond_state(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  stack_state_clear(&state->cond);
  return Qnil;
}

static VALUE lexer_cond_state_empty_p(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  return stack_state_empty_p(&state->cond) ? Qtrue : Qfalse;
}

static VALUE lexer_cond_state_value(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  return INT2NUM(stack_state_value(&state->cond));
}

static VALUE lexer_set_cond_state(VALUE self, VALUE value)
{
  INIT_LEXER_STATE(self, state);
  stack_set_value(&state->cond, NUM2INT(value));
  return Qtrue;
}
