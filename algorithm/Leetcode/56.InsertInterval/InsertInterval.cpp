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
    vector<Interval> insert(vector<Interval> &intervals, Interval newInterval) {

        vector<Interval> result;

        int i = 0;
        int n = intervals.size();

        // find the start merge interval
        while (i < n && intervals[i].end < newInterval.start) {
            result.push_back(intervals[i++]);
        }
        if (i < n) {
            newInterval.start = min(newInterval.start, intervals[i].start);
        }

        // find the end merge interval
        while (i < n && newInterval.end >= intervals[i].start) {
            newInterval.end = max(newInterval.end, intervals[i].end);
            i++;
        }
        result.push_back(newInterval);

        // add all remaining part
        while (i < n) {
            result.push_back(intervals[i++]);
        }

        return result;
    }
};


int main(void) {

    Solution solution;
    vector<Interval> input;

    Interval interval1(1,2);
    Interval interval2(5,6);
    Interval interval3(10,12);
    Interval interval4(15,18);
    Interval interval5(20,22);

    Interval interval6(15,22);

    input.push_back(interval1);
    input.push_back(interval2);
    input.push_back(interval3);
    input.push_back(interval4);
    input.push_back(interval5);

    vector<Interval> result = solution.insert(input, interval6);

    // for (int i = 0; i < input.size(); i++) {
    //     cout << "[" << input[i].start << ", " << input[i].end << "]" << endl;
    // }

    for (int i = 0; i < result.size(); i++) {
        cout << "[" << result[i].start << ", " << result[i].end << "]" << endl;
    }

    return 0;
}
