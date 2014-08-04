// http://www.geeksforgeeks.org/searching-for-patterns-set-1-naive-pattern-searching/

// Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function
// search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[].
// You may assume that n > m.

// Examples:
// 1) Input:
//      txt[] = "THIS IS A TEST TEXT"
//      pat[] = "TEST"
//    Output:
//      Pattern found at index 10
// 2) Input:
//      txt[] = "AABAACAADAABAAABAA"
//      pat[] = "AABA"
//    Output:
//      Pattern found at index 0
//      Pattern found at index 9
//      Pattern found at index 13

// Pattern searching is an important problem in computer science. When we do
// search for a string in notepad/word file or browser or database, pattern
// searching algorithms are used to show the search results.

#include <stdio.h>
#include <string.h>


void search(char *txt, char *pat)
{
    int M = strlen(pat);
    int N = strlen(txt);

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++)
    {
        int j;

        /* For current index i, check for pattern match */
        for (j = 0; j < M; j++)
        {
            if (txt[i+j] != pat[j])
                break;
        }
        if (j == M)  // if pat[0...M-1] = txt[i, i+1, ...i+M-1]
        {
            printf("Pattern found at index %d \n", i);
        }
    }
}


class MySolution {
public:
    int searchNaive(char *txt, char *pat) {

        int n = strlen(txt);
        int m = strlen(pat);

        for (int i = 0; i <= n - m; i++) {
            // find head match
            if (txt[i] == pat[0]) {
                int txt_index = i;
                int pat_index = 0;
                for (pat_index = 0; pat_index < m; pat_index++, txt_index++) {
                    if (txt[txt_index] != pat[pat_index]) {
                        break;
                    }
                }
                if (pat_index == m) {
                    printf("Pattern matching at index %d\n", i);
                    // to avoid duplicate matching, e.g "AAA" and "AA", use
                    // i = i + m - 1;
                }
            }
        }
    }
};


/* Driver program to test above function */
int main()
{
    MySolution solution;
    char txt[] = "AABAACAADAABAAABAA";
    char pat[] = "AABA";

    search(txt, pat);
    solution.searchNaive(txt, pat);
    return 0;
}
