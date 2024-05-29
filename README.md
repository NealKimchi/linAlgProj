# Linear Algebra Project

This project is a final capstone for my Linear Algebra courses in university. This project will ideally be able to 
perform almost all the operations I learned during my two Linear Algebra courses. The software is currently in C++ becuase
I originally wanted the practice of using pointers, learning C++. Ultimately this project could turn into a website similar
to Wolfram Alpha or Octave. 

## Table of Contents
## TO-DO
- [x] Parse input string -> convert to array
- [x] Create UserMatrix object
    - holds the array (entries)
    - dimensions of the array (m,n)
- [x] Row Reduction Algorithm
    - [x] eliminate nonpivots
    - [ ] row reduced echelon form
    - **Test cases**
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

### 1. Parsing input
The parsing input function is the main driver of the application. The user will input a name, dimensions, and ssv (space separated values). The parser will then read in the string char by char and create the matrix. It checks for negative numbers and decimals as well, and adjusts the input number accordingly. The parser also keeps an index counter going that way it can dynamically produce the 2D matrix with the dimensions already in place. This may cause the algorithm to be slower.

### 2. UserMatrix object
The UserMatrix object is one of the few user defined objects in this library. It hold three simple values, a 2D-array holding the entries of the matrix, a int for the m dimension and an int for the n dimension. This object is held within a matrices map, which stores the object with a user defined key.

Some of the functions that can be applied to a UserMatrix object include:
- getter for entries, m, n
- setter for entries, m, n
- print matrix, column, row, entry
- free matrix

### 3. Row Reduction Algorithm
The algorithm I constructe works off of one simple property. Computers are much better at doing math than we are. Therefore we have no issue with dividing a multiplying prime numbers in order to row reduce. The algorithm iterates through the columns and then rows. If the index it is looking at is a pivot column it'll divide the row by itself, and then reduce all the rows below it by pivotRow  the value under pivot index. 

**Helper Functions**
- scale -- Scales a row by given number
- swapRow -- Swaps two rows within the matrix
- eliminateNonPivots -- The loop that goes through every row under the pivot and eliminates the value.

### 4. Matrix Multiplication
The matrix multiplication algorithm currently implemented is the basic O(n<sup>3</sup>) algorithm where the matrices are indexed through in the opposite order, where we iterate through one column and one row, and add the results to ann accumulating variable which eventually becomes the new value at that given row,column index. This new matrix is saved in a new (key,value) pair in the matrices dictionary.

### 5. Transpose
The transpose function takes in a matrix and produces its transpose. This will be useful further in the program when there are more complicated computations to be made. To accoplish this, the algorithm runs through the indeces of the matrix row then column wise and assigns the inverted index to the new matrix.
