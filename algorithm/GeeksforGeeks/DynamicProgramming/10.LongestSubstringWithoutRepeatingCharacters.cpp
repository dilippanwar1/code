// http://www.geeksforgeeks.org/length-of-the-longest-substring-without-repeating-characters/

// Given a string, find the length of the longest substring without repeating
// characters. For example, the longest substrings without repeating characters
// for "ABDEFGABEF" are "BDEFGA" and "DEFGAB", with length 6. For "BBBB" the
// longest substring is "B", with length 1. For "GEEKSFORGEEKS", there are two
// longest substrings shown in the below diagrams, with length 7.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NO_OF_CHARS 256


int longestUniqueSubstr(char *str)
{
    int n = strlen(str);
    int cur_len = 1;  // To store the lenght of current substring
    int max_len = 1;  // To store the result
    int prev_index;  // To store the previous index
    int i;
    int *visited = (int *)malloc(sizeof(int)*NO_OF_CHARS);

    /* Initialize the visited array as -1, -1 is used to indicate that
       character has not been visited yet. */
    for (i = 0; i < NO_OF_CHARS;  i++)
        visited[i] = -1;

    /* Mark first character as visited by storing the index of first
       character in visited array. */
    visited[str[0]] = 0;

    /* Start from the second character. First character is already processed
       (cur_len and max_len are initialized as 1, and visited[str[0]] is set */
    for (i = 1; i < n; i++)
    {
        prev_index =  visited[str[i]];

        /* If the currentt character is not present in the already processed
           substring or it is not part of the current NRCS, then do cur_len++ */
        if (prev_index == -1 || i - cur_len > prev_index)
            cur_len++;

        /* If the current character is present in currently considered NRCS,
           then update NRCS to start from the next character of previous instance. */
        else
        {
            /* Also, when we are changing the NRCS, we should also check whether
               length of the previous NRCS was greater than max_len or not.*/
            if (cur_len > max_len)
                max_len = cur_len;

            cur_len = i - prev_index;
        }

        visited[str[i]] = i; // update the index of current character
    }

    // Compare the length of last NRCS with max_len and update max_len if needed
    if (cur_len > max_len)
        max_len = cur_len;

    free(visited); // free memory allocated for visited

    return max_len;
}


class MySolution {
public:
    int longestUniqueSubstr(char *str) {

        // a simple hash table contains which character has been visited
        // the value of the table is the last position of the char in string
        int table[NO_OF_CHARS];
        int cur_len = 0;
        int max_len = 0;

        for (int i = 0; i < NO_OF_CHARS; i++) {
            table[i] = -1;
        }

        for (int i = 0; i < strlen(str); i++) {
            // haven't been visited before, or ** the character is outside
            // of current longest substring **, increase current length by 1
            if (table[str[i]] == -1 || table[str[i]] < i - cur_len) {
                cur_len++;
                table[str[i]] = i;
            } else {
                // current char has been visited before
                cur_len = i - table[str[i]];
                table[str[i]] = i;
            }
            if (cur_len > max_len) {
                max_len = cur_len;
            }
        }

        return max_len;
    }

    int longestUniqueSubstrEnhanced(char *str, int &start, int &finish) {

        // a simple hash table contains which character has been visited
        // the value of the table is the last position of the char in string
        int table[NO_OF_CHARS];
        int cur_len = 0;
        int max_len = 0;

        for (int i = 0; i < NO_OF_CHARS; i++) {
            table[i] = -1;
        }

        for (int i = 0; i < strlen(str); i++) {
            // haven't been visited before, or ** the character is outside
            // of current longest substring **, increase current length by 1
            if (table[str[i]] == -1 || table[str[i]] < i - cur_len) {
                cur_len++;
                table[str[i]] = i;
            } else {
                // current char has been visited before
                cur_len = i - table[str[i]];
                table[str[i]] = i;
            }
            if (cur_len > max_len) {
                max_len = cur_len;
                start = i - max_len + 1;
                finish = i;
            }
        }

        return max_len;
    }
private:
    int min(int a, int b) {
        return (a > b) ? b : a;
    }
};


/* Driver program to test above function */
int main() {

    MySolution solution;
    //char str[] = "ABDEFGABEF";
    char str[] = "GEEKSFORGEEKS";

    printf("The input string is %s\n", str);
    printf("The length of the longest non-repeating character "
           "substring is %d\n", solution.longestUniqueSubstr(str));

    int start, finish;
    printf("The length of the longest non-repeating character "
           "substring is %d\n",
           solution.longestUniqueSubstrEnhanced(str, start, finish));
    printf("Start: %d, End: %d\n", start, finish);

    return 0;
}
