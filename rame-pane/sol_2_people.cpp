/**
 * Author:     Theodor Moroianu
 * Indented:   30
 * Complexity: N^2
*/

#include <bits/stdc++.h>
using namespace std;

int main()
{
  int N, M;
  cin >> N >> M;

  int max1 = 0, max2 = 0;

  while (N--) {
    int x;
    cin >> x;
    if (x > max1) {
      max2 = max1;
      max1 = x;
    } else if (x > max2) {
      max2 = x;
    }
  }

  cout << max(max2, max1 / 2) << '\n';

  return 0;
}