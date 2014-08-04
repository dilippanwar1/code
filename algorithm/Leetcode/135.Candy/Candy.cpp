// There are N children standing in a line. Each child is assigned a rating
// value.  You are giving candies to these children subjected to the following
// requirements:

// Each child must have at least one candy.
// Children with a higher rating get more candies than their neighbors.
// What is the minimum candies you must give?

// Note that when children have same rating, then don't need to have same candies.


#include <vector>
#include <iostream>
using namespace std;


class Solution {
public:
    int candy(vector<int> &ratings) {

        // init sum to 0, and every child has one candy
        int sum = 0;
        vector<int> candies(ratings.size(), 1);

        // scan from left to right, make sure that current child has more candy
        // than left neighbor
        for (int i = 1; i < ratings.size(); i++) {
            if (ratings[i] > ratings[i-1]) {
                candies[i] = candies[i-1] + 1;
            }
        }

        // scan from right to left, make sure that current child has more candy
        // than right neighbor
        for (int i = ratings.size() - 2; i >= 0; i--) {
            if (ratings[i] > ratings[i+1]) {
                candies[i] = max(candies[i], candies[i+1] + 1);
            }
        }

        // sum them all
        for (int i = 0; i < ratings.size(); i++) {
            sum += candies[i];
        }

        return sum;
    }
};


int main(void) {

    Solution solution;
    //int ratings[] = {5, 6, 2, 3, 7, 9, 4, 2};
    int ratings[] = {2,2,1};
    vector<int> input1(ratings , ratings+sizeof(ratings)/sizeof(int));

    cout << solution.candy(input1) << endl;

    return 0;
}
