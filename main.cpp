#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <cmath>
using namespace std;


void print_matrix(float** matrix,int m,int n){
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void print_col(float** matrix, int m, int n){
    cout << '[';
    for (int i = 0; i < m; ++i) {
        if(i == m-1){
            cout << matrix[i][n];
            break;
        }
        cout << matrix[i][n] << ", ";
    }
    cout << ']' << endl;
}

void print_row(float** matrix, int m, int n){
    cout << '[';
    for (int i = 0; i < n; ++i) {
        if(i == n-1){
            cout << matrix[m][i];
            break;
        }
        cout << matrix[m][i] << ", ";
    }
    cout << ']' << endl;
}

void print_entry(float** matrix, int m, int n){
    cout << matrix[m][n] << endl;
}

void free_matrix(float** matrix, int m) {
    // Free each row first
    for (int i = 0; i < m; i++) {
        delete[] matrix[i];
    }
    // Free the array of pointers
    delete[] matrix;
}

float** parse_input(string in, int m, int n){
/**
 * This function will be called to read user input for a matrix/vector
    Would like user input to look as such:
        MATRIX (3x3 example):
        enter rows: 3
        enter cols: 3
        enter matrix: x = 1 2 3 4 5 6 7 8 9
    Also asks user for name for the matrix, which is used as a key value pair
    in a dictionary.
*/  
    int length = in.length();
    float** matrix = new float*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new float[n];
    }

    int index = 0, rindex = 0, cindex = 0, decVal = 1, isDec = 0; 
    float decAcc = 0, acc = 0;
    
    for(int i = 0; i < length; i++){
        if(isdigit(in[i]) || in[i] == '.'){   
            if(in[i] == '.'){
                isDec = 1;
            }
            if(isDec && in[i] != '.'){
                float digit = (in[i] - '0') / pow(10, decVal);
                decAcc = decAcc + digit;
                decVal++;
            }                     
            if(in[i] != '.' && !isDec){
                acc = (acc * 10) + (in[i] - '0');       
            }    
            if(i == length -1){                    
                matrix[m-1][n-1] = acc + decAcc;
            }
        } else if (in[i] == ' '){                   //if space, number seperator
            matrix[rindex][cindex] = acc + decAcc;           
            acc = 0;    
            isDec = 0; 
            decAcc = 0; 
            decVal = 1;                          //reset acc and add to arr
            if(cindex == n - 1){                    //end of row, reset to new
                rindex += 1;
                cindex = 0;
            }else{
                cindex += 1;
            }
        }
    }

    // print_matrix(matrix, m, n);
    return matrix;
    // free_matrix(matrix, m);
}

void swap_row(float** matrix, int swap, int pivot, int n){
    /**
     * done with a temporary int, that holds the value from one array.
    */
   int temp;
   for(int i = 0; i < n; i++){
        temp = matrix[pivot][i];
        matrix[pivot][i] = matrix[swap][i];
        matrix[swap][i] = temp;
   }
}

void scale_row(float** matrix, int row, double scalar, int n){
    /**
     * Args:
     *  - matrix, row (index), scalar, n (cols)
     * scales the row by the scalar.
     * If want to divide row, the scalar should be put 
    */
    for(int i = 0; i < n; i++){
        matrix[row][i] = matrix[row][i] * scalar;
    }
}

void eliminate_nonpivots(float **matrix, int pivCol, int pivRow, int m, int n){
    /**
     * Iterates through the rows below the pivot position and eliminates the
     * values underneath.
    */
   float *pvtRow = matrix[pivRow];
   float scalar = 1;
   for(int i = pivRow+1; i < m; i++){
        for(int j = pivCol; j < n; j++){
            if(j == pivCol){
                scalar = abs(matrix[i][j]);
                scale_row(matrix, pivRow, abs(1/pvtRow[j]), n);
                scale_row(matrix, pivRow, scalar, n);
            }
            matrix[i][j] = matrix[i][j] - pvtRow[j];
            if(j == n - 1){
                if(pvtRow[j] < 0){
                    scale_row(matrix, pivRow, -(1/scalar), n);
                } else {
                    scale_row(matrix, pivRow, 1/scalar, n);
                }
            }
        }
   }
}

void row_reduction(float **matrix, int m, int n){
    /**
     * Row reduction algorithm:
     *  1) Iterate through columns -- row-wise (look at 1 column at a time)
     *  2) Iterate through the column -- column-wise
     *      2a) Search through until a non-zero number is found
     *      2b) Swap that row with pivot row
     *  3) Divide the entire row by pivot value
     *  4) Subract row from every other row in matrix
     *  5) Go to next column, repeat from step 1
     * Helper Functions: swap_row(), subtract_row(), scale_row()
    */
   int pvtRow = 0;
   int pvtCol = 0;
   int i = 0;
   int j = 0;

   for(i = pvtCol; i < n; i++){
        for(j = pvtRow; j < m; j++){
            if(matrix[j][i] == 0){
            }
            else{
                swap_row(matrix, j, pvtRow, n);
                // if(matrix[j][i] == 0){
                //     scale_row(matrix, j, matrix[j][i], n);
                // }
                // else{
                //     scale_row(matrix, j, 1/matrix[j][i], n);
                // }
                eliminate_nonpivots(matrix, i, pvtRow, m, n);
                pvtRow++;
                pvtCol++;
                break;
            }
        }   
   }
}

int main(){
    string input;
    map <string, float**> matrices;
    int m;
    int n;
    string name;

    cout << "Enter a name for the matrix: ";
    cin >> name;
    cout << "Enter the number of rows(m): ";
    cin>> m;
    cout << "Enter the number of cols(n): ";
    cin>> n;
    cin.clear();                                //Wipe buffer for cin
    fflush(stdin);                              //----->
    cout << "Please enter a matrix: ";
    getline(cin, input);

    float** matrix1 = parse_input(input, m, n);
    matrices[name] = matrix1;
    print_matrix(matrices[name], m, n);
    cout << "\n";

    // swap_row(matrix1, 1, 2, n);
    // print_matrix(matrices[name], m, n);
    // scale_row(matrix1, 0, 0.1,n);
    // eliminate_nonpivots(matrices[name], 0,0,m,n);
    row_reduction(matrices[name], m, n);
    print_matrix(matrices[name], m, n);
    free_matrix(matrices[name], m);

    // fscanf(stdin, "c"); //Used for debugging with leaks.

    return 0;
}