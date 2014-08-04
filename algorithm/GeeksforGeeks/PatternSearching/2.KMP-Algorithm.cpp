// http://www.geeksforgeeks.org/searching-for-patterns-set-2-kmp-algorithm/

// Given a text txt[0..n-1] and a pattern pat[0..m-1], write a function
// search(char pat[], char txt[]) that prints all occurrences of pat[] in txt[].
// You may assume that n > m.

// We have discussed Naive pattern searching algorithm in the previous post.
// The worst case complexity of Naive algorithm is O(m(n-m+1)). The Naive
// pattern searching algorithm doesn't work well in cases where we see many
// matching characters followed by a mismatching character. Time complexity
// of KMP algorithm is O(n) in worst case.

#include <stdio.h>
#include <string.h>


// For each sub-pattern pat[0...i] where i = 0 to m-1, it calculates the length
// of maximum matching proper prefix which is also a suffix of the sub-pattern
// pat[0..i] and stores the value in lps[i]. E.g.
// For the pattern "AABAACAABAA", lps[] is [0, 1, 0, 1, 2, 0, 1, 2, 3, 4, 5]
void computeLPSArray(char *pat, int m, int *lps) {

    // Length of the previous longest prefix suffix
    int len = 0;

    lps[0] = 0;
    // The loop calculates lps[i] for i = 1 to m-1
    for (int i = 1; i < m;) {
        if (pat[i] == pat[len]) {
            // If match, increment len and update lps, e.g. "ABCAB", when
            // i=3 ("ABCA"), len=1; since pat[3]==pat[1], so now the longest
            // prefix suffix length is 2 ("AB"=="AB").
            lps[i++] = ++len;
        } else {
            if (len != 0) {
                // This is tricky. Consider both the example "AAACAAAA", i = 7
                // and "AAACAAAB", i = 7.
                // Also, note that we do not increment i here
                len = lps[len-1];
            } else {
                // If pat[i], pat[len] didn't match and len == 0, we can
                // just set lps[i] to 0. There is no common part in prefix
                // and suffix. E.g. "ABCDE", when i=3 ("ABCD"), len=0, so
                // when i=4, pat[4]!=pat[0], we just set lps[4]=0.
                lps[i++] = 0;
            }
        }
    }
}


// Unlike the Naive algo where we slide the pattern by one, we use a value
// from lps[] to decide the next sliding position. Let us see how we do that.
// When we compare pat[j] with txt[i] and see a mismatch, we know that
// characters pat[0..j-1] match with txt[i-j+1...i-1], and we also know that
// lps[j-1] characters of pat[0...j-1] are both proper prefix and suffix which
// means we do not need to match these lps[j-1] characters with txt[i-j...i-1]
// because we know that these characters will anyway match.
void KMPsearch(char *txt, char *pat) {

    int m = strlen(pat);
    int n = strlen(txt);

    // Create lps[] that will hold the longest prefix suffix values for pattern
    int lps[m];
    int j = 0;

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, m, lps);
    // for (int i = 0; i < m; i++) {
    //     printf("%d ", lps[i]);
    // }
    // printf("\n");

    // Start matching. i,j is index for txt[] and pat[] respectively
    for (int i = 0; i < n;) {

        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == m) {
            printf("Found pattern at index %d \n", i-j);
            j = lps[j-1];
        } else if (pat[j] != txt[i]) {
            // Mismatch after j matches, do not match pat[0..lps[j-1]]
            // characters, they will match anyway.
            if (j != 0) {
                j = lps[j-1];
            } else {
                i++;
            }
        }
    }
}


/* Driver program to test above function */
int main()
{
    char txt[] = "AABAACAADAABAAABAA";
    char pat[] = "AAB";

    KMPsearch(txt, pat);
    return 0;
}
