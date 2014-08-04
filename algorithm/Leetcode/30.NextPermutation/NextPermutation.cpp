// Implement next permutation, which rearranges numbers into the lexicographically
// next greater permutation of numbers.

// If such arrangement is not possible, it must rearrange it as the lowest possible
// order (ie, sorted in ascending order).

// The replacement must be in-place, do not allocate extra memory.

// Here are some examples. Inputs are in the left-hand column and its corresponding
// outputs are in the right-hand column.
// 1,2,3 -> 1,3,2
// 3,2,1 -> 1,2,3
// 1,1,5 -> 1,5,1

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    void nextPermutation(vector<int> &num) {

        if (num.size() == 0 || num.size() == 1)
            return;

        // find decreasing sequence from last, and reverse it (note use
        // >= instead of >)
        int current = num.size() - 2;
        while (current >= 0 && num[current] >= num[current+1])
            current--;
        reverse(num, current + 1, num.size() - 1);

        // if it's not all decreasing, we need to find the right position
        // for `current` and swap. e.g. [2,3,1]
        if (current >= 0) {
            int temp = current + 1;
            while (num[current] >= num[temp])
                temp++;
            swap(num, current, temp);
        }
    }

    void reverse(vector<int> &num, int i, int j) {

        while (i < j) {
            swap(num, i++, j--);
        }
    }

    void swap(vector<int> &num, int i, int j) {
            int tmp = num[i];
            num[i] = num[j];
            num[j] = tmp;
    }
};


int main(void) {

    Solution solution;
    //int a[] = {2,1};
    //int a[] = {4,5,6,9,8,7};
    int a[] = {2,2,7,5,4,3,2,2,1};
    //int a[] = {2,3,1};
    vector<int> input(a, a+sizeof(a)/sizeof(a[0]));

    solution.nextPermutation(input);

    for (int i = 0; i < input.size(); i++) {
        cout << input[i] << " ";
    }
    cout << endl;

    return 0;
}
