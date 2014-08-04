// Implement strStr().

// Returns a pointer to the first occurrence of needle in haystack, or null if
// needle is not part of haystack.

#include <iostream>
using namespace std;


class Solution {
public:
    char *strStr(char *haystack, char *needle)
    {
        if (needle == NULL || !*needle)
            return haystack;
        if (strlen(haystack) < strlen(needle))
            return NULL;

        char *p1 = haystack, *p2 = needle;
        char *p1Adv = haystack;

        // we don't need to compare rest of `haystack` which is shorter than
        // `needle`
        while (*++p2)
            p1Adv++;

        while (*p1Adv) {
            char *p1Begin = p1;
            p2 = needle;
            while (*p1 && *p2 && *p1 == *p2) {
                p1++;
                p2++;
            }
            if (!*p2)
                return p1Begin;
            p1 = p1Begin + 1;
            p1Adv++;
        }

        return NULL;
    }
};


int main(int argc, char *argv[])
{
    Solution solution;

    cout << solution.strStr("I haha xe", "hah") << endl;
    return 0;
}
