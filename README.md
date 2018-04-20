# CLexer

[![Build Status](https://travis-ci.org/opal/c_lexer.svg?branch=master)](https://travis-ci.org/opal/c_lexer)
[![Build status](https://ci.appveyor.com/api/projects/status/lqw4pid44jvfbnl3/branch/master?svg=true)](https://ci.appveyor.com/project/iliabylich/c-lexer/branch/master)

A C port of the whitequark/parser's lexer.

Initially based on [whitequark/parser#248](https://github.com/whitequark/parser/pull/248) (thanks [@alexdowad](https://github.com/alexdowad)).

Can be use on Linux/Mac/Windows, requires MRI.

## Installation

```
$ gem install c_lexer
```

## Usage

`c_lexer` doesn't change any parser classes.

It provides 2 classes:
+ `Parser::CLexer` (C version of the lexer)
+ `Parser::Ruby25WithCLexer` (a subclass of `parser/ruby25` that uses `Parser::CLexer` for lexing)

If you want `CLexer` to be a default lexer you can use the following patch:

``` ruby
require 'parser'
require 'c_lexer'

module Parser
  dedenter = Lexer::Dedenter

  remove_const(:Lexer)
  Lexer = CLexer
  Lexer::Dedenter = dedenter
end
```

## Versioning

`c_lexer` follows versioning of the `parser` gem to avoid confusions like
"which version of `c_lexer` should be used with the `parser vX.Y.Z`". For `parser 2.5.1.0` you should use `c_lexer 2.5.1.0`.

`c_lexer` supports all versions of `parser` starting from `2.5.1.0`

## Development

1. Make sure that you have `ragel` installed.
2. Clone the repo and fetch submodules with `git submodule update --init`.
3. The parser gem is located under `vendor/parser`.
4. `rake ruby_parser:generate` generates `lexer.rb` and parsers for the `parser` gem.
5. `rake c_lexer:generate` generates `lexer.c`.
6. `rake compile` compiles `lexer.c` to `lexer.so` (or `lexer.bundle` depending on your platform).
7. `rake test` runs `parser` tests using `c_lexer` as a default lexer.

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/opal/c_lexer.

Before submitting a bug report, please, make sure that `parser` is not affected by the same issue.
If it's a parser bug please report it to the parser repo and we will backport it afterwards.
