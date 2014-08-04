// Given a String s and int c, first fill each character row wise and print
// column wise.

// for e.g. String s = "abcdefgh" and c = 3
// so filling column wise would give :
//   a d g
//   b e h
//   c f
// and final ans would be adgbehcf.
// he just wanted the exact output. Internally how we handle string was not
// concern.

#include <string>
#include <iostream>
using namespace std;


string columnWise(string s, int c) {

    string result(s.size(), ' ');
    int r = s.size() / c + 1;

    int index1 = 0;
    for (int j = 0; j < c; j++) {
        for (int i = 0; i < r; i++) {
            int index = i * c + j;
            if (index < s.length()) {
                result[index] = s[index1++];
            }
        }
    }

    return result;
}

int main(void) {

    cout << columnWise("abcdefgh", 3) << endl;
    return 0;
}
