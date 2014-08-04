#include <iostream>
using namespace std;


class Point
{
public:
  Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

  Point operator+(Point &p) {
    Point sum(x + p.x, y + p.y);
    return sum;
  }

  // Must be friend
  friend ostream &operator<<(ostream &out, const Point &p) {
    out << "(" << p.x << ", " << p.y << ")";
    return out;
  }

private:
  double x, y;
};


int main(void)
{
  Point p1(1.0, -1.0);
  Point p2(-2.2, 2.3);

  cout << p1 + p2 << endl;
}
