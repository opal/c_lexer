require 'c_lexer/version'
require 'parser'
require_relative 'lexer'

class Parser::Lexer
  class CmdargProxyStack
    def initialize(lexer)
      @lexer = lexer
    end

    def push(value); @lexer.push_cmdarg_state(value); end
    def pop;         @lexer.pop_cmdarg_state;         end
    def lexpop;      @lexer.lexpop_cmdarg_state;      end
  end

  class CondProxyStack
    def initialize(lexer)
      @lexer = lexer
    end

    def push(value); @lexer.push_cond_state(value); end
    def pop;         @lexer.pop_cond_state;         end
    def lexpop;      @lexer.lexpop_cond_state;      end
  end

  def cmdarg
    @cmdarg ||= CmdargProxyStack.new(self)
  end

  def cond
    @cond ||= CondProxyStack.new(self)
  end
end

module CLexer
  # Your code goes here...
end
