// Given an array and a fixed window size X, you have to find out the minimum
// value from every window. De-queue was not allowed. So I had to do it using
// 2 stacks.

#include <stack>
#include <vector>
#include <iostream>
using namespace std;


void test_stack(void);
void test_queue(void);

/*
 * A customized int stack which support constant time push, pop and get_min()
 * No error handling
 */
class Stack {
private:
    stack<int> stk;
    stack<int> mins;

public:
    void push(int val) {
        stk.push(val);
        if (mins.empty() || mins.top() >= val) {
            mins.push(val);
        }
    }

    void pop(void) {
        int val = stk.top();
        stk.pop();
        if (val == mins.top()) {
            mins.pop();
        }
    }

    int top(void) {
        return stk.top();
    }

    bool empty(void) {
        return stk.empty();
    }

    int get_min(void) {
        return mins.top();
    }

    void hook(void) {
        cout << stk.size() << endl;
        cout << mins.size() << endl;
    }
};



/*
 * A customized int queue which support constant time push, pop and get_min()
 * No error handling
 */
class Queue {
private:
    Stack stk1;
    Stack stk2;

public:
    void push_rear(int val) {
        stk1.push(val);
    }

    int pop_front(void) {

        if (stk2.empty()) {
            while (!stk1.empty()) {
                stk2.push(stk1.top());
                stk1.pop();
            }
        }

        int tmp = stk2.top();
        stk2.pop();
        return tmp;
    }

    bool empty(void) {
        return stk1.empty() && stk2.empty();
    }

    int get_min(void) {

        if (stk1.empty())
            return stk2.get_min();
        if (stk2.empty())
            return stk1.get_min();

        int min1 = stk1.get_min();
        int min2 = stk2.get_min();
        return min(min1, min2);
    }

    void hook(void) {
        stk1.hook();
        stk2.hook();
    }
};


// suppose k < n
vector<int> minEveryWindow(int numbers[], int n, int k) {

    int i;
    Queue queue;
    vector<int> result;

    for (i = 0; i < k; i++) {
        queue.push_rear(numbers[i]);
    }

    for (; i < n; i++) {
        result.push_back(queue.get_min());
        queue.pop_front();
        queue.push_rear(numbers[i]);
    }
    result.push_back(queue.get_min());

    return result;
}


int main(void) {

    int numbers[] = {8, 6, 3, 4, 7, 9, 7, 2, 8, 4, 8, 1};
    vector<int> result = minEveryWindow(numbers, sizeof(numbers)/sizeof(int), 4);

    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << " ";
    }
    cout << endl;

    return 0;
}




void test_stack(void) {

    Stack stk;

    stk.push(8);
    stk.push(6);
    stk.push(3);
    stk.push(3);
    stk.push(7);
    stk.push(2);
    stk.push(5);
    stk.push(4);

    while (!stk.empty()) {
        cout << stk.get_min() << " ";
        stk.pop();
    }
    cout << endl;

    stk.hook();
}


void test_queue(void) {

    Queue queue;

    queue.push_rear(3);
    queue.push_rear(6);
    queue.push_rear(8);
    queue.push_rear(4);
    queue.push_rear(5);
    queue.push_rear(9);

    while (!queue.empty()) {
        cout << "min: " << queue.get_min() << " ";
        cout << "val: " << queue.pop_front() << " ";
    }
    cout << endl;

    queue.hook();
}
