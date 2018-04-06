require 'ast'
require 'parse_helper'
require 'parser/all'
require 'c_parser/ruby25'

C_VERSIONS = %w(2.5)

ParseHelper::ALL_VERSIONS.select! { |version| C_VERSIONS.include?(version) }
