# Find more information at ase.vu.nl/docs/framework/glossary/makefiles
.PHONY: clean test install

#
# By modifying ./boot.json you can change the bootspec that is injected by roverd normally, so you can test in isolation. 
#

install:
	@echo "Installing dependencies..."
	@mkdir -p dependencies

	# ─── c-list ───────────────────────────────────────────────────────────────────────
	@if [ ! -d dependencies/c-list ]; then \
		echo "Cloning c-list…"; \
		git clone https://github.com/joelguittet/c-list.git dependencies/c-list; \
	else \
		echo "  c-list already exists – skipping clone && build."; \
	fi
	mkdir -p dependencies/c-list/build; \
	cd dependencies/c-list/build && cmake .. && make install; \

	# ─── c-hashtable ─────────────────────────────────────────────────────────────────
	@if [ ! -d dependencies/c-hashtable ]; then \
		echo "Cloning c-hashtable…"; \
		git clone https://github.com/VU-ASE/c-hashtable.git dependencies/c-hashtable; \
	else \
		echo "  c-hashtable already exists – skipping clone && build."; \
	fi
	mkdir -p dependencies/c-hashtable/build; \
	cd dependencies/c-hashtable/build && cmake .. && make install; \

clean:
	@rm -f main

test: install
	# @echo "Running streams tests..."
	# @gcc -o tests/streams_test_runner \
	# 	unity/src/unity.c \
	# 	tests/streams_test.c \
	# 	./src/*.c ./src/rovercom/outputs/*.c ./src/rovercom/tuning/*.c \
	# 	-lcjson -lzmq -lprotobuf-c -lhashtable -llist \
	# 	-I/usr/include/cjson -I./include -I./unity/src -g
	# @echo "Running streams tests..."
	# @./tests/streams_test_runner

	@echo "Compiling bootinfo tests..."
	@gcc -o tests/bootinfo_test_runner \
		unity/src/unity.c \
		tests/bootinfo_test.c \
		./src/*.c ./src/rovercom/outputs/*.c ./src/rovercom/tuning/*.c \
		-lcjson -lzmq -lprotobuf-c -lhashtable -llist \
		-I/usr/include/cjson -I./include -I./unity/src -g
	@echo "Running bootinfo tests..."
	@./tests/bootinfo_test_runner 1
	@./tests/bootinfo_test_runner 2
	@./tests/bootinfo_test_runner 3
	@./tests/bootinfo_test_runner 4



	# @echo "Compiling configuration tests..."
	# @gcc -o tests/configuration_test_runner \
	# 	unity/src/unity.c \
	# 	tests/configuration_test.c \
	# 	./src/*.c ./src/rovercom/outputs/*.c ./src/rovercom/tuning/*.c \
	# 	-lcjson -lzmq -lprotobuf-c -lhashtable -llist \
	# 	-I/usr/include/cjson -I./include -I./unity/src -g
	# @echo "Running configuration tests..."
	# @./tests/configuration_test_runner


	