// Chani Kaminetsky
// Comp Org Fall '23
// Final Project

#include <stdio.h>

// Encoding a UTF8 string, taking as input an ASCII string, 
// with UTF8 characters encoded using the “U+” notation, and returns a UTF8 encoded string.
int my_utf8_encode(char *input, char *output){
    int outputTracker = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char holder = input[i];

        // Find its range
        // 1 byte 0xxxxxxx
        if ((0x0000 < (unsigned char)holder) && ((unsigned char)holder <= 0x007F)){
            output[outputTracker] = ((unsigned char)holder);
            // get ready for the next byte
            outputTracker += 1;
        }
        // 2 bytes 110xxxxx	10xxxxxx
        else if ((0x0080 <  (unsigned char)holder) && ((unsigned char)holder <= 0x07FF)){
            // get the green and add the leading 110
            output[outputTracker] = ((holder >> 6) | 0xC0);

            // get ready for the next byte
            outputTracker += 1;
            // reassign holder
            holder = input[i];
            // get the red and add the leading 10
            // isolate the right 6 bits
            holder = (holder & 0x3F); 
            // add the leading 10
            holder = (holder | 0x80);
            // put it in the next spot
            output[outputTracker] = holder;

            // get ready for the next byte
            outputTracker += 1;
        }

        // 3 bytes 1110xxxx 10xxxxxx 10xxxxxx
        else if ((0x0800 <  (unsigned char)holder) && ((unsigned char)holder <= 0xFFFF)){
            // get the blue and add the leading 1110
            output[outputTracker] = ((holder >> 12) | 0xEF);

            // get ready for the next byte
            outputTracker += 1;
            // reassign holder
            holder = input[i];
            // get the green and move it to the right and 
            // get rid of any 1's before it
            holder = ((holder >> 6) & 0x3F);
            // add the leading 10
            holder = (holder | 0x80);

            // get ready for the next byte
            outputTracker += 1;
            // reassign holder
            holder = input[i];
            // finally get the red (6 most right bits)
            // isolate the right 6 bits
            holder = (holder & 0x03F);  
            // add the leading 10
            holder = (holder | 0x80);
            // put it in the next spot
            output[outputTracker] = holder;

            // get ready for the next byte
            outputTracker += 1;

        }
        // 4 bytes 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if ((0x10000 <  (unsigned char)holder) && ((unsigned char)holder <= 0x10FFFF)){
            // get the purple and add the leading 11110
            output[outputTracker] = ((holder >> 18) | 0xF7);

            // get ready for the next byte
            outputTracker += 1;
            // reassign holder
            holder = input[i];
            // get the blue, the next 6 bits
            // get rid of any 1's before it
            holder = ((holder >> 12) & 0x3F);
            // add the leading 10
            holder = (holder | 0x80);

            // get ready for the next byte
            outputTracker += 1;
            // reassign holder
            holder = input[i];
            // get the green and move it to the right and 
            // get rid of any 1's before it
            holder = ((holder >> 6) & 0x3F);
            // add the leading 10
            holder = (holder | 0x80);

            // get ready for the next byte
            outputTracker += 1;
            // reassign holder
            holder = input[i];
            // finally get the red (6 most right bits)
            // isolate the right 6 bits
            holder = (holder & 0x03F);  
            // add the leading 10
            holder = (holder | 0x80);
            // put it in the next spot
            output[outputTracker] = holder;

            // get ready for the next byte
            outputTracker += 1;
        }

        else{
            // Invalid input
            return -1;
        }
    }
    //End the output
    output[outputTracker]='\0';

    for (int i = 0; output[i] != '\0'; i++){
        printf("%X", output[i]);
    }

    return 0;
}

