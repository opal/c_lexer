require 'bundler/gem_tasks'
require 'rake/testtask'

task :default => [:test]

Rake::TestTask.new do |t|
  t.ruby_opts  = ["-r 'version_patch'"]
  t.libs       = %w(test/ lib/ parser/test/ parser/lib/)
  t.test_files = %w(parser/test/test_lexer.rb parser/test/test_parser.rb)
  t.warning    = false
end

task :build => [:generate_release, :changelog]

GENERATED_FILES = %w(parser/lib/parser/lexer.rb
                     parser/lib/parser/ruby25.rb)

CLEAN.include(GENERATED_FILES)

ENCODING_COMMENT = "# -*- encoding:utf-8; warn-indent:false; frozen_string_literal: true  -*-\n"

desc 'Generate the Ragel lexer and Racc parser.'
task :generate => GENERATED_FILES do
  Rake::Task[:ragel_check].invoke
  GENERATED_FILES.each do |filename|
    content = File.read(filename)
    content = ENCODING_COMMENT + content unless content.start_with?(ENCODING_COMMENT)

    File.open(filename, 'w') do |io|
      io.write content
    end
  end
end

task :regenerate => [:clean, :generate]

desc 'Generate the Ragel lexer and Racc parser in release mode.'
task :generate_release => [:clean_env, :regenerate]

task :clean_env do
  ENV.delete 'RACC_DEBUG'
end

task :ragel_check do
  require 'cliver'
  Cliver.assert('ragel', '~> 6.7')
end

rule '.rb' => '.rl' do |t|
  sh "ragel -F1 -R #{t.source} -o #{t.name}"
end

rule '.rb' => '.y' do |t|
  opts = [ "--superclass=Parser::Base",
           t.source,
           "-o", t.name
         ]
  opts << "--no-line-convert" unless ENV['RACC_DEBUG']
  opts << "--debug" if ENV['RACC_DEBUG']

  sh "racc", *opts
end

task :test => [:generate]
