#include <iostream>
#include <string>
#include <cctype>
using namespace std;


void print_matrix(int** matrix,int m,int n){
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void free_matrix(int** matrix, int m) {
    // Free each row first
    for (int i = 0; i < m; i++) {
        delete[] matrix[i];
    }
    // Free the array of pointers
    delete[] matrix;
}

void parse_input(string in, int m, int n){
/**
 * This function will be called to read user input for a matrix/vector
    Would like user input to look as such:
        MATRIX (3x3 example):
        enter rows: 3
        enter cols: 3
        enter matrix: x = 1 2 3 4 5 6 7 8 9
    Not sure if variable assignment is necessary in current program iteration.
    -> Could use variable assignment as a key:val pair in a dictionary 
*/  
    int length = in.length();
    /*
        Idea here is that because we know the dimensions of the matrix, we can 
        directly create the 2D array, rather than iterate twice through the string
    */
    int** matrix = new int*[m];
    for (int i = 0; i < m; i++) {
        matrix[i] = new int[n];
    }

    int acc = 0, index = 0, rindex = 0, cindex = 0;
    
    for(int i = 0; i < length; i++){
        if(isdigit(in[i])){                         //Checks if char is an int
            acc = (acc * 10) + (in[i] - '0');       //adds digit to accumulator

            if(i == length -1){                     //if last digit add to arr
                matrix[m-1][n-1] = acc;
            }
        } else if (in[i] == ' '){                   //if space, number seperator
            matrix[rindex][cindex] = acc;           
            acc = 0;                                //reset acc and add to arr
            if(cindex == n - 1){                    //end of row, reset to new
                rindex += 1;
                cindex = 0;
            }else{
                cindex += 1;
            }
        }
    }

    print_matrix(matrix, m, n);
    free_matrix(matrix, m);
}

int main(){
    string input;
    int m;
    int n;

    cout << "Enter the number of rows(m): ";
    cin>> m;
    cout << "Enter the number of cols(n): ";
    cin>> n;
    cin.clear();                                //Wipe buffer for cin
    fflush(stdin);                              //----->
    cout << "Please enter a matrix: ";
    getline(cin, input);
    parse_input(input, m, n);

    return 0;
}