#!/usr/bin/ruby
require 'mcbuild'

libs = [
	$com_oreisoft_mcruntime
]

$com_oreisoft_lemontea = MCBuild.new(File.dirname(__FILE__))
	.set_name("lemontea")
	.set_dependency(libs)



