const int BUFFER_SIZE = 26;
const int offset = 1;
#include <iostream>

static char inputString[] = "ydrsxdladccdclzqhmzqzrztbd"; //this test string should output zestyembeddedmarinarasauce

//puts a character into the output buffer
//remember that nothing will show until you print a newline.
void putc(char c){
    printf("%c", c);
}

//returns a number for a corresponding letter 
//a is 0, b is 1, all the way to z is 25
int letterToNumber(char c){ 
    return c - 'a';
}

//returns a letter to the corresponding number
//a is 0, b is 1, all the way to z is 25
char numberToLetter(char i){ 
    return i + 'a';
}

int main(void)
{
    //CODE GOES HERE 
    for (int i = 0; inputString[i] != '\0'; ++i) {
    char c = inputString[i];

    if (c >= 'a' && c <= 'z') {
        int kkk = letterToNumber(c);                 
        int shifted = (kkk + offset) % BUFFER_SIZE;  
        char out = numberToLetter(shifted);          
        putc(out);
    } else {
        putc(c);
    }
}
    putc('\n');
}
