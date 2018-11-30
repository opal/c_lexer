lib = File.expand_path('../lib', __FILE__)
$LOAD_PATH.unshift(lib) unless $LOAD_PATH.include?(lib)
require 'c_lexer/version'

Gem::Specification.new do |spec|
  spec.name          = 'c_lexer'
  spec.version       = CLexer::VERSION
  spec.authors       = ['Ilya Bylich']
  spec.email         = ['ibylich@gmail.com']

  spec.description   = %q{A Ruby parser written in C}
  spec.summary       = spec.description
  spec.homepage      = 'https://github.com/iliabylich/c_lexer'

  spec.files         = `git ls-files`.split.reject do |f|
    f.match(%r{^(test|spec|features|vendor)/})
  end + ['ext/lexer/lexer.c']

  spec.bindir        = 'exe'
  spec.executables   = spec.files.grep(%r{^exe/}) { |f| File.basename(f) }
  spec.require_paths = ['lib']
  spec.extensions    = ['ext/lexer/extconf.rb']

  spec.add_dependency             'ast',           '~> 2.4.0'
  spec.add_dependency             'parser',        '= 2.5.3.0'

  spec.add_development_dependency 'bundler',       '~> 1.16'
  spec.add_development_dependency 'rake',          '~> 10.0'
  spec.add_development_dependency 'rake-compiler', '~> 0.9'

  # Parser dev dependencies
  spec.add_development_dependency 'minitest',      '~> 5.10'
  spec.add_development_dependency 'simplecov',     '~> 0.15.1'
  spec.add_development_dependency 'racc',          '= 1.4.14'
  spec.add_development_dependency 'cliver',        '~> 0.3.2'
end
