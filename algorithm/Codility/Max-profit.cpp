// Best time to buy and sell stock I

#include <vector>
#include <iostream>
using namespace std;


int solution(const vector<int> &A) {

    int profit = 0, min_sofar = INT_MAX;

    for (int i = 0; i < A.size(); i++) {
        min_sofar = min(min_sofar, A[i]);
        profit = max(profit, A[i] - min_sofar);
    }

    return profit;
}


int main(void) {
    return 0;
}
