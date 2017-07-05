#!/usr/bin/ruby
require 'mcbuild'

$com_oreisoft_mcruntime = MCBuild.new(File.dirname(__FILE__))
	.set_name("monkc")
	.set_headers(["monkc.h"])
	.set_excludes(["MCNonLock.S"])

