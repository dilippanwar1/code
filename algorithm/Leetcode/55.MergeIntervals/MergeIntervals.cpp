#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


struct Interval {
    int start;
    int end;
    Interval() : start(0), end(0) {}
    Interval(int s, int e) : start(s), end(e) {}
};



class Solution {
public:
    vector<Interval> merge(vector<Interval> &intervals) {

        vector<Interval> result;

        if (intervals.size() == 0)
            return result;

        sort(intervals.begin(), intervals.end(), sortByStart);
        result.push_back(intervals[0]);

        for (int i = 0, j = 1; j < intervals.size(); j++) {
            if (result[i].end >= intervals[j].start) {
                result[i].end = max(result[i].end, intervals[j].end);
            } else {
                result.push_back(intervals[j]);
                i++;
            }
        }

        return result;
    }

private:
    static bool sortByStart(const Interval &interval1, const Interval &interval2) {
        return interval1.start < interval2.start;
    }
};


int main(void) {

    Solution solution;
    vector<Interval> input;

    Interval interval1(1,4);
    Interval interval2(0,4);
    // Interval interval3(8,10);
    // Interval interval4(15,18);

    input.push_back(interval1);
    input.push_back(interval2);
    // input.push_back(interval3);
    // input.push_back(interval4);

    vector<Interval> result = solution.merge(input);

    // for (int i = 0; i < input.size(); i++) {
    //     cout << "[" << input[i].start << ", " << input[i].end << "]" << endl;
    // }

    for (int i = 0; i < result.size(); i++) {
        cout << "[" << result[i].start << ", " << result[i].end << "]" << endl;
    }
    return 0;

}
