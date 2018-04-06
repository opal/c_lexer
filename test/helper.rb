# frozen_string_literal: true

require 'tempfile'
require 'minitest/test'

# minitest/autorun must go after SimpleCov to preserve
# correct order of at_exit hooks.
require 'minitest/autorun'

$LOAD_PATH << File.expand_path('../../lib', __FILE__)
require 'parser'
