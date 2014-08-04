// Say you have an array for which the ith element is the price of a given
// stock on day i.

// Design an algorithm to find the maximum profit. You may complete at most
// two transactions.

// Note:
// You may not engage in multiple transactions at the same time (ie, you must
// sell the stock before you buy again).


#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:

    // First consider the case that when we are only allowed to make one
    // transaction. we can handle this easily with DP. If we move forward,
    // any new price we meet will only affect our history result by two ways:
    //    will it be so low that it beats our previous lowest price?
    //    will it be so high that we should instead sell on this time to gain
    //       a higher profit (than the history record)?
    // Similarly, we can move backward with the highest price and profit in record.
    // Either way would take O(n) time.
    // Now consider the two transaction case. Since there will be no overlaps,
    // we are actually dividing the whole time into two intervals.
    // We want to maximize the profit in each of them so the same method above
    // will apply here. We are actually trying to break the day at each time
    // instance, by adding the potential max profit before and after it together.
    // By recording history and future for each time point, we can again do this
    // within O(n) time.
    int maxProfit(vector<int> &prices) {

        // null check
        int len = prices.size();
        if (len == 0)
            return 0;

        int historyProfit[len];
        int futureProfit[len];
        int valley = prices[0];
        int peak = prices[len-1];
        int maxProfit = 0;

        for (int i = 0; i < len; i++) {
            historyProfit[i] = 0;
            futureProfit[i] = 0;
        }

        // forward, calculate max profit until this time
        for (int i = 0; i < len; i++) {
            valley = min(valley, prices[i]);
            if (i > 0) {
                historyProfit[i] = max(historyProfit[i-1], prices[i]-valley);
            }
        }

        // backward, calculate max profit from now, and the sum with history
        for (int i = len-1; i >= 0; i--) {
            peak = max(peak, prices[i]);
            if (i < len-1) {
                futureProfit[i] = max(futureProfit[i+1], peak-prices[i]);
            }
            maxProfit = max(maxProfit, historyProfit[i]+futureProfit[i]);
        }
        return maxProfit;
    }


    // Time Limit Exceeded
    int maxProfitSlow(vector<int> &prices) {

        if (prices.size() == 0 || prices.size() == 1)
            return 0;

        int max_profit = 0;
        for (int i = 1; i < prices.size(); i++) {
            max_profit = max(max_profit,
                             maxProfitOne(prices, 0, i) +
                             maxProfitOne(prices, i+1, prices.size()-1));
        }

        return max(max_profit, maxProfitOne(prices, 0, prices.size()-1));
    }

    int maxProfitOne(vector<int> &prices, int left, int right) {

        if (left == right)
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
    int a[] = {7,1,2,3,8,7,12,19};
    vector<int> prices(a, a+sizeof(a)/sizeof(a[0]));

    cout << solution.maxProfit(prices) << endl;
    return 0;
}
