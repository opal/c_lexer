require 'parser/ruby25'
require 'c_lexer'

module Parser
  dedenter = Lexer::Dedenter

  remove_const(:Lexer)
  Lexer = CLexer
  Lexer::Dedenter = dedenter

  remove_const(:Ruby25)
  Ruby25 = Ruby25WithCLexer
end
