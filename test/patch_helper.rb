require 'parser/ruby25'
require 'parser/ruby26'
require 'c_lexer'

module Parser
  dedenter = Lexer::Dedenter
  max_numparam_stack = Lexer::MaxNumparamStack

  remove_const(:Lexer)
  Lexer = CLexer
  Lexer::Dedenter = dedenter
  Lexer::MaxNumparamStack = max_numparam_stack

  remove_const(:Ruby25)
  Ruby25 = Ruby25WithCLexer

  remove_const(:Ruby26)
  Ruby26 = Ruby26WithCLexer

  remove_const(:Ruby27)
  Ruby27 = Ruby27WithCLexer
end
