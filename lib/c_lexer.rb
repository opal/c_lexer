require 'c_lexer/version'
require 'parser'

dedenter = Parser::Lexer::Dedenter
Parser.send(:remove_const, :Lexer)

puts "Using C lexer"

require_relative 'lexer'

class Parser::Lexer
  class CmdargProxyStack
    def initialize(lexer)
      @lexer = lexer
      @value = nil
    end

    def push(value); @lexer.push_cmdarg_state(value); end
    def pop;         @lexer.pop_cmdarg_state;         end
    def lexpop;      @lexer.lexpop_cmdarg_state;      end
    def clear;       @lexer.clear_cmdarg_state;       end
    def empty?;      @lexer.cmdarg_state_empty?;      end
    def value;       @value || @lexer.cmdarg_state_value;       end
    def initialize_copy(original)
      @value = original.value
    end

    def to_s
      "[#{value.to_s(2)} <= cmdarg]"
    end
  end

  class CondProxyStack
    def initialize(lexer)
      @lexer = lexer
      @value = nil
    end

    def push(value); @lexer.push_cond_state(value); end
    def pop;         @lexer.pop_cond_state;         end
    def lexpop;      @lexer.lexpop_cond_state;      end
    def clear;       @lexer.clear_cond_state;       end
    def empty?;      @lexer.cond_state_empty?;      end
    def value;       @value || @lexer.cond_state_value;       end
    def initialize_copy(original)
      @value = original.value
    end

    def to_s
      "[#{value.to_s(2)} <= cond]"
    end
  end

  def cmdarg
    @cmdarg ||= CmdargProxyStack.new(self)
  end

  def cond
    @cond ||= CondProxyStack.new(self)
  end

  def cmdarg=(cmdarg)
    set_cmdarg_state(cmdarg.value)
    @cmdarg = nil
  end

  def cond=(cond)
    set_cond_state(cond.value)
    @cond = nil
  end
end

Parser::Lexer.const_set(:Dedenter, dedenter)

module CLexer
end
