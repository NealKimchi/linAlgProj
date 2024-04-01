import string


def parse_input(raw):
    """
        This function will be called to read user input for a matrix/vector
        Would like user input to look as such:
            MATRIX (3x3 example):
            x = [1,2,3;4,5,6;,7,8,9] (base form)
            x(3,3) = 1 2 3 4 5 6 7 8 9 (alt form)
        Not sure if variable assignment is necessary in current program iteration.
        -> Could use variable assignment as a key:val pair in a dictionary 
        Will first do this as the alternate form, as in the long run I believe it will be easier
    """
    
    for c in raw:
        print(c)
        
    
    
    
def main():
    # userInput = input("Enter matrix: ")
    # print(userInput)
    parse_input("(3,3) 1 2 3 4 5 6 7 8 9")
    pass
        
if __name__ == "__main__":
    main()