static VALUE lexer_push_cmdarg_state(VALUE self, VALUE bit)
{
  INIT_LEXER_STATE(self, state);
  int bitval = RTEST(bit) ? 1 : 0;
  stack_state_push(&state->cmdarg, bitval);
  return Qnil;
}

static VALUE lexer_pop_cmdarg_state(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  stack_state_pop(&state->cmdarg);
  return Qnil;
}

static VALUE lexer_lexpop_cmdarg_state(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  stack_state_lexpop(&state->cmdarg);
  return Qnil;
}

static VALUE lexer_clear_cmdarg_state(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  stack_state_clear(&state->cmdarg);
  return Qnil;
}

static VALUE lexer_cmdarg_state_empty_p(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  return stack_state_empty_p(&state->cmdarg);
}

static VALUE lexer_cmdarg_state_value(VALUE self)
{
  INIT_LEXER_STATE(self, state);
  return INT2NUM(stack_state_value(&state->cmdarg));
}

static VALUE lexer_set_cmdarg_state(VALUE self, VALUE value)
{
  INIT_LEXER_STATE(self, state);
  stack_set_value(&state->cmdarg, NUM2INT(value));
  return Qtrue;
}
