// Given a string, determine if it is a palindrome, considering only alphanumeric
// characters and ignoring cases.

// For example,
//    "A man, a plan, a canal: Panama" is a palindrome.
//    "race a car" is not a palindrome.

// Note:
// Have you consider that the string might be empty? This is a good question to
// ask during an interview.
// For the purpose of this problem, we define empty string as valid palindrome.

#include <string>
#include <cctype>
#include <iostream>
using namespace std;


class Solution {
public:
    bool isPalindrome(string s) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int left = 0, right = s.length();

        while (left < right) {
            if (!isalnum(s[left])) {
                left++;
            } else if (!isalnum(s[right])) {
                right--;
            } else if (tolower(s[left]) != tolower(s[right])) {
                return false;
            } else {
                left++;
                right--;
            }
        }

        return true;
    }
};


int main(void) {
    Solution solution;
    cout << solution.isPalindrome(".,") << endl;
    return 0;
}
