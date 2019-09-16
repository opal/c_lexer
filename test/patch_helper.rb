require 'parser/ruby25'
require 'parser/ruby26'
require 'c_lexer'

module Parser
  dedenter = Lexer::Dedenter

  remove_const(:Lexer)
  Lexer = CLexer
  Lexer::Dedenter = dedenter

  remove_const(:Ruby25)
  Ruby25 = Ruby25WithCLexer

  remove_const(:Ruby26)
  Ruby26 = Ruby26WithCLexer

  remove_const(:Ruby27)
  Ruby27 = Ruby26WithCLexer
end
