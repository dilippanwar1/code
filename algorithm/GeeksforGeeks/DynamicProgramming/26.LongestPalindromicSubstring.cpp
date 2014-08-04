// http://www.geeksforgeeks.org/longest-palindrome-substring-set-1/

// Given a string, find the longest substring which is palindrome. For example,
// if the given string is “forgeeksskeegfor”, the output should be “geeksskeeg”.


#include <stdio.h>
#include <string.h>


// A utility function to print a substring str[low..high]
void printSubStr( char* str, int low, int high )
{
    for( int i = low; i <= high; ++i )
        printf("%c", str[i]);
    printf("\n");
}

// This function prints the longest palindrome substring of str[].
// It also returns the length of the longest palindrome
int longestPalSubstr( char *str )
{
    int n = strlen( str ); // get length of input string

    // table[i][j] will be false if substring str[i..j] is not palindrome.
    // Else table[i][j] will be true
    bool table[n][n];
    memset( table, 0, sizeof( table ) );

    // All substrings of length 1 are palindromes
    int maxLength = 1;
    for( int i = 0; i < n; ++i )
        table[i][i] = true;

    // check for sub-string of length 2.
    int start = 0;
    for( int i = 0; i < n-1; ++i )
    {
        if( str[i] == str[i+1] )
        {
            table[i][i+1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Check for lengths greater than 2. k is length of substring
    for( int k = 3; k <= n; ++k )
    {
        // Fix the starting index
        for( int i = 0; i < n - k + 1 ; ++i )
        {
            // Get the ending index of substring from starting index i and length k
            int j = i + k - 1;

            // checking for sub-string from ith index to jth index iff str[i+1]
            // to str[j-1] is a palindrome
            if( table[i+1][j-1] && str[i] == str[j] )
            {
                table[i][j] = true;

                if( k > maxLength )
                {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }

    printf("Longest palindrome substring is: ");
    printSubStr( str, start, start + maxLength - 1 );

    return maxLength; // return length of LPS
}

class MySolution {
public:
    int longestPalSubstr(char str[]) {

        int n = strlen(str);
        int table[n][n];

        for (int i = 0; i < n; i++) {
            table[i][i] = 1;    // every single character is palindrome
        }

        int max_len = 1;
        int start = 0;
        for (int cl = 2; cl <= n; cl++) {
            for (int i = 0; i < n - cl + 1; i++) {
                int j = i + cl - 1;
                if (cl == 2) {
                    if (str[i] == str[j]) {
                        table[i][j] = 2;
                        max_len = cl;
                    } else {
                        table[i][j] = 0;
                    }
                } else {
                    if (str[i] == str[j]) {
                        table[i][j] = table[i+1][j-1] + 2;
                        if (table[i][j] > max_len) {
                            max_len = table[i][j];
                            start = i;
                        }
                    } else {
                        table[i][j] = 0;
                    }
                }
            }
        }

        printf("Longest palindrome substring is: ");
        printSubStr(str, start, start + max_len - 1);
        return max_len;
    }

private:
    void printSubStr( char* str, int low, int high )
    {
        for( int i = low; i <= high; ++i )
            printf("%c", str[i]);
        printf("\n");
    }
};

// Driver program to test above functions
int main()
{
    MySolution solution;
    char str[] = "forgeoeifjwoeksskeegfor";
    printf("Length is: %d\n", longestPalSubstr(str));
    printf("Length is: %d\n", solution.longestPalSubstr(str));
    return 0;
}
