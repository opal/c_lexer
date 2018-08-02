typedef int stack_state;

define_stack_type(ss_stack, stack_state, 0);

static inline int stack_state_push(stack_state *ss, int bit)
{
  bit = bit ? 1 : 0;
  *ss = (*ss << 1) | bit;
  return bit;
}

static inline int stack_state_pop(stack_state *ss)
{
  int bit = *ss & 1;
  *ss >>= 1;
  return bit;
}

static inline int stack_state_lexpop(stack_state *ss)
{
  *ss = ( (*ss >> 1) | (*ss & 1) );
  return *ss & 1;
}

static inline int stack_state_active(stack_state *ss)
{
  return *ss & 1;
}

static inline void stack_state_clear(stack_state *ss)
{
  *ss = 0;
}

static inline int stack_state_empty_p(stack_state *ss)
{
  return *ss == 0;
}

static inline int stack_state_value(stack_state *ss)
{
  return *ss;
}

static inline void stack_set_value(stack_state *ss, int value)
{
  *ss = value;
}
