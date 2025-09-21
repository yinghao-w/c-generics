CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow -Wpedantic -Wstrict-aliasing -Wcast-align=strict
INCLUDE=-I ..
OUTPUT = test.out

tests: tests.c kvec_test.c calc_test.c rand_test.c ../void.c
	$(CC) $(CFLAGS) $(INCLUDE) -o $(OUTPUT) tests.c kvec_test.c calc_test.c rand_test.c	../void.c
	./$(OUTPUT)
