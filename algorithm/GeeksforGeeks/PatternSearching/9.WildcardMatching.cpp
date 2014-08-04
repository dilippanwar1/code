// http://www.geeksforgeeks.org/wildcard-character-matching/

// Given two strings where first string may contain wild card characters and
// second string is a normal string. Write a function that returns true if
// the two strings match. The following are allowed wild card characters in
// first string.

// * --> Matches with 0 or more instances of any character or set of characters.
// ? --> Matches with any one character.
// For example, "g*ks" matches with "geeks" match. And string "ge?ks*" matches
// with "geeksforgeeks" (note '*' at the end of first string). But 'g*k' doesn't
// match with "gee" as character 'k' is not present in second string.
// Note '*' and '?' here has different meaning as opposed to regex.

#include <stdio.h>


bool match(char* pat, char *txt) {

    /* Base cases */
    // if we reach the end of both strings
    if (*txt == '\0' && *pat == '\0') {
        return true;
    }
    // make sure there are characters after * in txt, in short, we don't
    // want * to match all characters. E.g. test("abc*c?d", "abcd");
    if (*txt == '\0' && *pat == '*' && *(pat + 1) != '\0') {
        return false;
    }

    /* Matching */
    // if current character matches or pattern is '?', simply proceed
    if (*pat == *txt || *pat == '?') {
        return match(pat + 1, txt + 1);
    }

    // if pattern is '*', we have two choices
    if (*pat == '*') {
        // use '*' or do not use '*'
        return match(pat + 1, txt) || match(pat, txt + 1);
    }

    return false;
}


void test(char *first, char *second) {
    match(first, second)? puts("Yes"): puts("No");
}

// Driver program to test above functions
int main()
{
    test("g*ks", "geeks");           // Yes
    test("ge?ks*", "geeksforgeeks"); // Yes
    test("g*k", "gee");             // No because 'k' is not in second
    test("*pqrs", "pqrst");         // No because 't' is not in first
    test("abc*bcd", "abcdhghgbcd"); // Yes
    test("abc*c?d", "abcd"); // No because second must have 2 instances of 'c'
    test("*c*d", "abcd");    // Yes
    test("*?c*d", "abcd");   // Yes

    return 0;
}
