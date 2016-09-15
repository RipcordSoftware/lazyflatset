.PHONY: build all clean test

build all clean test:
	cd test/lazyflatset && $(MAKE) $@

