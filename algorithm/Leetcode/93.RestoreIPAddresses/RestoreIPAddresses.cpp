// Given a string containing only digits, restore it by returning all possible
// valid IP address combinations.

// For example:
// Given "25525511135",
// return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)

// Given "010010"
// return ["0.10.0.10","0.100.1.0"]
// Note "0.1.0.010", "0.1.00.10", etc are not valid.

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        return restoreIpAddressesHelper(s, 3);
    }

private:
    vector<string> restoreIpAddressesHelper(string s, int dots) {

        vector<string> result;

        // base cases
        if (s.length() == 0) // if `s` is short, we end up with nothing before
            return result;   // `dots` becomes 0, e.g. "0000"

        if (dots == 0) {     // last part of ip address
            // note that "0.0.0.01" is not a valid ip address for this problem
            if (atoi(s.c_str()) > 255 || (s.length() > 1 && s[0] == '0')) {
                return result;
            } else {
                result.push_back(s);
                return result;
            }
        }

        for (int len = 1; len < 4; len++) {
            if (len > s.length())
                break;
            if (len > 1 && s[0] == '0') // same as base case, stop spit string
                break;
            string number = s.substr(0, len); // cut off current number
            int digits = atoi(number.c_str());
            if (digits <= 255) { // one possible valid conversion
                vector<string> tmp = restoreIpAddressesHelper(s.substr(len), dots-1);
                for (int i = 0; i < tmp.size(); i++) {
                    result.push_back(number + "." + tmp[i]);
                }
            }
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    vector<string> tmp = solution.restoreIpAddresses("391032");

    for (int i = 0; i < tmp.size(); i++) {
        cout << tmp[i] << endl;
    }

    return 0;
}
