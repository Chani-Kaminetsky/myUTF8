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
    // check for out of bounds, > \U10FFFF
    // check for valid leading etc
    // check for overlong encoding
    for (int i = 0; string[i] != '\0'; i++){
        // If this is one byte make sure there are no following bits
        if (((string[i] >> 0x7) && 0x0001) == 0){
            if (((string[i+1] >> 0x6) && 0x0010) == 10){
                //invalid
                return -1;
            }
        }
        // If it's 2 bytes make sure there is only one following byte
        else if (((string[i] >> 0xD) && 0x110) == 0x6){
           if ((((string[i+1] >> 0x6) && 0x0010) != 10) || \
           (((string[i+2] >> 0x6) && 0x0010) == 10)){
                //invalid
                return -1;
           }
        }
        // 3 bytes check that there are only 2 following bytes
        else if (((string[i] >> 0x14) && 0x1110) == 0xE){
          if ((((string[i+1] >> 0x6) && 0x0010) != 10) || \
           (((string[i+2] >> 0x6) && 0x0010) != 10) || \
            (((string[i+3] >> 0x6) && 0x0010) == 10) )
           {
                //invalid
                return -1;
           }
        }
        // 4 bytes check that there are only 3 following bytes
        else if (((string[i] >> 0x1B) && 0x11110) == 0x3E){
          if ((((string[i+1] >> 0x6) && 0x0010) != 10) || \
           (((string[i+2] >> 0x6) && 0x0010) != 10) || \
           (((string[i+3] >> 0x6) && 0x0010) != 10) || \
            (((string[i+4] >> 0x6) && 0x0010) == 10) )
           {
                //invalid
                return -1;
           } 
        }
    }
    // It is valid
    return 1;
}

// Returns the number of characters in the string.
int my_utf8_strlen(char *string){
    int counter = 0;
    for (int i = 0; string[i] != '\0'; i++){
        // Look for a leading byte, or a not following
        // byte (aka can't start with 10) but can start with 0 (like ascii)
        // or 110...
        if (((string[i] >> 7) & 0x1 == 0) || ((string[i] >> 6) & 0x0b11 != 0x10)){
            counter++;
        }
    }

    return counter;
}

