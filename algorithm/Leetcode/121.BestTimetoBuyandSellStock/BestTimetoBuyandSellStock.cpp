// Say you have an array for which the ith element is the price of a given
// stock on day i.

// If you were only permitted to complete at most one transaction (ie, buy one
// and sell one share of the stock), design an algorithm to find the maximum
// profit.

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    int maxProfit(vector<int> &prices) {

        if (prices.size() == 0 || prices.size() == 1)
            return 0;

        int max_profit = INT_MIN, min_sofar = prices[0];
        for (int i = 1; i < prices.size(); i++) {
            min_sofar = min(min_sofar, prices[i]); // keep minimal buy price
            max_profit = max(max_profit, prices[i] - min_sofar);
        }

        return max_profit;
    }

    int maxProfitNaive(vector<int> &prices) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        if (prices.size() == 0 || prices.size() == 1)
            return 0;

        int max_profit = 0;
        for (int i = 0; i < prices.size(); i++) {
            for (int j = i + 1; j < prices.size(); j++) {
                if (prices[j] - prices[i] > max_profit) {
                    max_profit = prices[j] - prices[i];
                }
            }
        }

        return max_profit;
    }

private:
    int max(int a, int b) {
        return a > b ? a : b;
    }

    int min(int a, int b) {
        return a < b ? a : b;
    }

    int abs(int a) {
        return a > 0 ? a : -a;
    }
};


int main(void) {

    Solution solution;
    int a[] = {2,3,4,8,9,3,4};
    vector<int> prices(a, a+sizeof(a)/sizeof(a[0]));

    cout << solution.maxProfitNaive(prices) << endl;
    cout << solution.maxProfit(prices) << endl;
    return 0;
}
