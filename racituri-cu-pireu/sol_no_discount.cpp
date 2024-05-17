#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll MOD = 1e9 + 7;

ll lg_pow(ll a, int n) 
{
  ll ans = 1;
  while (n) {
    if (n & 1)
        ans = (ans * a) % MOD;
    n >>= 1;
    a = (a * a) % MOD;
  }
  return ans;
}

ll inv_mod(int a) 
{
  return lg_pow(a, MOD - 2);
}

int main()
{
  int R, P, X;
  cin >> R >> P >> X;

  vector <int> r(R);
  vector <int> p(P);

  for (int &x : r)
    cin >> x;

  for (int &x : p)
    cin >> x;

  ll sum = 0;
  for (int x : r)
    sum += x;
  for (int x : p)
    sum += x;

  cout << sum % MOD * inv_mod(2LL) % MOD;

  return 0;
}