// Returns the UTF8 encoded character at the location specified.
char *my_utf8_charat(char *string, int index){
    int completeLetters = 0;
    char *answer;

    for (int i = 0; string[i] != '\0'; i++){
        // If we haven't reached our goal yet, keep moving
        // along the letters in the word
        if (completeLetters != (index)){

        if (((string[i] >> 0x7) & 0x0001) == 0){
           // 1 byte long
           completeLetters += 1;
        }
        else if (((string[i] >> 0xD) & 0x110) == 0x6){
           // 2 bytes so increment 1 here and the loop will do the other
           i += 1;
           completeLetters += 1;
        }
        else if (((string[i] >> 0x14) & 0x1110) == 0xE){
           // 3 bytes so increment 2 here and the loop will do the other
           i += 2;
           completeLetters += 1;
        }
        else if (((string[i] >> 0x1B) & 0x11110) == 0x3E){
           // 4 bytes so increment 3 here and the loop will do the other
           i += 3;
           completeLetters += 1;
        }
        }

        // We have reached our goal index
        else if (completeLetters == (index)){
            for (int j=i; (((string[j] >> 6) & 0x0001) != 0); j++){
                *answer = string[j];
                answer++;
            }
            return answer;

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

// Returns which string requires more bytes
int byteCounter(char *string1, char *string2){
    int byteCounter1 = 0;
    int byteCounter2 = 0;

    for (int i = 0; string1[i] != '\0'; i++){
        if (((string1[i] >> 0x7 == 0) & 0x0001) != 0){
           byteCounter1 += 1; 
        }
        else if (((string1[i] >> 0xD) & 0x110) == 0x6){ //110
           byteCounter1 += 2;  
        }
        else if (((string1[i] >> 0x14) & 0x1110) == 0xE){ //1110
           byteCounter1 += 3;  
        }
        else if (((string1[i] >> 0x1B) & 0x11110) == 0x3E){ //111110
           byteCounter1 += 4;  
        }
    }

    for (int i = 0; string2[i] != '\0'; i++){
        if (((string2[i] >> 0x7 == 0) & 0x0001) != 0){
           byteCounter2 += 1; 
        }
        else if (((string2[i] >> 0xD) & 0x110) == 0x6){ //110
           byteCounter2 += 2;  
        }
        else if (((string2[i] >> 0x14) & 0x1110) == 0xE){ //1110
           byteCounter2 += 3;  
        }
        else if (((string2[i] >> 0x1B) & 0x11110) == 0x3E){ //111110
           byteCounter2 += 4;  
        }
    }

    if (byteCounter1 > byteCounter2){
        printf("%d\n", byteCounter1);
        printf("%d\n", byteCounter2);
        return 1; // for string 1
    }
    else if (byteCounter2 > byteCounter1){
        printf("%d\n", byteCounter1);
        printf("%d\n", byteCounter2);
        return 2; // for string 2
    }
    else{
        printf("%d\n", byteCounter1);
        printf("%d\n", byteCounter2);
        return 0; // if they are equal in byte size
    }
}

void main(){

    // Encode
    // char *input = "\u20AC";
    // char *output = NULL;
    // my_utf8_encode(input, output);
    // printf("%s", output);

    // -------------------------------------------------
    // Compare
    // char *string1 = "Hello";
    // char *string2 = "Hello";
    // printf("%d\n", my_utf8_strcmp(string1, string2));

    // char *string1B = "Helloooooo";
    // char *string2B = "Hello";
    // printf("%d\n", my_utf8_strcmp(string1B, string2B));

    // char *string1C = "אריה";
    // char *string2C = "אריה";
    // printf("%d\n", my_utf8_strcmp(string1C, string2C));
     
    // char *string1D = "\u05D0\u05E8\u05D9\u05D4";
    // char *string2D = "אריה";
    // printf("%d\n", my_utf8_strcmp(string1D, string2D));

    // -------------------------------------------------
    // Length
    // printf("Hello\n");
    // printf("%d\n", my_utf8_strlen("Hello"));
    // printf("%s\n", "\xC2\xA3");
    // printf("%d\n", my_utf8_strlen("\u00A3"));
    // char *lenStr = "אריה";
    // printf("%d\n", my_utf8_strlen(lenStr));

    // -------------------------------------------------
    // Str Charat - NEED TO FIX
    // char *stringCharat = "\u05D0\u05E8\u05D9\u05D4";
    // printf("%X", *my_utf8_charat(stringCharat, 2));

    // -------------------------------------------------
    // Byte Counter - NEED TO FIX
    // char *string1E = "\u05D0\u05E8\u05D9\u05D4"; 
    // char *string2E = "\u05D0\u05E8\u05D9\u05D4";
    // printf("%d", byteCounter(string1E, string2E));
}

// Testing
// ---------------------------------------------------------------------

// Check Function
int my_utf8_checkTest(unsigned char *string, int expected){
    int actual = my_utf8_check(string);
    printf("%s\n", string);
    printf("%s:, expected=%d, actual=%d\n",
            (expected == actual ? "PASSED" : "FAILED"),
            expected, actual);
}

void my_utf8_checkTestAll() {
    my_utf8_checkTest("\u00A3", 1);
} 

// ---------------------------------------------------------------------
// Str Len
int my_utf8_strlenTest(unsigned char *string, int expected){
    int actual = my_utf8_strlen(string);
    printf("%s\n", string);
    printf("%s:, expected=%d, actual=%d\n",
            (expected == actual ? "PASSED" : "FAILED"),
            expected, actual);
}

void my_utf8_strlenTestAll() {
    my_utf8_strlenTest("\u00A3", 1);
}

// ---------------------------------------------------------------------
// Charat
int my_utf8_charatTest(unsigned char *string, int index, int expected){
    int actual = *my_utf8_charat(string, index);
    printf("%s\n", string);
    printf("%s:, expected=%d, actual=%d\n",
            (expected == actual ? "PASSED" : "FAILED"),
            expected, actual);
}

void my_utf8_checkTestAll() {
    my_utf8_charatTest("\u00A3", 0, ----------);
}

// ---------------------------------------------------------------------
// Strcmp
int my_utf8_strcmpTest(unsigned char *string1, unsigned char *string2, int expected){
    int actual = my_utf8_strcmp(string1, string2);
    printf("%s\n", string1, string2);
    printf("%s:, expected=%d, actual=%d\n",
            (expected == actual ? "PASSED" : "FAILED"),
            expected, actual);
}

void my_utf8_strcmpTestAll() {
    my_utf8_strcmpTest("\u00A3", "\u00A3", 1);
}
