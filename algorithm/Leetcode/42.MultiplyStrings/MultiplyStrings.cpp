// Given two numbers represented as strings, return multiplication of the
// numbers as a string.

// Note: The numbers can be arbitrarily large and are non-negative.

#include <string>
#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    // better solution from web
    string multiply(string num1, string num2) {

        // `n` is the size of result string
        int n1 = num1.size(), n2 = num2.size(), n = n1 + n2;

        if (n1 == 0 || n2 == 0)
            return "0";
        if (num1[0] == '0' || num2[0] == '0')
            return "0";

        vector<int> res(n, 0);
        string result(n, '0');

        for (int i = 0; i < n1; i++){
            for (int j = 0; j < n2; j++){
                res[i+j+1] += (num1[i]-'0') * (num2[j]-'0');
            }
        }

        for (int i = n-1; i > 0; i--){
            if (res[i] > 9)     // carry
                res[i-1] += res[i] / 10;
            result[i] += res[i] % 10; // note that result elements are '0'
        }

        result[0] += res[0];
        return result[0]=='0' ? string(result.begin()+1, result.end()) : result;
    }

    // fail for very large num1 * num2, since `total` overflow
    string multiply2(string num1, string num2) {

        int n1 = num1.length() - 1, n2 = num2.length() - 1;

        if (n1 < 0 || n2 < 0)
            return "";

        vector<string> result;
        int carry = 0;
        for (int i = n1, digit = 1; i >= 0; i--, digit *= 10) {
            string res;
            for (int j = n2; j >= 0; j--) {
                int total = carry;
                total += (num1[i] - '0') * (num2[j] - '0') * digit;
                carry = total / 10;
                res.insert(0, 1, total%10 + '0');
            }
            while (carry != 0) {
                res.insert(0, 1, carry%10 + '0');
                carry = carry/10;
            }
            result.push_back(res);
        }

        // cout << "size: " << result.size() << endl;
        // for (int i = 0; i < result.size(); i++)
        //     cout << result[i] << endl;

        while (result.size() != 1) {
            string res;
            string s1 = result.back(); result.pop_back();
            string s2 = result.back(); result.pop_back();
            int n1 = s1.length()-1, n2 = s2.length()-1;
            int carry = 0;
            while (n1 >= 0 || n2 >= 0 || carry > 0) {
                int total = carry;
                total += (n1 >= 0) ? s1[n1]-'0' : 0;
                total += (n2 >= 0) ? s2[n2]-'0' : 0;
                carry = total / 10;
                res.insert(0, 1, total%10 + '0');
                n1--; n2--;
            }
            result.push_back(res);
        }

        // handle all 0s
        string ret = result[0];
        int count = 0;
        for (int i = 0; i < ret.length(); i++)
            if (ret[i] == '0')
                count++;
        if (count == ret.length())
            return "0";

        return ret;
    }
};


int main(void) {

    Solution solution;
    // cout << solution.multiply("12", "9") << endl;
    // cout << solution.multiply("9", "12") << endl;
    // cout << solution.multiply("12", "22") << endl;
    // cout << solution.multiply("0", "10200") << endl;
    cout << solution.multiply("47", "21") << endl;
    return 0;
}
