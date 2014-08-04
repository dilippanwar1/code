#include <iostream>
using namespace std;


template <typename T>
T sum(T data[], int size) {
  T acc = 0;
  for (int i = 0; i < size; i++)
    acc += data[i];
  return acc;
}


int main(int argc, char *argv[]) {
  int array1[] = {1,2 , 3};
  double array2[] = {2.3, 20.0};

  cout << sum(array1, 3) << endl;
  cout << sum(array2, 2) << endl;
  return 0;
}
