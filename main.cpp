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
    Will first do this as the alternate form, as in the long run I believe it 
    will be easier
*/  
    int length = in.length();
    cout << length << " is the length\n";
    if(length < 7){
        cout << "input is invalid";
        return;
    };

    /*
        Idea here is that because we know the dimensions of the matrix, we can 
        directly create the matrix, rather than iterate twice through the string
    */
    int matrix[m][n];
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