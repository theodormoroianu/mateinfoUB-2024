#include <bits/stdc++.h>
using namespace std;

int Gcd(int a, int b, int& x, int& y)
{
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }

  int x1, y1;
  int d = Gcd(b % a, a, x1, y1);

  // d = (b % a) * x1 + a * y1
  // d = (b - b / a * a) * x1 + a * y1
  // d = a * (y1 - b / a * x1) + b * x1
  x = y1 - b / a * x1;
  y = x1;
  return d;
}

int main()
{
  
  return 0;
}