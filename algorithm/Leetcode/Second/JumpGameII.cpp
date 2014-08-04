class Solution {
public:
    int jump(int A[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int last_reach = 0;
        int max_reach = 0;
        int step = 0;

        for (int i = 0; i < n; i++) {
            if (last_reach < i) {
                last_reach = max_reach;
                max_reach = 0;
                step++;
            }
            max_reach = max(max_reach, i+A[i]);
        }

        return step;
    }
};

