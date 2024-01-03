// Chani Kaminetsky
// Comp Org Fall '23
// Final Project

#include <stdio.h>

// Encoding a UTF8 string, taking as input an ASCII string, 
// with UTF8 characters encoded using the “U+” notation, and returns a UTF8 encoded string.
int my_utf8_encode(char *input, char *output){

    // for (int i = 0; input[i] != '\0'; i++) {
    //     unsigned char curChar = (unsigned char)input[i];
    //     output[0] = (curChar >> 4) & 0xF;
    //     output[1] = curChar & 0xF; 
    //     output[2] = '\0';

    //     printf("Hexadecimal representation of input[%d]: %s\n", i, output);

    // }

    // return 0;
}


    
// Takes a UTF8 encoded string, and returns a string, with ASCII 
// representation where possible, and UTF8 character representation for non-ASCII characters.
int my_utf8_decode(char *input, char *output){
}

// Validates that the input string is a valid UTF8 encoded string.
int my_utf8_check(char *string){

}

// Returns the number of characters in the string.
int my_utf8_strlen(char *string){
    int counter = 0;
    for (int i = 0; string[i] != '\0'; i++){
        // Look for a leading byte, or a not following
        // byte (aka can't start with 10) but can start with 0 (like ascii)
        // or 110...
        if ((((string[i] >> 7 == 0) && 0x0001) != 0) || (((string[i] >> 6) && 0x0001) != 0)){
            counter++;
        }
    }

    return counter;
}

// Returns the UTF8 encoded character at the location specified.
char *my_utf8_charat(char *string, int index){
    int completeLetters;


    for (int i = 0; string[i] != '\0'; i++){
        // If we haven't reached our goal yet, keep moving
        // along the letters in the word
        if (completeLetters != (index)){

        if (((string[i] >> 0x7 == 0) && 0x0001) != 0){
           completeLetters += 1;
        }
        else if (((string[i] >> 0xD) && 0x110) == 0x110){
           // 2 bytes so increment 1 here and the loop will do the other
           i += 1;
           completeLetters += 1;
        }
        else if (((string[i] >> 0x14) && 0x1110) == 0x1110){
           // 3 bytes so increment 2 here and the loop will do the other
           i += 2;
           completeLetters += 1;
        }
        else if (((string[i] >> 0x1B) && 0x11110) == 0x11110){
           // 4 bytes so increment 3 here and the loop will do the other
           i += 3;
           completeLetters += 1;
        }
        }

        // We have reached our goal index
        else if (completeLetters == (index)){
            return string[i];

        } 
    }
    
    //Out of bounds, we finished the word and didn't reach the index
    return NULL;
}

// Returns whether the two strings are the same 
// (similar result set to strcmp() )
int my_utf8_strcmp(char *string1, char *string2){

    // Accounts for the typical string termination as well 
    // as the the type of
    while (*string1 != '\0' && *string2 != '\0') {
        
        // if they are different return -1 now
        if (*string1 != *string2) {
            return -1;
        }

        //otherwise keep incrementing
        string1++;
        string2++;
    }

    // If we made it to here the strings are the same
    if (*string1 == '\0' && *string2 == '\0'){
        return 1;
    }

    // If one is longer than the other-they are not the
    // same and return -1
    else{
        return -1;
    }
}


// Two of my own:


// Returns the amount of bytes in a character or word
int byteCounter(char *string){
    int byteCounter;
    for (int i = 0; string[i] != '\0'; i++){
        if (((string[i] >> 0x7 == 0) && 0x0001) != 0){
           byteCounter += 1; 
        }
        else if (((string[i] >> 0xD) && 0x110) == 0x110){
           byteCounter += 2;  
        }
        else if (((string[i] >> 0x14) && 0x1110) == 0x1110){
           byteCounter += 3;  
        }
        else if (((string[i] >> 0x1B) && 0x11110) == 0x11110){
           byteCounter += 4;  
        }
    }

    return byteCounter;
}

void main(){


    // char *input = "\u20AC";
    // char *output = NULL;
    // my_utf8_encode(input, output);
    // printf("%s", output);

    // Compare
    char *string1 = "Hello";
    char *string2 = "Hello";
    printf("%d\n", my_utf8_strcmp(string1, string2));

    char *string1B = "Helloooooo";
    char *string2B = "Hello";
    printf("%d\n", my_utf8_strcmp(string1B, string2B));

    char *string1C = "אריה";
    char *string2C = "אריה";
    printf("%d\n", my_utf8_strcmp(string1C, string2C));
     
    char *string1D = "\u05D0\u05E8\u05D9\u05D4";
    char *string2D = "אריה";
    printf("%d\n", my_utf8_strcmp(string1D, string2D));

    // Length
    printf("Hello\n");
    printf("%d\n", my_utf8_strlen("Hello"));
    printf("%c\n", "\xC2\xA3");
    printf("%d\n", my_utf8_strlen("\u00A3"));
    //printf("%d\n", my_utf8_strlen(string2D));
    
}
