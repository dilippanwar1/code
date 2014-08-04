// Given a number represented as an array of digits, plus one to the number.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<int> plusOne(vector<int> &digits) {

        vector<int> result(digits.size());
        int carry = 1, i = digits.size() - 1;
        for (int i = 0; i < digits.size(); i++)
            result[i] = digits[i];

        while (carry != 0 && i >= 0) {
            result[i] += 1;
            if (result[i] > 9) {
                result[i] = 0;
            } else {
                carry = 0;
            }
            i--;
        }
        // ......999...... case
        if (carry == 1) {
            result.resize(digits.size() + 1);
            for (int i = result.size() - 1; i > 0; i--)
                digits[i] = digits[i-1];
            result[0] = 1;
        }
        return result;
    }
};


int find(const vector<int> &A)
{
    int count = 0;
    int current = 0;
    bool visited[A.size()];

    visited[0] = true;
    for (int i = 1; i < A.size(); i++)
        visited[i] = false;

    for (int i = 0; i < A.size(); i++) {
        if (current + A[current] >= 0 && current + A[current] < A.size()) {
            visited[current + A[current]] = true;
            current = current + A[current];
        } else {
            break;
        }
    }

    for (int i = 0; i < A.size(); i++) {
        if (visited[i] == false)
            count++;
    }

    return count;
}


int main(void) {

    Solution solution;
    //int a[] = {3,-5,0,-1,-3};
    vector<int> num(a, a+sizeof(a)/sizeof(a[0]));

    vector<int> res = solution.plusOne(num);
    for (int j = 0; j < res.size(); j++) {
        cout << res[j] << " ";
    }
    cout << endl;

    cout << find(num) << endl;

    return 0;
}
