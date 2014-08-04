// A zero-indexed array A consisting of N integers is given. An equilibrium
// index of this array is any integer P such that 0 <= P < N and the sum of
// elements of lower indices is equal to the sum of elements of higher indices,
// i.e. A[0] + A[1] + ... + A[P-1] = A[P+1] + ... + A[N-2] + A[N-1].
// Sum of zero elements is assumed to be equal to 0. This can happen if P = 0
// or if P = N−1.

// Write a function
//   int solution(int A[], int N);
// that, given a zero-indexed array A consisting of N integers, returns any of
// its equilibrium indices. The function should return −1 if no equilibrium
// index exists.
// Assume that:
//   N is an integer within the range [0..10,000,000];
//   each element of array A is an integer within the range
//     [-2,147,483,648..2,147,483,647].

// Complexity:
//   expected worst-case time complexity is O(N);
//   expected worst-case space complexity is O(N), beyond input storage (not
//     counting the storage required for input arguments).

// Elements of input arrays can be modified.


#include <vector>
#include <algorithm>
using namespace std;


int solution(const vector<int> &A) {

    // use long long to avoid overflow
    long long sum = 0, left_sum = 0, right_sum = 0;
    for (int i = 0; i < A.size(); i++)
        sum += A[i];

    for (int i = 0; i < A.size(); i++) {
        right_sum = sum - left_sum - A[i]; // exclude current value
        if (left_sum == right_sum)
            return i;
        else
            left_sum += A[i];
    }

    return -1;
}


int main(void) {
    return 0;
}
