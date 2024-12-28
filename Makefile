# Makefile to be compliant with the test github action
.PHONY: test

test: lint
	@echo "No tests to run"
	@exit 0
