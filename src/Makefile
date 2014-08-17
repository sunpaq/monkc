BINPATH 	= /usr/local/bin
RUNTIME_PATH 	= ./monkc_runtime
LEMONTEA_PATH 	= ./lemontea
GEMONTEA_PATH 	= ./lemontea_GUI
MCPP_PATH 	= ./monkc_preprocessor
MCBUILD_PATH 	= ./monkc_buildtool
TESTPATH	= ./tests
XCODEPATH       = ../XcodeMonkC
EXAMPLEPATH     = ../examples

OS=$(strip $(shell uname -s))
MAKE = make
ifeq ($(OS),FreeBSD)
	MAKE = gmake
endif

info:
	#[sudo make install] to install monkc and lemontea
	#[sudo make clean] to clean the monkc and lemontea
	#[sudo make sync] to copy xcode project files to src
	#[make test] to make and run test

install: clean
	cd $(RUNTIME_PATH) && $(MAKE) && $(MAKE) install
	cd ..
	cd $(LEMONTEA_PATH) && $(MAKE) && $(MAKE) install
	cd ..
	cd $(MCPP_PATH) && $(MAKE) && $(MAKE) install
	cd ..
	cd $(MCBUILD_PATH) && $(MAKE) install
	cd ..
	#install success
	#/usr/local/lib/libmonkc.a
	#/usr/local/lib/liblemontea.a
	#/usr/local/bin/mcpp
	#/usr/local/bin/mcbuild

clean:
	cd $(RUNTIME_PATH) && $(MAKE) clean
	cd ..
	cd $(LEMONTEA_PATH) && $(MAKE) clean
	cd ..
	cd $(GEMONTEA_PATH) && $(MAKE) clean
	cd ..
	cd $(TESTPATH) && $(MAKE) clean
	cd ..
	cd $(MCPP_PATH) && $(MAKE) clean
	cd ..

syncFromXcode:
	cp -r $(XCODEPATH)/MonkC/src/* $(RUNTIME_PATH)
	cp $(XCODEPATH)/Lemontea/src/* $(LEMONTEA_PATH)
	rm -fr $(EXAMPLEPATH)/src
	mkdir -p $(EXAMPLEPATH)/src
	cp -r $(XCODEPATH)/Example/src/* $(EXAMPLEPATH)/src

test:
	cd $(TESTPATH) && $(MAKE) && ./exec
	cd ..



	
