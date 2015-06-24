build: force_true
	cd test/lazyflatset && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) build

all: force_true
	cd test/lazyflatset && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) all

clean: force_true
	cd test/lazyflatset && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) clean

test: force_true
	cd test/lazyflatset && $(MAKE) $(MFLAGS) $(MAKEOVERRIDES) test

force_true:
	true
