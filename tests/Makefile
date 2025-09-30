CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow -Wpedantic -Wstrict-aliasing -Wcast-align=strict
INCLUDE=-I ..

USE_IMPLS = USE_CODE_GEN USE_FAT_POINTER USE_VOID


.PHONY: clean run

all: tests run

tests: units fuzz
	@echo All tests compiled. Run with "make run".

units: $(USE_IMPLS)

$(USE_IMPLS):
	@$(CC) $(CFLAGS) $(INCLUDE) -D $@ -D POINT -o $@_POINT.out unified.c ../void.c
	@$(CC) $(CFLAGS) $(INCLUDE) -D $@ -D LONG_DOUBLE -o $@_LONG_DOUBLE.out unified.c ../void.c
	@$(CC) $(CFLAGS) $(INCLUDE) -D $@ -o $@_INT.out unified.c ../void.c

fuzz: fuzz.c
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@.out fuzz.c ../void.c

OUTPUTS = $(wildcard USE*.out)

run: $(OUTPUTS)
	@$(foreach f, $^, ./$(f);)
	@./fuzz.out

benchmark: benchmark.c ../void.c
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@.out benchmark.c ../void.c
	./benchmark.out

clean:
	@rm -rf *.out
