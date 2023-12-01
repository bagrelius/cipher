#include <iostream> 



void scramble(std::string& inputString) {

    //Just using the random library (not fully unpredictable)
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    char x; 
    int len = inputString.length();

    for(int i = 0; i < len; i++) {
        
        srand(time(0));

        x = letters[rand() % 26];
        
        inputString[i] = x;
    } 

    return;
}

int main() {

    std::string instring = "BOGUS";

    scramble(instring);

    std::cout << instring << std::endl;

    return 0;
}






