require 'bundler/gem_tasks'
require 'rake/testtask'
require 'rake/extensiontask'

# Rake::TestTask.new do |t|
#   t.ruby_opts  = ["-rc_lexer"]
#   t.libs       = %w(test/ lib/ parser/test/ parser/lib/)
#   t.test_files = %w(parser/test/test_lexer.rb parser/test/test_parser.rb)
#   t.warning    = false
# end
task :test do
  sh 'ruby -Ilib -Iparser/lib -Iparser/test -rparser -rc_lexer parser/test/test_lexer.rb'
end

Rake::ExtensionTask.new('lexer')

namespace :ruby_parser do
  desc "'rake generate' in the Ruby Parser"
  task :generate do
    sh 'cd parser && rake generate'
  end

  desc "'rake clean' in the Ruby Parser"
  task :clean do
    sh 'cd parser && rake clean'
  end
end

namespace :c_lexer do
  desc 'Generate lexer.c from lexer.rl'
  task :generate do
    source = 'ext/lexer/lexer.rl'
    target = 'ext/lexer/lexer.c'

    sh "ragel -F1 #{source} -o #{target}"

    # Ragel likes to use int variables where a #define would do
    src = File.read(target)
    src.gsub!(/^static const int (\w+) = (\d+);/, '#define \1 \2')
    File.open(target, 'w') { |f| f.write(src) }
  end
end

task generate: ['ruby_parser:generate', 'c_lexer:generate']

task test: [:generate, :compile]

task :default => [:test]
