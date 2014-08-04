// http://www.geeksforgeeks.org/dynamic-programming-set-32-word-break-problem/

// Given an input string and a dictionary of words, find out if the input string
// can be segmented into a space-separated sequence of dictionary words. See
// following examples for more details.
// This is a famous Google interview question, also being asked by many other
// companies now a days.

// Consider the following dictionary
// { i, like, sam, sung, samsung, mobile, ice, cream, icecream, man, go, mango}

// Input:  ilike
// Output: Yes
// The string can be segmented as "i like".

// Input:  ilikesamsung
// Output: Yes
// The string can be segmented as "i like samsung" or "i like sam sung".

// The above solutions only finds out whether a given string can be segmented
// or not. Extend the above Dynamic Programming solution to print all possible
// partitions of input string. See extended recursive solution for reference.

#include <string>
#include <iostream>
using namespace std;


class MySolution {
public:
    bool wordBreak(string str) {

        if (dictionaryContains(str)) {
            return true;
        } else if (str.length() == 0) {
            return true;
        }

        for (int len = 1; len <= str.length(); len++) {
            string word = str.substr(0, len);
            if (dictionaryContains(word)) {
                if (wordBreak(str.substr(len, str.length())) == true) {
                    return true;
                }
            }
        }

        return false;
    }

    bool wordBreakDP(string str) {

        int size = str.size();
        if (size == 0) {
            return true;
        }

        // Create the DP table to store results of subroblems. The value
        // table[i] will be true if str[0..i-1] can be segmented into
        // dictionary words, otherwise false.
        bool table[size+1];
        for (int i = 0; i <= size; i++) {
            table[i] = false;
        }

        for (int cl = 1; cl <= size; cl++) { // prefix length

            // If table[i] is false, then check if current prefix can make
            // it true. If it is already true, proceed.
            if (table[cl] == false && dictionaryContains(str.substr(0, cl))) {
                table[cl] = true;
            }

            // table[i] is true, then check for all substrings starting from
            // (i+1)th character and store their results.
            if (table[cl] == true) {

                if (cl == size) {
                    return true; // reach the end, last prefix
                }

                // Update table[j] if it is false and can be updated
                // Note the parameter passed to dictionaryContains() is
                // substring starting from index 'cl' and length 'j-cl'
                for (int i = cl + 1; i <= size; i++) {
                    if (table[i] == false &&
                        dictionaryContains(str.substr(cl, i - cl))) {
                        table[i] = true;
                    }

                    // If we reach the last character
                    if (i == size && table[i] == true)
                        return true;
                }
            }
        }

        return false;
    }
private:
    /* A utility function to check whether a word is present in dictionary or not.
       An array of strings is used for dictionary.  Using array of strings for
       dictionary is definitely not a good idea. We have used for simplicity of
       the program. */
    bool dictionaryContains(string word) {

        string dictionary[] = {"mobile","samsung","sam","sung","man","mango",
                               "icecream","and","go","i","like","ice","cream"};
        int size = sizeof(dictionary)/sizeof(dictionary[0]);

        for (int i = 0; i < size; i++) {
            if (dictionary[i].compare(word) == 0) {
                return true;
            }
        }
        return false;
    }

};


// Driver program to test above functions
int main()
{
    MySolution solution;

    solution.wordBreak("ilikesamsung")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreak("iiiiiiii")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreak("")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreak("ilikelikeimangoiii")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreak("samsungandmango")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreak("samsungandmangok")? cout <<"Yes\n": cout << "No\n";

    cout << endl;
    solution.wordBreakDP("ilikesamsung")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreakDP("iiiiiiii")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreakDP("")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreakDP("ilikelikeimangoiii")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreakDP("samsungandmango")? cout <<"Yes\n": cout << "No\n";
    solution.wordBreakDP("samsungandmangok")? cout <<"Yes\n": cout << "No\n";

    return 0;
}
