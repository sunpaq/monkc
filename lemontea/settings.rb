#!/usr/bin/ruby
require 'mcbuild'

$com_oreisoft_lemontea = MCBuild.new(__dir__)
	.set_name("lemontea")
	.set_dependency([
		$com_oreisoft_mcruntime])



