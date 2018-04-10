require 'bundler/gem_tasks'
require 'rake/testtask'
require 'rake/extensiontask'

Rake::TestTask.new do |t|
  t.ruby_opts  = ["-rc_parser"]
  t.libs       = %w(test/ lib/ parser/test/ parser/lib/)
  t.test_files = %w(parser/test/test_lexer.rb parser/test/test_parser.rb)
  t.warning    = false
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

namespace :c_parser do
  desc 'Generate lexer.c from lexer.rl'
  task :generate do
    sh 'ragel -F1 ext/lexer/lexer.rl -o ext/lexer/lexer.c'
  end
end

task test: ['ruby_parser:generate', 'c_parser:generate', :compile]

task :default => [:test]
