/**
 * Author: Theodor Moroianu
 * Indented: 100p
 * Complexity: (R + P) * [sum of values]
*/
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1'000'000'007;

int Put(int a, int p)
{
  int ans = 1;
  while (p) {
    if (p & 1)
      ans = 1LL * ans * a % MOD;
    a = 1LL * a * a % MOD;
    p >>= 1;
  }
  return ans;
}

void Add(int& a, int b)
{
  a += b;
  if (a >= MOD)
    a -= MOD;
  if (a < 0)
    a += MOD;
}

int main()
{
  int R, P, X;
  cin >> R >> P >> X;
  assert(R <= 100 && P <= 100 && X <= 200'000);

  vector <int> racituri(R), pireu(P);
  for (auto &x : racituri) {
    cin >> x;
    assert(x <= 1000);
  }
  for (auto &x : pireu) {
    cin >> x;
    assert(x <= 1000);
  }

  // int total_sum = accumulate(racituri.begin(), racituri.end(), 0) + accumulate(pireu.begin(), pireu.end(), 0);
  int total_sum = accumulate(racituri.begin(), racituri.end(), 0);
  vector <int> rucsac(total_sum + 1, 0);
  rucsac[0] = 1;

  for (auto r : racituri)
    for (int i = total_sum; i >= r; i--)
      Add(rucsac[i], rucsac[i - r]);

  // for (auto p : pireu) {
  //   vector <int> rucsac_sp = rucsac;
  //   for (int i = 1; i < (int)rucsac_sp.size(); i++)
  //     Add(rucsac_sp[i], rucsac_sp[i - 1]);
  //   
  //   for (int i = 1; i < (int)rucsac.size(); i++) {
  //     int from = max(0, i - p);
  //     rucsac[i] = (rucsac_sp[i] - (from ? rucsac_sp[from - 1] : 0) + MOD) % MOD;
  //   }
  // }

  int ans = 0;
  const int INV2 = Put(2, MOD - 2);
  for (int i = 1; i <= total_sum; i++) {
    int x = 1LL * rucsac[i] * i % MOD; 
    if (i > X)
      x = 1LL * x * INV2 % MOD;

    Add(ans, x);
  }

  int total_mods = Put(2, R);
  // for (auto i : pireu)
  //   total_mods = 1LL * total_mods * (i + 1) % MOD;

  ans = 1LL * ans * Put(total_mods, MOD - 2) % MOD;

  cout << ans << '\n';
  return 0;
}
