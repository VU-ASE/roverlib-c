.PHONY: build start clean

#
# This makefile can be used to test and debug the roverlib-c library.
# It bundles the raw source files and header files, so they can be modified
# to test new features or debug existing ones. Make sure to not leave print statements when pushing :)
#
# By modifying ./boot.json you can change the bootspec that is injected by roverd normally, so you can test in isolation. 
#

build: 
	@echo "Building main.c with local source files and debug flags"
	@gcc -o main main.c \
	../src/*.c ../src/rovercom/outputs/*.c ../src/rovercom/tuning/*.c \
	-lcjson -lzmq -lprotobuf-c -lhashtable -llist -I/usr/include/cjson -I../include -g

clean:
	@rm -f main

start: build
	@echo "Starting program with injected bootspec"
	@ASE_SERVICE=$$(cat boot.json) && export ASE_SERVICE && echo "Starting program" && ./main

debug: build
	@echo "Starting program in debug mode with injected bootspec"
	@ASE_SERVICE=$$(cat boot.json) && export ASE_SERVICE && echo "Starting program" && gdb ./main