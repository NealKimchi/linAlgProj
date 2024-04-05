#include <iostream>
#include <string>
#include <cctype>
#include <map>
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

int** parse_input(string in, int m, int n){
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

    // print_matrix(matrix, m, n);
    return matrix;
    // free_matrix(matrix, m);
}

int main(){
    string input;
    map <string, int**> matrices;
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

    int** matrix1 = parse_input(input, m, n);
    matrices[name] = matrix1;
    print_matrix(matrices[name], m, n);
    free_matrix(matrices[name], m);

    // fscanf(stdin, "c"); //Used for debugging with leaks.

    return 0;
}