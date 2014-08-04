// http://www.geeksforgeeks.org/given-a-string-find-its-first-non-repeating-character/

// Given a string, find the first non-repeating character in it. For example,
// if the input string is "GeeksforGeeks", then output should be 'f' and if
// input string is 'GeeksQuiz', then output should be 'G'.

#include <cstring>
#include <iostream>
using namespace std;


int firstNonRepeating(char *str)
{
    char arrays[256];

    // initialize array
    for (int i = 0; i < 256; i++) {
        arrays[i] = 0;
    }

    // create count array by looping through string
    for (int i = 0; i < strlen(str); i++) {
        arrays[str[i]]++;
    }

    // return first non-repeating character
    for (int i = 0; i < strlen(str); i++) {
        if (arrays[str[i]] == 1)
            return i;
    }

    return -1;
}


int firstNonRepeating2(char *str)
{
    struct countIndex {
        int count;
        int index;
    };

    int result = INT_MAX;
    countIndex arrays[256];

    // initialize array
    for (int i = 0; i < 256; i++) {
        arrays[i].count = 0;
        arrays[i].index = 0;
    }

    // create count array by looping through string
    for (int i = 0; i < strlen(str); i++) {
        arrays[str[i]].count++;
        if (arrays[str[i]].count == 1)
            arrays[str[i]].index = i;
    }

    // instead of looping string, we need only loop 256 times
    for (int i = 0; i < 256; i++) {
        if (arrays[i].count == 1 && arrays[i].index < result) {
            result = arrays[i].index;
        }
    }

    return result;
}



/* Driver program to test above function */
int main()
{
    char str[] = "geeksforgeeks";
    int index = firstNonRepeating2(str);

    if (index == -1) {
        printf("Either all characters are repeating or string is empty\n");
    } else {
        printf("First non-repeating character is %c\n", str[index]);
    }

    return 0;
}
