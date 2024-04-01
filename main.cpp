#include <iostream>
#include <cctype>
using namespace std;


void parse_input(string in, int m, int n){
/**
 * This function will be called to read user input for a matrix/vector
    Would like user input to look as such:
        MATRIX (3x3 example):
        x = [1,2,3;4,5,6;,7,8,9] (base form)
        x(3,3) = 1 2 3 4 5 6 7 8 9 (alt form)
    Not sure if variable assignment is necessary in current program iteration.
    -> Could use variable assignment as a key:val pair in a dictionary 
    Will first do this as the alternate form, as in the long run I believe it will be easier
*/  
    int length = in.length();
    cout << length << " is the length\n";
    if(length < 7){
        cout << "input is invalid";
        return;
    };

    /*
        Idea here is that because we know the dimensions of the matrix, we can directly 
        create the matrix, rather than iterate twice through the string.
    */
    // int matrix[m*n];
    int matrix[m][n];
    int acc = 0, index = 0, rindex = 0, cindex = 0;
    
    for(int i = 0; i < length; i++){
        if(isdigit(in[i])){
            cout << in[i] << " is a digit\n";
            acc = (acc * 10) + (in[i] - '0');

            if(i == length -1){
                matrix[m][n] = acc;
            }
        } else if (in[i] == ' '){
            matrix[rindex][cindex] = acc;
            acc = 0;
            if(cindex == n - 1){
                rindex += 1;
                cindex = 0;
            }else{
                cindex += 1;
            }
        }
    }

    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            cout << matrix[i][j] << ' ';
        }
    }
    
    // for(int i = 0; i < length; i++){
    //     if(isdigit(in[i])){
    //         cout << in[i] << " is a digit\n";
    //         acc = (acc * 10) + (in[i] - '0');

    //         if(i == length -1){
    //             matrix[index] = acc;
    //         }
    //     } else if (in[i] == ' '){
    //         matrix[index] = acc;
    //         // cout << matrix[index] << ' ';
    //         acc = 0;
    //         index += 1;
    //     }
    // }

    // for(int x = 0; x < m*n; x++){
    //     cout << matrix[x] << ' ';
    // }
    
}

int main(){
    string input;
    int m;
    int n;
    // // int out[] = {1,2,3,4,5};

    cout << "Enter the number of rows(m): ";
    cin>> m;
    cout << "Enter the number of cols(n): ";
    cin>> n;
    cin.clear();                                //Wipe buffer for cin
    fflush(stdin);                              //----->
    cout << "Please enter a matrix: ";
    getline(cin, input);
    
    // cout << input.length() << '\n';
    // // cout << *out;
    parse_input(input, m, n);

    // int row[5] = {0,1,3,5,6};
    // int *rwptr = row;
    // cout << *(rwptr + 2);


    return 0;
}