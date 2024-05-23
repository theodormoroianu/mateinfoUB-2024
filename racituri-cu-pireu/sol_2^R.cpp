/**
 * Author: Theodor Moroianu
 * Indented: ??
 * Complexity: 2^R * R
*/
#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000000007;
const int INV2 = (MOD + 1) / 2;

typedef long long i64;

int main()
{
  int R, P, X;
  cin >> R >> P >> X;

  assert(R <= 27 && P == 0);

  vector <int> racituri(R);
  for (auto &x : racituri)
    cin >> x;

  i64 answer_simple = 0, answer_reduced = 0;
  for (int mask = 0; mask < (1 << R); mask++) {
    int sum = 0;
    for (int i = 0; i < R; i++)
      if (mask & (1 << i))
        sum += racituri[i];
    if (sum <= X)
      answer_simple += sum;
    else
      answer_reduced += sum;
  }

  i64 answer = (answer_simple + answer_reduced % MOD * INV2) % MOD;
  for (int i = 1; i <= R; i++)
    answer = answer * INV2 % MOD;

  cout << answer << '\n';
  return 0;
}
