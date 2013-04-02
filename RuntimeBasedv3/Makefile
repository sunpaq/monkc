

all:
	#sudo make clean
	#sudo make install
	#make run
	#make test
	#make dump

install:
	cd ./monkc_core_lib && make clean && make && sudo make install
	cd ..
	cd ./lemontea && make clean && make && sudo make install
	cd ..

clean:
	cd ./monkc_core_lib && make clean
	cd ..
	cd ./lemontea && make clean
	cd ..
	cd ./examples && make clean
	cd ..
	cd ./tests && make clean
	cd ..

run:
	cd ./examples && make clean && make && ./exec
	cd ..

test:
	cd ./tests && make clean && make && ./exec
	cd ..

dump:
	#please type follow commands
	#to enable core dump on linux:
	#
	#ulimit -c unlimited