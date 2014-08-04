
#include <iostream>
using namespace std;


class Solution {
public:
    // Use A[i] to store i+1
    int firstMissingPositive(int A[], int n) {

        int i = 0;
        while (i < n) {
            if (A[i] > 0 && A[i] <= n && A[i] != i+1 && A[A[i]-1] != A[i]) {
                int tmp = A[i]; // swap A[i], A[A[i]-1]
                A[i] = A[tmp-1];
                A[tmp-1] = tmp;
            } else {
                i++;
            }
        }

        for (int i = 0; i < n; i++) {
            if (A[i] != i+1)
                return i+1;
        }

        return n;
    }
};


int main(void) {

    Solution solution;
    int A[] = {-1,1,3,4};
    //int A[] = {1,2,0};
    //int A[] = {1,1};
    cout << solution.firstMissingPositive(A, sizeof(A)/sizeof(A[0])) << endl;
    return 0;
}
