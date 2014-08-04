#include <iostream>
using namespace std;


class Solution {
public:
    int trap(int A[], int n) {

        if (n == 0 || n == 1 || n == 2)
            return 0;

        int sum = 0;
        int leftMax[n], rightMax[n];
        leftMax[0] = A[0];
        rightMax[n-1] = A[n-1];

        for (int i = 1; i < n; i++)
            leftMax[i] = max(leftMax[i-1], A[i]);
        for (int i = n - 2; i >= 0; i--)
            rightMax[i] = max(rightMax[i+1], A[i]);

        for (int i = 1; i < n - 1; i++) {
            int boundary = min(leftMax[i], rightMax[i]);
            if (boundary > A[i])
                sum += boundary - A[i];
        }

        return sum;
    }
};


int main(void) {

    Solution solution;
    int A[] = {0,1,0,2,1,0,1,3,2,1,2};
    //int A[] = {2,1,0,1,3};
    cout << solution.trap(A, sizeof(A)/sizeof(A[0])) << endl;
    return 0;
}
