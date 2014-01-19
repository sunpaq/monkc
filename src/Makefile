BINPATH 		= /usr/local/bin
RUNTIME_PATH 	= ./monkc_runtime
LEMONTEA_PATH 	= ./lemontea
MCPP_PATH 		= ./monkc_preprocessor
MCBUILD_PATH 	= ./monkc_buildtool
TESTPATH		= ./tests

make:
	#[sudo make install] to install monkc and lemontea
	#[sudo make clean] to clean the monkc and lemontea
	#[make test] to make and run test

install:
	cd $(RUNTIME_PATH) && make && sudo make install
	cd ..
	cd $(LEMONTEA_PATH) && make && sudo make install
	cd ..
	cd $(MCPP_PATH) && make && sudo make install
	cd ..
	cd $(MCBUILD_PATH) && sudo make install
	cd ..
	#install success
	#/usr/local/lib/libmonkc.a
	#/usr/local/lib/liblemontea.a
	#/usr/local/bin/mcpp
	#/usr/local/bin/mcbuild

test:
	cd $(TESTPATH) && make && ./exec
	cd ..

clean:
	cd $(RUNTIME_PATH) && sudo make clean
	cd ..
	cd $(LEMONTEA_PATH) && sudo make clean
	cd ..
	cd $(TESTPATH) && sudo make clean
	cd ..
	cd $(MCPP_PATH) && sudo make clean
	cd ..

	
