# Makefile in accordance with the docs on git management (to use in combination with meta)
.PHONY: build start clean test

BUILD_DIR=bin/
BINARY_NAME=roverlib

lint:
	@echo "Lint check..."
	@echo "No lint check implemented yet"

build: lint
	@echo "building ${BINARY_NAME}"
	mkdir -p $(BUILD_DIR)
	gcc -I/usr/include/cjson -o $(BUILD_DIR)$(BINARY_NAME) src/main.c -lcjson -L/usr/local/lib -llist -lhashtable

#
# You can specify run arguments and build arguments using runargs and buildargs, like this:
# make start runargs="-debug"
# make start runargs="-debug" buildargs="-verbose"
# make build buildargs="-verbose"
#


clean:
	@echo "Cleaning all targets for ${BINARY_NAME}"
	rm -rf $(BUILD_DIR)

test: lint
	exit 0
