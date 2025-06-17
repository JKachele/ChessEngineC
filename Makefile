######################################################################
# @author      : Justin Kachele (justin@kachele.com)
# @file        : Makefile
# @created     : Thursday Jan 16, 2025 08:38:50 EST
######################################################################

CC = gcc
CFLAGS = -std=c11 -g
CFLAGS += -Wall -Wextra -Wpedantic 
CFLAGS += -Wno-unused-parameter -Wno-unused-variable
CFLAGS += -Ilib/cglm/include -Ilib/glad/include -Ilib/glfw/include -Ilib/stb
LDFLAGS = lib/glad/src/glad.o lib/glfw/src/libglfw3.a
LDFLAGS += lib/cglm/libcglm.a -lm -g

SRC = $(wildcard src/*.c) $(wildcard src/**/*.c)
OBJ = $(SRC:.c=.o)
BIN = bin

TEST = test/test.c

.PHONY: build dirs clean cleanAll run runTest

build: dirs libs out

libs:
	cd lib/glfw && cmake . && make
	cd lib/cglm && cmake . -DCGLM_STATIC=ON && make
	cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c

dirs:
	mkdir -p ./$(BIN)

run: build
	$(BIN)/out

out: $(OBJ)
	$(CC) -o $(BIN)/out $^ $(LDFLAGS)
	rm $(OBJ)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

runTest: test
	$(BIN)/test

test: dirs
	$(CC) -o $(BIN)/test $(TEST) -lm -g

clean:
	rm -rf bin/

cleanAll:
	rm -rf bin/
	rm $(OBJ)

