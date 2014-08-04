#include <iostream>
using namespace std;


int parse(const char *head, char *&p) {

    if (head == p)
        return (*p - '0');

    if (*p == '+') {
        p--;
        int a = parse(head, p);
        int b = parse(head, p);
        return a + b;
    }
    else if (*p == '-') {
        p--;
        int a = parse(head, p);
        int b = parse(head, p);
        return b - a;
    }
    else if (*p == '*') {
        p--;
        int a = parse(head, p);
        int b = parse(head, p);
        return a * b;
    }
    else if (*p == '/') {
        p--;
        int a = parse(head, p);
        int b = parse(head, p);
        return a / b;
    }

    else {
        int temp = *p--;
        return temp - '0';
    }
}


int main(int argc, char *argv[])
{
    char *head = "42+56-*7*";
    char *p = head;
    while (*p != '\0')
        p++;
    p--;

    cout << parse(head, p) << endl;
    return 0;
}
