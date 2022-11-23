require 'bundler/gem_tasks'
require 'rake/testtask'
require 'rake/extensiontask'

Rake::TestTask.new do |t|
  t.ruby_opts  = ["-rpatch_helper"]
  t.libs       = %w(lib/ test/ vendor/parser/test/ vendor/parser/lib/)
  t.test_files = %w(vendor/parser/test/test_lexer.rb vendor/parser/test/test_parser.rb)
  t.warning    = false
end

Rake::ExtensionTask.new('lexer')

namespace :ruby_parser do
  desc "'rake generate' in the Ruby Parser"
  task :generate do
    sh 'ragel -F1 -R vendor/parser/lib/parser/lexer.rl -o vendor/parser/lib/parser/lexer.rb'
    %w[
      ruby18
      ruby19
      ruby20
      ruby21
      ruby22
      ruby23
      ruby24
      ruby25
      ruby26
      ruby27
      macruby
      rubymotion
    ].each do |version|
      sh "bundle exec racc --superclass=Parser::Base vendor/parser/lib/parser/#{version}.y -o vendor/parser/lib/parser/#{version}.rb --no-line-convert"
    end
  end

  desc "'rake clean' in the Ruby Parser"
  task :clean do
    sh 'cd vendor/parser && bundle exec rake clean'
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

task :clean do
  sh 'rm -rf tmp'
  sh 'rm -f lib/lexer.*'
  sh 'rm -f ext/lexer/lexer.c'
  sh 'cd vendor/parser && rake clean'
end

task generate: ['ruby_parser:generate', 'c_lexer:generate']
task test: [:generate, :compile]
task build: :generate
task default: :test
