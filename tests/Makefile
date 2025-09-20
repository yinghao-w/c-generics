CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow 
INCLUDE=-I ..

tests: tests.c kvec_test.c calc_test.c rand_test.c
	$(CC) $(CFLAGS) $(INCLUDE) tests.c kvec_test.c calc_test.c rand_test.c