// Takes a UTF8 encoded string, and returns a string, with ASCII 
// representation where possible, and UTF8 character representation for non-ASCII characters.
int my_utf8_decode(char *input, char *output){
   for (int i = 0; input[i] != '\0'; i++) {
       char holder = input[i]; 

       // 1 Byte
       if ((holder & 0x80) == 0){
            output = holder;
       }

       // 2 Bytes
       if ((holder & 0xE0) == 0xC0){
            // get rid of the leading 110
            holder = (holder << 3);
            output = holder;

            // get rid of the leading 10
            // reassign holder
            holder = input[i];
            holder = (holder << 2);

            // add it to the output
            // first we need to make room
            output = ((unsigned char)output << 3);
            output = ((unsigned char)output | holder);
       }

       // 3 Bytes
       if ((holder & 0xF0) == 0xE0){
            // get rid of the leading 1110
            holder = (holder << 4);
            output = holder;

            // get rid of the leading 10
            // reassign holder
            holder = input[i];
            holder = (holder << 2);

            // add it to the output
            // first we need to make room
            output = ((unsigned char)output << 2);
            output = ((unsigned char)output | holder);

            // get rid of the leading 10
            // reassign holder
            holder = input[i];
            holder = (holder << 2);

            // add it to the output
            // first we need to make room
            output = ((unsigned char)output << 6);
            output = ((unsigned char)output | holder);
       }

       // 4 Bytes
       if ((holder & 0xF8) == 0xF0){
            // get rid of the leading 11110
            holder = (holder << 5);
            output = holder;

            // get rid of the leading 10
            // reassign holder
            holder = input[i];
            holder = (holder << 2);

            // add it to the output
            // first we need to make room
            output = ((unsigned char)output << 1);
            output = ((unsigned char)output | holder);

            // get rid of the leading 10
            // reassign holder
            holder = input[i];
            holder = (holder << 2);

            // add it to the output
            // first we need to make room
            output = ((unsigned char)output << 6);
            output = ((unsigned char)output | holder);

            // get rid of the leading 10
            // reassign holder
            holder = input[i];
            holder = (holder << 2);

            // add it to the output
            // first we need to make room
            output = ((unsigned char)output << 6);
            output = ((unsigned char)output | holder);
       }
   }
   return 0;
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
    char *input = "\u20AC";
    char *output;
    my_utf8_encode(input, output);
    printf("Input: \n");
    printf("%s\n", input);
    printf("Output: \n");
    printf("%s\n", output); 

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

// // Testing
// // ---------------------------------------------------------------------

// // Check Function
// int my_utf8_checkTest(unsigned char *string, int expected){
//     int actual = my_utf8_check(string);
//     printf("%s\n", string);
//     printf("%s:, expected=%d, actual=%d\n",
//             (expected == actual ? "PASSED" : "FAILED"),
//             expected, actual);
// }

// void my_utf8_checkTestAll() {
//     my_utf8_checkTest("\u00A3", 1);
// } 

// // ---------------------------------------------------------------------
// // Str Len
// int my_utf8_strlenTest(unsigned char *string, int expected){
//     int actual = my_utf8_strlen(string);
//     printf("%s\n", string);
//     printf("%s:, expected=%d, actual=%d\n",
//             (expected == actual ? "PASSED" : "FAILED"),
//             expected, actual);
// }

// void my_utf8_strlenTestAll() {
//     my_utf8_strlenTest("\u00A3", 1);
// }

// // ---------------------------------------------------------------------
// // Charat
// char *my_utf8_charatTest(unsigned char *string, int index, int expected){
//     int actual = *my_utf8_charat(string, index);
//     printf("%s\n", string);
//     printf("%s:, expected=%d, actual=%d\n",
//             (expected == actual ? "PASSED" : "FAILED"),
//             expected, actual);
// }

// void my_utf8_checkTestAll() {
//     my_utf8_charatTest("\u00A3", 0, 1); //change the 1
// }

// // ---------------------------------------------------------------------
// // Strcmp
// int my_utf8_strcmpTest(unsigned char *string1, unsigned char *string2, int expected){
//     int actual = my_utf8_strcmp(string1, string2);
//     printf("%s\n", string1, string2);
//     printf("%s:, expected=%d, actual=%d\n",
//             (expected == actual ? "PASSED" : "FAILED"),
//             expected, actual);
// }

// void my_utf8_strcmpTestAll() {
//     my_utf8_strcmpTest("\u00A3", "\u00A3", 1);
// }
