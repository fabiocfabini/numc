# NUMC - A Numerical Computing Library for C

Just like NumPy, but in C. This library is still in development, and is not yet ready for use.

## Goals

- [ ] Create a library that is as easy(as possible) to use as NumPy
- [ ] Make it static or dynamickly linked
- [ ] Basic building blocks
  - [x] Creation of arrays of any shape, type, and size
  - [x] Loading and saving arrays to disk
  - [ ] Basic array manipulation: reshaping, transposing, copying, concatenating, etc.
  - [ ] Indexing and slicing
  - [ ] Basic arithmetic operations: addition, subtraction, multiplication, division, etc.
- [ ] Linear algebra
  - [ ] Matrix multiplication
  - [ ] Matrix inversion
  - [ ] Matrix decomposition
  - [ ] Eigenvalues and eigenvectors
  - [ ] Singular value decomposition
  - [ ] QR decomposition
  - [ ] Cholesky decomposition
  - [ ] LU decomposition
  - [ ] Solving linear systems
  - [ ] Solving eigenvalue problems

More goals will be added as development continues.

## Showcase

As this library is intended to be a NumPy-like library, some of the functionality has been mimicked. Here is an example:

```c
// Create a 2x3x4 array of integers full of zeros
NCarray numc_arr = nc_zeros(NC_INT, 3, 2, 3, 4);

// Print the array
nc_show(numc_arr);

NCarray([[[0, 0, 0, 0],
          [0, 0, 0, 0],
          [0, 0, 0, 0]],

         [[0, 0, 0, 0],
          [0, 0, 0, 0],
          [0, 0, 0, 0]]], type=i32)


// Reshape the array to be 6x4
numc_arr = nc_reshape(numc_arr, 2, 6, 4);

// Print the array
nc_show(numc_arr);

NCarray([[0, 0, 0, 0],
         [0, 0, 0, 0],
         [0, 0, 0, 0],
         [0, 0, 0, 0],
         [0, 0, 0, 0],
         [0, 0, 0, 0]], type=i32)
```

More examples can be found in the `examples` directory. //TODO: Add more examples. None exist yet. :smile:

## Contributing

This library is far from being finished, and your contributions are welcome. Of course, please open an issue first for a discussion.