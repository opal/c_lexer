module CParser
  class Ruby25 < ::Parser::Ruby25
  end
end

Parser.send(:remove_const, :Ruby25)
Parser::Ruby25 = CParser::Ruby25
