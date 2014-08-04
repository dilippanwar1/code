#include <iostream>
using namespace std;


typedef enum days {
  SUN, MON, TUE, WED, THU, FRI, SAT
} days;


// prefix ++
inline days operator++(days d) {
  return static_cast<days>((static_cast<int>(d) + 1) % 7);
}

// suffix ++
inline days operator++(days d, int) {
  return static_cast<days>((static_cast<int>(d) + 1) % 7);
}

ostream& operator<<(ostream &out, days d) {
  switch (d) {
  case SUN: out << "SUN"; break;
  case MON: out << "MON"; break;
  case TUE: out << "TUE"; break;
  case WED: out << "WED"; break;
  case THU: out << "THU"; break;
  case FRI: out << "FRI"; break;
  case SAT: out << "SAT"; break;
  }
  return out;
}

int main(void) {
  days s = SUN;
  days m = s++;
  days t = ++m;
  cout << s << endl;
  cout << m << endl;
  cout << t << endl;
}
