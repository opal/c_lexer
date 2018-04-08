require 'bundler/gem_tasks'
require 'rake/testtask'
require 'rake/extensiontask'

task :default => [:test]

Rake::TestTask.new do |t|
  t.ruby_opts  = ["-rc_parser"]
  t.libs       = %w(test/ lib/ parser/test/ parser/lib/)
  t.test_files = %w(parser/test/test_lexer.rb parser/test/test_parser.rb)
  t.warning    = false
end

Rake::ExtensionTask.new 'lexer' do |ext|
  ext.lib_dir = 'lib/c_parser'
end
task :compile => 'ext/lexer/lexer.c'

desc "'rake generate' in the Ruby Parser"
task :generate do
  `cd parser && rake generate`
end

desc "'rake clean' in the Ruby Parser"
task :clean do
  `cd parser && rake clean`
end

task :test => [:generate]
