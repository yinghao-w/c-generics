# C-Generics

Study on different methods of implementing generic containers in C, specifically dynamic arrays.

All implement the following operations:

- creation
- destruction
- push
- pop
- insertion
- deletion
- retrieval
- length of the array

There is no index bounds checking.

## Current implementation methods:

- void * pointers
- code generation
- template instantiation
- fat pointers (stretchy buffers)

## Implementation methods of popular public libraries

|Library|Method|
|---|---|
|klib|code generation|
|STC|template instantiation|
|CTL|template instantiation|
|stb\_ds|fat pointers|
|CMC|template instantiation|
|DG_dynarr|code generation|
|Collections-C sized|void|
|qlibc|void|
