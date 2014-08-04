// Say you have an array for which the ith element is the price of a given
// stock on day i.

// Design an algorithm to find the maximum profit. You may complete as many
// transactions as you like (ie, buy one and sell one share of the stock
// multiple times). However, you may not engage in multiple transactions at
// the same time (ie, you must sell the stock before you buy again).

#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    int maxProfit(vector<int> &prices) {

        if (prices.size() == 0 || prices.size() == 1)
            return 0;

        // basic idear, sell stock when it goes low
        int max_profit = 0, min_sofar = prices[0], current = 0;
        for (int i = 1; i < prices.size(); i++) {
            min_sofar = min(min_sofar, prices[i]); // still keep min price
            if (prices[i] - min_sofar < current) { // time to sell stock
                max_profit += current;
                min_sofar = prices[i]; // start over
                current = 0;
            } else {
                current = prices[i] - min_sofar;
            }
        }

        if (current != 0)       // remember last one
            max_profit += current;

        return max_profit;
    }

    // Time Limit Exceeded
    int maxProfitSlow(vector<int> &prices) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        if (prices.size() == 0 || prices.size() == 1)
            return 0;

        int n = prices.size();
        int **cache = new int *[n];
        for (int i = 0; i < n; i++) {
            cache[i] = new int[n];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cache[i][j] = -1;
            }
        }
        return maxProfitHelper(prices, 0, prices.size()-1, cache);
    }

    int maxProfitHelper(vector<int> &prices, int left, int right, int **cache) {

        if (left == right)
            return 0;
        if (cache[left][right] != -1) {
            return cache[left][right];
        }

        int max_current = 0;
        for (int i = left + 1; i < right; i++) {
            max_current = max(max_current,
                              maxProfitHelper(prices, left, i, cache) +
                              maxProfitHelper(prices, i+1, right, cache));
        }

        cache[left][right] = max(max_current, maxProfitOne(prices, left, right));
        return cache[left][right];
    }

    int maxProfitOne(vector<int> &prices, int left, int right) {

        if (prices.size() == 0 || prices.size() == 1)
            return 0;

        int max_profit = INT_MIN, min_sofar = prices[left];
        for (int i = left + 1; i <= right; i++) {
            min_sofar = min(min_sofar, prices[i]); // keep minimal buy price
            max_profit = max(max_profit, prices[i] - min_sofar);
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
    int a[] = {4, 8, 6, 7, 18, 19};
    // int a[] = {2,3,4,8,9,3,4};
    vector<int> prices(a, a+sizeof(a)/sizeof(a[0]));

    cout << solution.maxProfit(prices) << endl;
    return 0;
}
