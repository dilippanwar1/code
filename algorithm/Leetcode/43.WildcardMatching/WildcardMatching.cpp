// Implement wildcard pattern matching with support for '?' and '*'.

// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).

// The matching should cover the entire input string (not partial).

// The function prototype should be:
//    bool isMatch(const char *s, const char *p)

// Some examples:
// isMatch("aa","a") ? false
// isMatch("aa","aa") ? true
// isMatch("aaa","aa") ? false
// isMatch("aa", "*") ? true
// isMatch("aa", "a*") ? true
// isMatch("ab", "?*") ? true
// isMatch("aab", "c*a*b") ? false

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    // solution from web
    bool isMatch(const char *s, const char *p) {
        int n=strlen(s), m=strlen(p), i, j, chars=0;
        for(i=0; p[i]!='\0'; ++i) if(p[i]!='*' && n<++chars) return false;
        vector<bool> dp(n+2,false);
        for(i=m-1, dp[n]=true; i>=0; --i){
            if(p[i]=='*'){
                while(i>0 && p[i]==p[i-1]) --i; //skip multiple *
                for(j=n; j>=0 && !dp[j]; --j);
                for(; j>=0; --j) dp[j]=true;
            }else{
                for(j=0; j<n+1; ++j)
                    dp[j]=(p[i]==s[j] || p[i]=='?') ? dp[j+1] : false;
            }
        }
        return dp[0];
    }

    // Too slow
    bool isMatchSlow(const char *s, const char *p)
    {
        /* Base cases */
        // if we reach the end of both strings
        if (*s == '\0' && *p == '\0') {
            return true;
        }
        // make sure there are characters after * in s, in short, we don't
        // want * to match all characters. E.g. test("abc*c?d", "abcd");
        if (*s == '\0' && *p == '*' && *(p + 1) != '\0') {
            return false;
        }

        /* Matching */
        // if current character matches or ptern is '?', simply proceed
        if (*p == *s || *p == '?') {
            return isMatch(s + 1, p + 1);
        }

        // if ptern is '*', we have two choices
        if (*p == '*') {
            // use '*' or do not use '*'
            return isMatch(s, p + 1) || isMatch(s + 1, p);
        }

        return false;
    }
};


int main(int argc, char *argv[])
{
    Solution solution;

    cout << solution.isMatch("aa", "*") << endl;
    return 0;
}
