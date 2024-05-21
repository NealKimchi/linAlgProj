# Linear Algebra Project

This project is a final capstone for my Linear Algebra courses in university. This project will ideally be able to 
perform almost all the operations I learned during my two Linear Algebra courses. The software is currently in C++ becuase
I originally wanted the practice of using pointers, learning C++. Ultimately this project could turn into a website similar
to Wolfram Alpha or Octave. 

## Table of Contents
1. [To-do](##TO-DO)
## TO-DO
- [x] Parse input string -> convert to array
- [x] Create UserMatrix object
    - holds the array (entries)
    - dimensions of the array (m,n)
- [x] Row Reduction Algorithm
    - [x] eliminate nonpivots
    - [ ] row reduced echelon form
- [x] Matrix Multiplication
    - [x] O(n<sup>3</sup>) Algorithm
    - [ ] **Faster algorithms!!**
- [x] Transpose
- [ ] Modularize repo
    - Separate main.cpp into smaller files
    - Create a MakeFile to compile
- [ ] Determinant
- [ ] Inverse of Matrix
- [ ] Eigen
    - [ ] Eigenvalue calculation
    - [ ] Eigenvector/Eigenspace calculation
    - [ ] Complex Eigenvalues??
- [ ] Diagonlization
    - [ ] PDP<sup>-1</sup>
- [ ] Orthogonality
    - [ ] Col Spaces
    - [ ] Null Spaces
    - [ ] Orthogonal projections
    - [ ] Orthogonal matrices
        - [ ] Unitary Matrix
- [ ] Gram-Schmidt
- [ ] Least-Squares
- [ ] Spectral Theorem
- [ ] Singular Value Decomposition
    - [ ] Moore-Penrose psuedo inverse

### 1) Parsing input
The parsing input function is the main driver of the application. The use will input a name, dimensions, and ssv (space separated values). The parser will then read in the string char by char and create the matrix. It checks for negative numbers and decimals as well, and adjusts the input number accordingly. The parser also keeps an index counter going that way it can dynamically produce the 2D matrix with the dimensions already in place. This may cause the algorithm to be slower.


