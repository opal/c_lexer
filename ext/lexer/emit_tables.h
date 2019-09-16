#define try_mapping(str, token) if (strcmp(value_str, str) == 0) { emit_token(lexer, token, value, start, end); return; }
#define invalid_mapping rb_raise(rb_eArgError, "Invalid punctuation token: %s", value_str);

static void emit_table_PUNCTUATION(Lexer *lexer, VALUE value, long start, long end)
{
  const char *value_str = RSTRING_PTR(value);

  try_mapping("=", tEQL);
  try_mapping("&", tAMPER2);
  try_mapping("|", tPIPE);
  try_mapping("!", tBANG);
  try_mapping("^", tCARET);
  try_mapping("+", tPLUS);
  try_mapping("-", tMINUS);
  try_mapping("*", tSTAR2);
  try_mapping("/", tDIVIDE);
  try_mapping("%", tPERCENT);
  try_mapping("~", tTILDE);
  try_mapping(",", tCOMMA);
  try_mapping(";", tSEMI);
  try_mapping(".", tDOT);
  try_mapping("..", tDOT2);
  try_mapping("...", tDOT3);
  try_mapping("[", tLBRACK2);
  try_mapping("]", tRBRACK);
  try_mapping("(", tLPAREN2);
  try_mapping(")", tRPAREN);
  try_mapping("?", tEH);
  try_mapping(":", tCOLON);
  try_mapping("&&", tANDOP);
  try_mapping("||", tOROP);
  try_mapping("-@", tUMINUS);
  try_mapping("+@", tUPLUS);
  try_mapping("~@", tTILDE);
  try_mapping("**", tPOW);
  try_mapping("->", tLAMBDA);
  try_mapping("=~", tMATCH);
  try_mapping("!~", tNMATCH);
  try_mapping("==", tEQ);
  try_mapping("!=", tNEQ);
  try_mapping(">", tGT);
  try_mapping(">>", tRSHFT);
  try_mapping(">=", tGEQ);
  try_mapping("<", tLT);
  try_mapping("<<", tLSHFT);
  try_mapping("<=", tLEQ);
  try_mapping("=>", tASSOC);
  try_mapping("::", tCOLON2);
  try_mapping("===", tEQQ);
  try_mapping("<=>", tCMP);
  try_mapping("[]", tAREF);
  try_mapping("[]=", tASET);
  try_mapping("{", tLCURLY);
  try_mapping("}", tRCURLY);
  try_mapping("`", tBACK_REF2);
  try_mapping("!@", tBANG);
  try_mapping("&.", tANDDOT);
  try_mapping(".:", tMETHREF);

  invalid_mapping;
}

static void emit_table_PUNCTUATION_BEGIN(Lexer *lexer, VALUE value, long start, long end)
{
  const char *value_str = RSTRING_PTR(value);

  try_mapping("&", tAMPER);
  try_mapping("*", tSTAR);
  try_mapping("**", tDSTAR);
  try_mapping("+", tUPLUS);
  try_mapping("-", tUMINUS);
  try_mapping("::", tCOLON3);
  try_mapping("(", tLPAREN);
  try_mapping("{", tLBRACE);
  try_mapping("[", tLBRACK);

  invalid_mapping;
}

static void emit_table_KEYWORDS(Lexer *lexer, VALUE value, long start, long end)
{
  const char *value_str = RSTRING_PTR(value);

  try_mapping("if", kIF_MOD);
  try_mapping("unless", kUNLESS_MOD);
  try_mapping("while", kWHILE_MOD);
  try_mapping("until", kUNTIL_MOD);
  try_mapping("rescue", kRESCUE_MOD);
  try_mapping("defined?", kDEFINED);
  try_mapping("BEGIN", klBEGIN);
  try_mapping("END", klEND);

  try_mapping("class", kCLASS);
  try_mapping("module", kMODULE);
  try_mapping("def", kDEF);
  try_mapping("undef", kUNDEF);
  try_mapping("begin", kBEGIN);
  try_mapping("end", kEND);
  try_mapping("then", kTHEN);
  try_mapping("elsif", kELSIF);
  try_mapping("else", kELSE);
  try_mapping("ensure", kENSURE);
  try_mapping("case", kCASE);
  try_mapping("when", kWHEN);
  try_mapping("for", kFOR);
  try_mapping("break", kBREAK);
  try_mapping("next", kNEXT);
  try_mapping("redo", kREDO);
  try_mapping("retry", kRETRY);
  try_mapping("in", kIN);
  try_mapping("do", kDO);
  try_mapping("return", kRETURN);
  try_mapping("yield", kYIELD);
  try_mapping("super", kSUPER);
  try_mapping("self", kSELF);
  try_mapping("nil", kNIL);
  try_mapping("true", kTRUE);
  try_mapping("false", kFALSE);
  try_mapping("and", kAND);
  try_mapping("or", kOR);
  try_mapping("not", kNOT);
  try_mapping("alias", kALIAS);
  try_mapping("__FILE__", k__FILE__);
  try_mapping("__LINE__", k__LINE__);
  try_mapping("__ENCODING__", k__ENCODING__);

  invalid_mapping;
}

static void emit_table_KEYWORDS_BEGIN(Lexer *lexer, VALUE value, long start, long end)
{
  const char *value_str = RSTRING_PTR(value);

  try_mapping("if", kIF);
  try_mapping("unless", kUNLESS);
  try_mapping("while", kWHILE);
  try_mapping("until", kUNTIL);
  try_mapping("rescue", kRESCUE);
  try_mapping("defined?", kDEFINED);
  try_mapping("BEGIN", klBEGIN);
  try_mapping("END", klEND);

  try_mapping("class", kCLASS);
  try_mapping("module", kMODULE);
  try_mapping("def", kDEF);
  try_mapping("undef", kUNDEF);
  try_mapping("begin", kBEGIN);
  try_mapping("end", kEND);
  try_mapping("then", kTHEN);
  try_mapping("elsif", kELSIF);
  try_mapping("else", kELSE);
  try_mapping("ensure", kENSURE);
  try_mapping("case", kCASE);
  try_mapping("when", kWHEN);
  try_mapping("for", kFOR);
  try_mapping("break", kBREAK);
  try_mapping("next", kNEXT);
  try_mapping("redo", kREDO);
  try_mapping("retry", kRETRY);
  try_mapping("in", kIN);
  try_mapping("do", kDO);
  try_mapping("return", kRETURN);
  try_mapping("yield", kYIELD);
  try_mapping("super", kSUPER);
  try_mapping("self", kSELF);
  try_mapping("nil", kNIL);
  try_mapping("true", kTRUE);
  try_mapping("false", kFALSE);
  try_mapping("and", kAND);
  try_mapping("or", kOR);
  try_mapping("not", kNOT);
  try_mapping("alias", kALIAS);
  try_mapping("__FILE__", k__FILE__);
  try_mapping("__LINE__", k__LINE__);
  try_mapping("__ENCODING__", k__ENCODING__);

  invalid_mapping;
}
