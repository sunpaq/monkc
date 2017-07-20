#!/usr/bin/ruby
require 'mcbuild'

$com_oreisoft_mcruntime = MCBuild.new(__dir__)
	.set_name("monkc")
	.set_headers(["monkc.h"])

