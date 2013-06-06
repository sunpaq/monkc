
make:
	#[sudo make install] to install monkc and lemontea
	#[sudo make clean] to clean the monkc and lemontea
	#[make test] to make and run test

install:
	cd ./monkc_core_lib && make && sudo make install
	cd ..
	cd ./lemontea && make && sudo make install
	cd ..
	cd ./monkc_preprocessor && make && sudo make install
	cd ..

test:
	cd ./tests && make && ./exec
	cd ..

clean:
	cd ./monkc_core_lib && sudo make clean
	cd ..
	cd ./lemontea && sudo make clean
	cd ..
	cd ./tests && sudo make clean
	cd ..

	
