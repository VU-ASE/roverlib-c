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
		mkdir -p dependencies/c-list/build; \
		cd dependencies/c-list/build && cmake .. && make install; \
	else \
		echo "  c-list already exists – skipping clone && build."; \
	fi

	# ─── c-hashtable ─────────────────────────────────────────────────────────────────
	@if [ ! -d dependencies/c-hashtable ]; then \
		echo "Cloning c-hashtable…"; \
		git clone https://github.com/VU-ASE/c-hashtable.git dependencies/c-hashtable; \
		mkdir -p dependencies/c-hashtable/build; \
		cd dependencies/c-hashtable/build && cmake .. && make install; \
	else \
		echo "  c-hashtable already exists – skipping clone && build."; \
	fi

clean:
	@rm -f main

test: install
	@echo "Running bootinfo tests..."
	@gcc -o tests/bootinfo_test_runner \
		unity/src/unity.c \
		tests/bootinfo_test.c \
		./src/*.c ./src/rovercom/outputs/*.c ./src/rovercom/tuning/*.c \
		-lcjson -lzmq -lprotobuf-c -lhashtable -llist \
		-I/usr/include/cjson -I./include -I./unity/src -g
	@./tests/bootinfo_test_runner

	@echo "Running configuration tests..."
	@gcc -o tests/configuration_test_runner \
		unity/src/unity.c \
		tests/configuration_test.c \
		./src/*.c ./src/rovercom/outputs/*.c ./src/rovercom/tuning/*.c \
		-lcjson -lzmq -lprotobuf-c -lhashtable -llist \
		-I/usr/include/cjson -I./include -I./unity/src -g
	@./tests/configuration_test_runner

	@echo "Running streams tests..."
	@gcc -o tests/streams_test_runner \
		unity/src/unity.c \
		tests/streams_test.c \
		./src/*.c ./src/rovercom/outputs/*.c ./src/rovercom/tuning/*.c \
		-lcjson -lzmq -lprotobuf-c -lhashtable -llist \
		-I/usr/include/cjson -I./include -I./unity/src -g
	@./tests/streams_test_runner
	