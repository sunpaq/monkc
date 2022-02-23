#!/usr/bin/ruby
require 'mcbuild'

build = MCBuild.new(__dir__).include ['mcruntime', 'lemontea', 'example']

libs = [
	$com_oreisoft_mcruntime, 
	$com_oreisoft_lemontea
]

build.command 'clean' do
	libs.each { |lib|
		lib.clean
	}
	$example.clean
end

build.command 'all' do
	libs.each { |lib|
		lib.set_std("gnu99")
		lib.info.compile.archive_lib
	}
	$example.set_std("gnu99")
	$example.info.compile.archive_exe.done
end

build.command 'run' do
	$example.run
end

build.print ["clean", "all", "run"]
