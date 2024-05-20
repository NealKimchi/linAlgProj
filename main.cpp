#include <iostream>
#include <string>
#include <cctype>
#include <map>
#include <cmath>
#include <stdlib.h>
#include <cassert>
using namespace std;

float** parse_input(string in, int m, int n);
class UserMatrix{
    float** entries;
    int m;
    int n;

    public:
    UserMatrix(float** entries, int dimM, int dimN): 
    entries(entries), m(dimM), n(dimN){};
    UserMatrix(){};

    float** getEntries(){return entries;};
    int getM(){return m;};
    int getN(){return n;};

    void setEntries(float** newEntries){
        entries = newEntries;
    }
    void parseEntries(string in){
        entries = parse_input(in, m, n);
    }
    void setM(int mDim){m = mDim;};
    void setN(int nDim){n = nDim;};

    void setEntry(int i, int j, float val){
        entries[i][j] = val;
    }

    void print_matrix(){
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << entries[i][j] << " ";
            }
        cout << endl;
        }
    }

    void print_col(int col){
        cout << '[';
        for (int i = 0; i < m; ++i) {
            if(i == m-1){
                cout << entries[i][col];
                break;
        }
        cout << entries[i][col] << ", ";
        }
        cout << ']' << endl;
    }

    void print_row(int row){
        cout << '[';
        for (int i = 0; i < n; ++i) {
            if(i == n-1){
                cout << entries[row][i];
                break;
            }
            cout << entries[row][i] << ", ";
        }
        cout << ']' << endl;
    }

    void print_entry(int m, int n){
        cout << entries[m][n] << endl;
    }

    void free_matrix(){
        // Free each row first
        for (int i = 0; i < m; i++) {
            delete[] entries[i];
        }
        // Free the array of pointers
        delete[] entries;
    }
};


void transpose(map<string, UserMatrix*> &matrices, string key, string key2){
    /**
     * The matrix transpose function will take in the dictionary containing all
     * the matrices, and the key of the matrix we are transposing. Currently I have
     * not decided whether I will create a new matrix with the name 'key'_transpose
     * or just override the UserMatrix object in the dictionary with its transpose.
    */
    int ogM = matrices[key]->getM();
    int ogN = matrices[key]->getN();
    

    float** transpose = new float*[ogN];
    for(int i = 0; i < ogN; i++){
       transpose[i] = new float[ogM]; 
    }

    float** og_entries = matrices[key]->getEntries();
    for(int i = 0; i < ogM; i++){
        for(int j = 0; j < ogN; j++){
            transpose[j][i] = og_entries[i][j];
        }
    }
    UserMatrix* transposeMatrix = new UserMatrix(transpose, ogN, ogM);
    matrices[key2] = transposeMatrix; 
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

    int rindex = 0, cindex = 0, decVal = 1, isDec = 0, isNeg = 0; 
    float decAcc = 0, acc = 0;
    
    for(int i = 0; i < length; i++){
        if(isdigit(in[i]) || in[i] == '.' || in[i] == '-'){   
            if(in[i] == '.'){
                isDec = 1;
            }
            if(in[i] == '-'){
                isNeg = 1;
            }
            if(isDec && in[i] != '.'){
                float digit = (in[i] - '0') / pow(10, decVal);
                decAcc = decAcc + digit;
                decVal++;
            }                     
            if(in[i] != '.' && !isDec && in[i] != '-'){
                acc = (acc * 10) + (in[i] - '0');       
            }   
            if(i == length -1){   
                if(isNeg){
                    matrix[m-1][n-1] = -1 * (acc + decAcc);
                } else {
                    matrix[m-1][n-1] = acc + decAcc;
                }
            }
        } else if (in[i] == ' '){
            if(isNeg){
                matrix[rindex][cindex] = -1 * (acc + decAcc);
            } else {
                matrix[rindex][cindex] = acc + decAcc;           
            }
            acc = 0;    
            isDec = 0; 
            decAcc = 0; 
            decVal = 1;  
            isNeg = 0;                        //reset acc and add to arr
            if(cindex == n - 1){                    //end of row, reset to new
                rindex += 1;
                cindex = 0;
            }else{
                cindex += 1;
            }
        }
    }

    return matrix;
}

void swap_row(float** matrix, int swap, int pivot, int n){
    /**
     * done with a temporary int, that holds the value from one array.
    */
   float temp;
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
                if(scalar == 0){
                    break;
                }
                scale_row(matrix, pivRow, abs(1/pvtRow[j]), n);
                scale_row(matrix, pivRow, scalar, n);
            }
            if(matrix[i][j] < 0 && pvtRow[j] > 0){
                matrix[i][j] = matrix[i][j] + pvtRow[j];
            } else {
                matrix[i][j] = matrix[i][j] - pvtRow[j];
            }
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

