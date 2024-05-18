#include <bits/stdc++.h>

using namespace std;

int main()
{
  int a, b, x;
  cin >> a >> b >> x;
  if (b % 2 == 0)
    cout << "IMPOSIBIL";
  else {
    cout << 2 * (b / 2 + 1) << '\n';
    for (int i = 0; i <= b / 2; i++) {
      cout << "UMPLE A\n";
      cout << "VARSA A IN B\n";
    }
  }
  return 0;
}
