#!/usr/bin/ruby
require 'mcbuild'

require_relative "mcruntime/settings.rb"
require_relative "lemontea/settings.rb"
require_relative "example/settings.rb"

libs = [
	$com_oreisoft_mcruntime, 
	$com_oreisoft_lemontea
]

MCBuild.waitArg('clean') do
	libs.each { |lib|
		lib.clean
	}
	$example.clean
end

MCBuild.waitArg('all') do
	libs.each { |lib|
		lib.info.compile.archive_lib
	}
	$example.info.compile.archive_exe.done
end

MCBuild.waitArg('run') do
	$example.run
end

MCBuild.printArgs(["clean", "all", "run"])
