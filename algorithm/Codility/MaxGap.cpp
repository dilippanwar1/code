#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


int solution(vector<int> &A) {

  if (A.size() == 0 || A.size() == 1) {
    return 0;
  }

  int max_gap = 0;
  vector<int> copy(A);

  sort(copy.begin(), copy.end());

  for (int i = 0; i < copy.size()-1; i++) {
    int num = (copy[i] + copy[i+1]) / 2;
    int tmp = min(abs(copy[i]-num), abs(copy[i+1]-num));
    max_gap = max(max_gap, tmp);
  }

  return max_gap;
}

int print(vector<int> &A) {
  // print out content:
  cout << "vector contains:";
  for (vector<int>::iterator it = A.begin(); it != A.end(); ++it)
    cout << ' ' << *it;
  cout << '\n';
}

int main(void) {
  int myints[] = {10, 0, 8, 2, -1, 12, 11, 3};
  vector<int> myvector (myints, myints+8);

  cout << solution(myvector) << endl;

  print(myvector);
}
