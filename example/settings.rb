#!/usr/bin/ruby
require 'mcbuild'

libs = [
	$com_oreisoft_mcruntime, 
	$com_oreisoft_lemontea
]

$example = MCBuild.new(File.dirname(__FILE__))
	.set_name("exp")
	.set_dependency(libs)


