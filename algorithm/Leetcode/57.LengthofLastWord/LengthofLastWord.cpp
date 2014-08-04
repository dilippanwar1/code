// Given a string s consists of upper/lower-case alphabets and empty space
// characters ' ', return the length of last word in the string.

// If the last word does not exist, return 0.

// Note: A word is defined as a character sequence consists of non-space
// characters only.

// For example,
//    Given s = "Hello World",
//    Return 5.

#include <ctype.h>
#include <iostream>
using namespace std;


class Solution {
public:
    int lengthOfLastWord(const char *s) {

        int p = 0;
        int ret = 0;

        while (s[p] != '\0') {
            p++;
        }

        while (p >= 0 && !isalpha(s[p]))
            p--;

        while (p >= 0 && isalpha(s[p])) {
            p--;
            ret++;
        }

        return ret;
    }


    // elegent solution from web
    int lengthOfLastWord2(const char * s) {

        int r = 0;
        while (*s) {
            if (*(s++) != ' ')
                r++;
            else if (*s && *s != ' ')
                r = 0;
        }
        return r;
    }
};


int main(void) {

    Solution solution;
    cout << solution.lengthOfLastWord("") << endl;
    return 0;
}
