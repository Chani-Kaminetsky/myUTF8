#include <stdio.h>
int stringComparer(char* stringA, char* stringB);
int main(void) 
{
    printf("%d\n", stringComparer("hello", "hello")); // should return 0
    printf("%d\n", stringComparer("hello", "world")); // should return 1
    printf("%d\n", stringComparer("world", "hello")); // should return 2
    return 0;
}

int stringComparer(char* stringA, char* stringB)
{
    while (*stringA != '\0' && *stringB != '\0') {
        if (*stringA < *stringB) {
        return 1;
        }
        else if (*stringA > *stringB) {
        return 2;
        }   

        stringA++;
        stringB++;

    }

    if (*stringA == '\0' && *stringB == '\0') {
        return 0;
    }
    if (*stringA == '\0') {
        return 1;
    }
    if (*stringB == '\0') {
        return 2;
    }
    return -1;
}