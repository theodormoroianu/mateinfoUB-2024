#include <bits/stdc++.h>

using namespace std;

int main() 
{
  int n, m;
  cin >> n >> m;
  vector <int> v(n);
  for (int& x : v)
    cin >> x;

  int lo = 0, hi = 1e9, ans = -1;
  while (lo <= hi) {
    int mid = (lo + hi) / 2;
    int s = 0;
    for (int x : v)
      s += x / mid;
    if (s >= m) {
      ans = mid;
      lo = mid + 1;
    }
    else
      hi = mid - 1;
  }

  cout << ans << '\n';
  return 0;
}