void row_reduction(map<string, UserMatrix*> matrices, string key){
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
   UserMatrix* user = matrices[key];
   float** matrix = (*user).getEntries();
   int m = (*user).getM();
   int n = (*user).getN();

   int pvtRow = 0;
   int pvtCol = 0;
   int i = 0;
   int j = 0;

   for(i = pvtCol; i < n; i++){
        for(j = pvtRow; j < m; j++){
            if(matrix[j][i] == 0){
            }
            else{
                if(i == n-1 && j == m-1){
                    scale_row(matrix, j, 1/matrix[j][i], n);
                    break;
                }
                swap_row(matrix, j, pvtRow, n);
                eliminate_nonpivots(matrix, i, pvtRow, m, n);
                pvtRow++;
                pvtCol++;
                break;
            }
        }   
   }
}

void input_matrix(map<string, UserMatrix*> &matrices){
    string input, name;
    int m, n;

    cout << "Enter a name for the matrix: ";
    cin >> name;
    cout << "Enter the number of rows(m): ";
    cin>> m;
    cout << "Enter the number of cols(n): ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //Wipe buffer for cin
    cin>> n;                            
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //----->
    cout << "Please enter a matrix: ";
    getline(cin, input);

    UserMatrix* matrix= new UserMatrix;
    matrix->setM(m);
    matrix->setN(n);
    matrix->parseEntries(input);
    matrices[name] = matrix;
    (*matrices[name]).print_matrix();
    cout << '\n';
}

void matrix_multiplication(map<string, UserMatrix*> &matrices, string key1, string key2, string key3){
    assert(matrices[key1]->getN() == matrices[key2]->getM() && "Dimensions do not match");

    UserMatrix* newMatrix = new UserMatrix;
    int mDim = matrices[key1]->getM();
    int nDim = matrices[key2]->getN();
    newMatrix->setM(mDim);
    newMatrix->setN(nDim);
    float** entries = new float*[mDim];
    for (int i = 0; i < mDim; i++) {
        entries[i] = new float[nDim];
    }
    newMatrix->setEntries(entries);
    float** matrix1 = matrices[key1]->getEntries();
    float** matrix2 = matrices[key2]->getEntries();


    int klim = matrices[key1]->getN();
    for(int i = 0; i < mDim; i++){
        for(int j = 0; j < nDim;j++){
            float acc = 0;
            for(int k = 0; k < klim; k++){
                acc += matrix1[i][k] * matrix2[k][j];
            }
            newMatrix->setEntry(i, j, acc);
        }
    }
    matrices[key3] = newMatrix;
}

int main(){
    map<string, UserMatrix*> matrices;
    char choice;
    string key1;
    string key2;
    string key3;
    input_matrix(matrices);
    do{
        cout << "What action would you like to perform\n1: row-reduction   ";
        cout << "2: print matrix   3: insert another matrix   4: matrix multiplication   5: transpose   6: exit";
        cin >> choice;
        switch(choice){
            case '1':
                cout << "Enter the name of the matrix: ";
                cin >> key1;
                row_reduction(matrices, key1);
                (*matrices[key1]).print_matrix();
                break;
            case '2':
                cout << "Enter the name of the matrix: ";
                cin >> key1;
                (*matrices[key1]).print_matrix();
                // cout << "[0][0] " << (*matrices[key]).getEntries()[0][0] << "\n";
                // cout << "[0][1] " << (*matrices[key]).getEntries()[0][1] << "\n";
                // cout << "[1][0] " << (*matrices[key]).getEntries()[1][0] << "\n";
                break;
            case '3':
                input_matrix(matrices);
                break;
            case '4':
                cout << "Enter the name of the first matrix: ";
                cin >> key1;
                cout << "Enter the name of the second matrix: ";
                cin >> key2;
                cout << "Enter the name of the new matrix: ";
                cin >> key3;
                matrix_multiplication(matrices, key1, key2, key3);
                (*matrices[key3]).print_matrix();
                break;
            case '5':
                cout << "Enter the name of the matrix to transpose: ";
                cin >> key1;
                cout << "Enter the name for the new matrix: ";
                cin >> key2;
                transpose(matrices, key1, key2);
                (*matrices[key2]).print_matrix();
                break;
            case '6':
                break;
        }

    } while(choice != '6');

    for (auto i = matrices.begin(); i != matrices.end(); i++)
        i->second->free_matrix();

    // fscanf(stdin, "c"); //Used for debugging with leaks.

    return 0;
}
