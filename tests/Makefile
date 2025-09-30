CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow -Wpedantic -Wstrict-aliasing -Wcast-align=strict
INCLUDE = -I ..
BENCH_INC = -I ../../stb -I ../../klib

USE_IMPLS = USE_CODE_GEN USE_FAT_POINTER USE_VOID


.PHONY: clean run

all: tests run

tests: units rand
	@echo All tests compiled. Run with "make run".

units: $(USE_IMPLS)

$(USE_IMPLS):
	@$(CC) $(CFLAGS) $(INCLUDE) -D $@ -D POINT -o $@_POINT.out unit_tests.c ../void.c
	@$(CC) $(CFLAGS) $(INCLUDE) -D $@ -D LONG_DOUBLE -o $@_LONG_DOUBLE.out unit_tests.c ../void.c
	@$(CC) $(CFLAGS) $(INCLUDE) -D $@ -o $@_INT.out unit_tests.c ../void.c

rand: rand_test.c
	@$(CC) $(CFLAGS) $(INCLUDE) -o $@_test.out rand_test.c ../void.c

OUTPUTS = $(wildcard USE*.out)

run: $(OUTPUTS)
	@$(foreach f, $^, ./$(f);)
	@./rand_test.out

benchmark: benchmark.c ../void.c
	@$(CC) $(CFLAGS) $(INCLUDE) $(BENCH_INC) -o $@.out benchmark.c ../void.c
	./benchmark.out

clean:
	@rm -rf *.out
