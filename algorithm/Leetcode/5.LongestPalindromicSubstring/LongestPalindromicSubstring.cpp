// Given a string S, find the longest palindromic substring in S. You may
// assume that the maximum length of S is 1000, and there exists one unique
// longest palindromic substring.

#include <iostream>
#include <string>
using namespace std;


class Solution {
public:
    // O(N^2) time complexity and O(N^2) space complexity
    string longestPalindrome(string s) {

        int len = s.length();
        // table[i][j] means whether string s[i...j] is palindrome
        bool table[len][len];
        int left = 0, right = 0, max_len = 1;

        // initialize table array
        for (int i = 0; i < len; i++) {
            for (int j = 0; j < len; j++) {
                if (i == j) {   // only one character
                    table[i][j] = true;
                } else if (j == i + 1 && s[i] == s[i+1]) {
                    table[i][j] = true; // two characters
                    left = i; right = j; max_len = 2;
                } else {
                    table[i][j] = false;
                }
            }
        }

        for (int cl = 3; cl <= len; cl++) {
            for (int i = 0; i < len - cl + 1 ; i++) {
                int j = i + cl - 1;
                if (j < len && s[i] == s[j] && table[i+1][j-1] == true) {
                    table[i][j] = true; // set to true
                    if (j - i + 1 > max_len) {
                        left = i; right = j; max_len = j - i + 1;
                    }
                }
            }
        }

        return s.substr(left, right - left + 1);
    }

    // O(N^2) time complexity and O(1) space complexity
    string longestPalindromeSimple(string s) {

        int n = s.length();

        if (n == 0)
            return "";
        string longest = s.substr(0, 1);  // a single char itself is a palindrome

        for (int i = 0; i < n-1; i++) {

            string p1 = expandAroundCenter(s, i, i); // for 'aba' case
            if (p1.length() > longest.length())
                longest = p1;

            string p2 = expandAroundCenter(s, i, i+1); // for 'abba' case
            if (p2.length() > longest.length())
                longest = p2;
        }

        return longest;
    }

    string expandAroundCenter(string s, int c1, int c2) {
        int l = c1, r = c2;
        int n = s.length();
        while (l >= 0 && r <= n-1 && s[l] == s[r]) {
            l--;
            r++;
        }
        return s.substr(l+1, r-l-1);
    }
};


int main(void) {

    Solution solution;
    string a("banana");

    cout << solution.longestPalindrome(a) << endl;
}
