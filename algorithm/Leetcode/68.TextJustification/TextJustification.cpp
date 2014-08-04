// Given an array of words and a length L, format the text such that each line
// has exactly L characters and is fully (left and right) justified.

// You should pack your words in a greedy approach; that is, pack as many words
// as you can in each line. Pad extra spaces ' ' when necessary so that each
// line has exactly L characters.

// Extra spaces between words should be distributed as evenly as possible. If
// the number of spaces on a line do not divide evenly between words, the empty
// slots on the left will be assigned more spaces than the slots on the right.

// For the last line of text, it should be left justified and no extra space is
// inserted between words.

// For example,
//    words: ["This", "is", "an", "example", "of", "text", "justification."]
//    L: 16.
// Return the formatted lines as:
//    [
//       "This    is    an",
//       "example  of text",
//       "justification.  "
//    ]
// Note: Each word is guaranteed not to exceed L in length.

// Corner Cases:
// A line other than the last line might contain only one word. What should you
// do in this case? In this case, that line should be left-justified.

#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<string> fullJustify(vector<string> &words, int L)
    {
        vector<string> result;

        int begin = 0;          // beginning word of current line
        int len = 0;            // length of all words in current line

        for (int i = 0; i < words.size(); i++) {
            // check length of words plus spaces exceed line length limit
            if (len + words[i].length() + (i - begin) > L) {
                result.push_back(createLine(words, begin, i-1, L, len, false));
                begin = i;      // next line's starting word is `i`
                len = words[i].length(); // next line's len is length of words[i]
            } else {
                len += words[i].length();
            }
        }

        // last line
        result.push_back(createLine(words, begin, words.size()-1, L, len, true));

        return result;
    }

    string createLine(vector<string> &words, int begin, int end,
                      int L, int len, bool final)
    {
        string line;
        int count = end - begin + 1; // number of words in this line
        int space, extra;

        // figure out how many space we need after each word, take
        // care of special cases of last line and one word line
        if (final == true) {
            space = 1;
            extra = 0;
        } else if (count != 1) {
            space = (L - len) / (count - 1); // average space for each word
            extra = (L - len) % (count - 1); // extra space if not even
        } else {
            space = L - len;
            extra = 0;
        }

        for (int i = begin; i <= end; i++) {
            line += words[i];
            if (i != end) {  // we do not want add space for last word
                line.append(space, ' ');
                if (extra != 0) {
                    line.append(1, ' ');
                    extra--;
                }
            }
        }

        // for last line or one word line, we need to pad with space
        if (final == true || count == 1) {
            line.append(L - line.size(), ' '); // use line.size() to pad space
        }

        return line;
    }
};


int main(void) {

    Solution solution;
    vector<string> words;
    int L;

    // words.push_back("This");
    // words.push_back("is");
    // words.push_back("an");
    // words.push_back("example");
    // words.push_back("of");
    // words.push_back("text");
    // words.push_back("justification.");
    // L = 16;

    // words.push_back("Listen");
    // words.push_back("to");
    // words.push_back("many,");
    // words.push_back("speak");
    // words.push_back("to");
    // words.push_back("a");
    // words.push_back("few.");
    // L = 6;

    words.push_back("What");
    words.push_back("must");
    words.push_back("be");
    words.push_back("shall");
    words.push_back("be.");
    L = 12;


    vector<string> result = solution.fullJustify(words, L);
    for (int i = 0; i < result.size(); i++)
        cout << result[i] << endl;

    return 0;
}
