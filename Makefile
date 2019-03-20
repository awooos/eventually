CC := clang

SOURCES := $(wildcard src/*.c)

CINCLUDES := -Ibuild/deps/tinker/include -Iinclude

override CFLAGS += -std=c11 -pedantic-errors \
					-fdiagnostics-show-option -Werror -Weverything \
					-Wno-cast-qual -Wno-missing-prototypes -Wno-vla

all: build/eventually-test

build-deps:
	mkdir -p build/deps/
	cd build/deps; test -d tinker || git clone https://github.com/awooos/tinker.git
	cd build/deps/tinker; git pull

build/eventually-test: $(SOURCES)
	$(MAKE) build-deps
	${CC} ${CFLAGS} ${CINCLUDES} $^ build/deps/tinker/src/main.c test/main.c -o $@

test: build/eventually-test
	./build/eventually-test

clean:
	rm -rf build

.PHONY: all clean test build-deps
