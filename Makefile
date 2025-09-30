CC = gcc
CFLAGS = -std=c99 -g -Wall -Wextra -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wrestrict -Wnull-dereference -Wjump-misses-init -Wdouble-promotion -Wshadow -Wpedantic -Wstrict-aliasing -Wcast-align=strict
INCLUDE=-I ..
OUTPUT = a.out

USE_IMPLS = USE_CODE_GEN USE_FAT_POINTER USE_VOID

LD_TYPE = double I "U_POP(A)" "U_GET(I,A)"

define interleave
-D U_TYPE=$(word 1, $(1)) -D "U_MAKE(I)"=$(word 2, $(1)) -D "U_POP_INT(I)"=$(word 3, $(1)) -D "U_GET_INT(I,A)"=$(word 4, $(1))
endef

.PHONY: all run clean

all: $(USE_IMPLS)

$(USE_IMPLS):
	@$(CC) $(CFLAGS) $(INCLUDE) -D $@ $(call interleave, $(LD_TYPE)) -o $@_$(word 1, $(LD_TYPE)).out unified.c void.c
	./$@_$(word 1, $(LD_TYPE)).out
