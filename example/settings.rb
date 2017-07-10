#!/usr/bin/ruby
require 'mcbuild'

$example = MCBuild.new(__dir__)
	.set_name("exp")
	.set_dependency([
		$com_oreisoft_mcruntime, 
		$com_oreisoft_lemontea])


