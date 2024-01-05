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
        if ((input[i] & 0x80) == 0){
            output[outputTracker] = ((unsigned char)holder);
            // get ready for the next byte
            outputTracker += 1;
        }
            // 2 bytes 110xxxxx	10xxxxxx
        else if ((input[i] & 0xE0) == 0xC0){
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
        else if ((input[i] & 0xF0) == 0xE0){
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
        else if ((input[i] & 0xF8) == 0xF0){
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
    int outputTracker = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        char holder = input[i];

        // 1 Byte
        if ((holder & 0x80) == 0){
            // ascii so it doesn't need \u
            output[outputTracker] = holder;
            // Signifying ending
            outputTracker ++;
            output[outputTracker] = '\0';
            break;
        }
        // 2 Bytes
        if ((holder & 0xE0) == 0xC0){
            // start with a \u
            output[outputTracker] = 0x5C;
            outputTracker ++;
            output[outputTracker] = 0x75;
            outputTracker ++;

            // get rid of the leading 110
            holder = (holder << 3);
            // get the first 3 bits
            holder = (holder >> 2);
            output[outputTracker] = holder;
            // align it all the way to the right
            output[outputTracker] = (output[outputTracker] >> 4);
            // Go to the next hex digit
            outputTracker ++;

            // add the next 2 green bits
            // reassign holder
            holder = input[0];
            holder = (holder << 6);
            output[outputTracker] = holder;
            // make room for only two more bits
            output[outputTracker] = (output[outputTracker] >> 2);

            // on to the next input location
            // get rid of the leading 10
            // reassign holder
            holder = input[1];
            holder = (holder << 2);
            holder = (holder >> 4);

            // add it to the output
            // first we need to make room
            output[outputTracker] = (output[outputTracker] | holder);

            // Go to the next hex digit
            outputTracker ++;
            // reassign holder
            holder = input[1];
            holder = (holder & 0x0F);
            output[outputTracker] = holder;

            // Signifying ending
            outputTracker ++;
            output[outputTracker] = '\0';
            break;

        }

        // 3 Bytes
        if ((holder & 0xF0) == 0xE0){
            // get rid of the leading 1110
            holder = (holder & 0x0F);
            output[outputTracker] = holder;

            // Go to the next hex digit
            outputTracker ++;
            // get rid of the leading 10
            // reassign holder
            holder = input[1];
            holder = (holder << 2);
            holder = (holder >> 4);
            output[outputTracker] = holder;

            // Go to the next hex digit
            outputTracker ++;
            // get rid of the leading 10
            // reassign holder
            holder = input[1];
            holder = (holder & 0x3);
            holder = (holder << 2);
            output[outputTracker] = holder;

            // Take the next two bits from the next hex digit
            holder = input[2];
            // Get rid of leading 10
            holder = (holder << 2);
            holder = (holder >> 4);
            output[outputTracker] = (output[outputTracker] | holder);

            // Next hex of the unicode
            outputTracker ++;

            // reassign holder
            holder = input[2];
            holder = (holder & 0x0F);
            output[outputTracker] = holder;

            // Signifying ending
            outputTracker ++;
            output[outputTracker] = '\0';
            break;
        }

        // 4 Bytes
        if ((holder & 0xF8) == 0xF0){
            // Purple
            holder = (holder << 6);
            holder = (holder >> 6);
            holder = (holder << 2);
            output[outputTracker] = holder;

            // finish purple with blue
            // go to the next hex in utf
            holder = input[1];
            holder = (holder << 2);
            holder = (holder >> 6);
            output[outputTracker] = (output[outputTracker] | holder);

            // finish blue
            // reassign holder
            holder = input[1];
            holder = (holder & 0x0F);
            // Next hex of the unicode
            outputTracker ++;
            output[outputTracker] = holder;

            // do green then red

            // Go to the next hex digit
            outputTracker ++;
            // get rid of the leading 10
            // reassign holder
            holder = input[2];
            holder = (holder << 2);
            holder = (holder >> 4);
            output[outputTracker] = holder;

            // Go to the next hex digit
            outputTracker ++;
            // get rid of the leading 10
            // reassign holder
            holder = input[2];
            holder = (holder & 0x3);
            holder = (holder << 2);
            output[outputTracker] = holder;

            // Take the next two bits from the next hex digit
            holder = input[3];
            // Get rid of leading 10
            holder = (holder << 2);
            holder = (holder >> 4);
            output[outputTracker] = (output[outputTracker] | holder);

            // Next hex of the unicode
            outputTracker ++;

            // reassign holder
            holder = input[3];
            holder = (holder & 0x0F);
            output[outputTracker] = holder;

            // Signifying ending
            outputTracker ++;
            output[outputTracker] = '\0';
            break;

        }
    }
    return 0;
}

// Validates that the input string is a valid UTF8 encoded string.
int my_utf8_check(char *string){
    for (int i = 0; string[i] != '\0'; i++){
        if (((string[0] >> 0x6) & 0b11) == 0b10){
            return -1;
        }
        // If this is one byte make sure there are no following bits
        else if ((string[i] & 0x80) == 0){
            if (((string[i+1] >> 0x6) & 0b11) == 0b10){
                //invalid
                return -1;
            }
        }
            // If it's 2 bytes make sure there is only one following byte
        else if ((string[i] & 0xE0) == 0xC0){
            if (((string[i+1] >> 0x6) & 0b11) != 0b10){
                printf("%d", ((string[i+1] >> 0x6) != 0b10));
                printf("%d", ((string[i+2] >> 0x6) == 0b10));
                //invalid
                return -1;
            }
        }
            // 3 bytes check that there are only 2 following bytes
        else if ((string[i] & 0xF0) == 0xE0){
            if ((((string[i+1] >> 0x6) & 0b11) != 0b10) || \
            ((string[i+2] >> 0x6) != 0b10))
            {
                //invalid
                return -1;
            }
        }
            // 4 bytes check that there are only 3 following bytes
        else if ((string[i] & 0xF8) == 0xF0){
            if ((((string[i+1] >> 0x6) & 0b11) != 0b10) || \
           (((string[i+2] >> 0x6) & 0b11) != 0b10) || \
           (((string[i+3] >> 0x6) & 0b11) != 0b10))
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
    char answer[6];
    int answerTracker = 0;

    for (int i = 0; string[i] != '\0'; i++){
        // If we haven't reached our goal yet, keep moving
        // along the letters in the word
        if (completeLetters != (index)){

            if ((string[i] & 0x80) == 0){
                // 1 byte long
                completeLetters += 1;
            }
            else if ((string[i] & 0xE0) == 0xC0){
                // 2 bytes so increment 1 here and the loop will do the other
                i += 1;
                completeLetters += 1;
            }
            else if ((string[i] & 0xF0) == 0xE0){
                // 3 bytes so increment 2 here and the loop will do the other
                i += 2;
                completeLetters += 1;
            }
            else if ((string[i] & 0xF8) == 0xF0){
                // 4 bytes so increment 3 here and the loop will do the other
                i += 3;
                completeLetters += 1;
            }
        }

            // We have reached our goal index
        else if (completeLetters == (index)){
            for (int j=i; (((string[j] >> 6) & 0b0001) != 0); j++){
                answer[answerTracker] = string[j];
                answerTracker++;
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
    // as the type of
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
        if ((string1[i] & 0x80) == 0){
            byteCounter1 += 1;
        }
        else if ((string1[i] & 0xE0) == 0xC0){ //110
            byteCounter1 += 2;
        }
        else if ((string1[i] & 0xF0) == 0xE0){ //1110
            byteCounter1 += 3;
        }
        else if ((string1[i] & 0xF8) == 0xF0){ //111110
            byteCounter1 += 4;
        }
    }

    for (int i = 0; string2[i] != '\0'; i++){
        if ((string2[i] & 0x80) == 0){
            byteCounter2 += 1;
        }
        else if ((string1[i] & 0xE0) == 0xC0){ //110
            byteCounter2 += 2;
        }
        else if ((string2[i] & 0xF0) == 0xE0){ //1110
            byteCounter2 += 3;
        }
        else if ((string2[i] & 0xF8) == 0xF0){ //111110
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

int spaceItOut(char *input, char *output){
    // space = 0x20
    for (int i = 0; input[i] != '\0'; i++){
        if ((0x0000 <= (unsigned char)input[i]) && ((unsigned char)input[i] <= 0x007F)){
            *output = input[i];
            output++;
            // Add a space
            *output = 0x20;
            output++;
        }
            // 2 bytes 110xxxxx	10xxxxxx
        else if ((0x0080 <=  (unsigned char)input[i]) && ((unsigned char)input[i] <= 0x07FF)){
            *output = input[i];
            output++;
            *output = input[i+1];
            output++;
            // Add a space
            *output = 0x20;
            output++;
            //Make i jump over the next one
            i++;
        }

            // 3 bytes 1110xxxx 10xxxxxx 10xxxxxx
        else if ((0x0800 <=  (unsigned char)input[i]) && ((unsigned char)input[i] <= 0xFFFF)){
            *output = input[i];
            output++;
            *output = input[i+1];
            output++;
            *output = input[i+2];
            output++;

            // Add a space
            *output = 0x20;
            output++;
            //Make i jump over the next two
            i += 2;
        }
        // 4 bytes 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if ((0x10000 <=  (unsigned char)input[i]) && ((unsigned char)input[i] <= 0x10FFFF)){
            *output = input[i];
            output++;
            *output = input[i+1];
            output++;
            *output = input[i+2];
            output++;
            *output = input[i+3];
            output++;


            // Add a space
            *output = 0x20;
            output++;
            //Make i jump over the next three
            i += 3;
        }
    }
    return 0;
}

// the findChar should be in hex UTF 8 format
// This function will return 1 if the character is found in the string and -1 if it is not
int findMe(char *findChar, char *string){
    int byteSize;

    // figure out how many bits the character we are looking for is
    if (((findChar[0] >> 0x7) & 0b1) == 0b0){
        byteSize = 1;
    }
    else if (((findChar[0] >> 0x5) & 0b111) == 0b110){
        byteSize = 2;
    }
    else if (((findChar[0] >> 0x4) & 0b1111) == 0b1110){
        byteSize = 3;
    }
    else if (((findChar[0] >> 0x3) & 0b11111) == 0b11110){
        byteSize = 4;
    }


    for (int i = 0; string[i] != '\0'; i++){
        // if the current letter is a 1 byte letter and so is the one we are looking for, check it
        if (((string[i] & 0x80) == 0) && byteSize == 1){
            if (string[i] == findChar[0]){
                return 1;
            }
        }
        // 2 bytes 110xxxxx	10xxxxxx
        // if the current letter is a 2 bytes letter and so is the one we are looking for, check it
        else if (((string[i] & 0xE0) == 0xC0) && byteSize == 2){
            if ((string[i] == findChar[0]) && (string[i+1] == findChar[1])){
                return 1;
            }
        }

            // 3 bytes 1110xxxx 10xxxxxx 10xxxxxx
        else if (((string[i] & 0xF0) == 0xE0) && byteSize == 3){
            if ((string[i] == findChar[0]) && (string[i+1] == findChar[1]) && (string[i+2] == findChar[2])){
                return 1;
            }
        }
            // 4 bytes 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
        else if (((string[i] & 0xF8) == 0xF0) && byteSize == 4){
            if ((string[i] == findChar[0]) && (string[i+1] == findChar[1]) && (string[i+2] == findChar[2]) && (string[i+3] == findChar[3])){
                return 1;
            }
        }
    }
    // Not found
    return -1;
}


// // Testing
// // ---------------------------------------------------------------------

 // Check Function
 void my_utf8_checkTest(char *string, int expected){
     int actual = my_utf8_check(string);
     printf("%s\n", string);
     printf("%s:, expected=%d, actual=%d\n",
             (expected == actual ? "PASSED" : "FAILED"),
             expected, actual);
 }

 void my_utf8_checkTestAll() {
     my_utf8_checkTest("אריה", 1);
     my_utf8_checkTest("Hello 🌍", 1);
     my_utf8_checkTest("10000011", -1);
 }

 // ---------------------------------------------------------------------
 // Str Len
 void my_utf8_strlenTest(char *string, int expected){
     int actual = my_utf8_strlen(string);
     printf("%s\n", string);
     printf("%s:, expected=%d, actual=%d\n",
             (expected == actual ? "PASSED" : "FAILED"),
             expected, actual);
 }

 void my_utf8_strlenTestAll() {
     my_utf8_strlenTest("אריה", 4);
     my_utf8_strlenTest("Hello 🌍", 6);
     my_utf8_strlenTest("\u00A3", 1);
 }

 // ---------------------------------------------------------------------
 // Charat
 int my_utf8_charatTest(char *string, int index, char expected){
     char actual = *my_utf8_charat(string, index);
     printf("%s\n", string);
     printf("%s:, expected=%s, actual=%s\n",
             ((unsigned char) expected == actual ? "PASSED" : "FAILED"),
             expected, actual);
     return 0;
 }

 void my_utf8_charatTestAll() {
     my_utf8_charatTest("\u00A3", 0, "£");
 }

 // ---------------------------------------------------------------------
 // Strcmp
 int my_utf8_strcmpTest(char *string1, char *string2, int expected){
     int actual = my_utf8_strcmp(string1, string2);
     printf("%s\n", string1);
     printf("%s\n", string2);
     printf("%s:, expected=%d, actual=%d\n",
             (expected == actual ? "PASSED" : "FAILED"),
             expected, actual);
 }

 void my_utf8_strcmpTestAll() {
     my_utf8_strcmpTest("\u00A3", "\u00A3", 1);
     my_utf8_strcmpTest("Hello", "\u00A3", -1);
     my_utf8_strcmpTest("🌍", "A", -1);
     my_utf8_strcmpTest("£", "£", 1);
 }

// ---------------------------------------------------------------------
// Byte Counter
void my_utf8_byteCounterTest(char *string1, char *string2, int expected){
    int actual = byteCounter(string1, string2);
    printf("%s\n", string1);
    printf("%s\n", string2);
    printf("%s:, expected=%d, actual=%d\n",
           (expected == actual ? "PASSED" : "FAILED"),
           expected, actual);
}

void my_utf8_byteCounterTestAll() {
    my_utf8_byteCounterTest("אריה", "אריה", 0);
    my_utf8_byteCounterTest("Hello 🌍", "Hello", 1);
    my_utf8_byteCounterTest("\u00A3", "\u00A3", 0);
    my_utf8_byteCounterTest("A", "\u20AC", 2);
}

// Byte Counter
void my_utf8_findMeTest(char *findChar, char *string, int expected){
    int actual = findMe(findChar, string);
    printf("%s\n", findChar);
    printf("%s\n", string);
    printf("%s:, expected=%d, actual=%d\n",
           (expected == actual ? "PASSED" : "FAILED"),
           expected, actual);
}

void my_utf8_findMeTestAll() {
    my_utf8_findMeTest("א", "אריה", 1);
    my_utf8_findMeTest("🌍", "Hello", -1);
    my_utf8_findMeTest("\u00A3", "\u00A3", 1);
    my_utf8_findMeTest("י", "חני", 1);
}

void main(){
    // my_utf8_checkTestAll();
    // my_utf8_strlenTestAll();
    // my_utf8_charatTestAll(); //issues
    // my_utf8_strcmpTestAll();
    // my_utf8_byteCounterTestAll();
    // my_utf8_findMeTestAll();


//    // Encode
//    char *input = "\u20AC";
//    char *output;
//    my_utf8_encode(input, output);
//    printf("Input: \n");
//    printf("%s\n", input);
//    printf("Output: \n");
//    printf("%s\n", output);

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

}
