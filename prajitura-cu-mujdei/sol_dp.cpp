/**
 * Author: Theodor Moroianu
 * Intended: ??
 * Complexity: O(A * B)
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int A, B, D;
  cin >> A >> B >> D;

  if (D % __gcd(A, B) != 0) {
    cout << "IMPOSIBIL\n";
    return 0;
  }

  vector<vector<tuple <int, int, string>>> dp(
    A + 1,
    vector<tuple <int, int, string>>(B + 1, { -1, -1, "" })
  );

  auto ApplyMove = [&](int a, int b, int move) -> pair <pair <int, int>, string> {
    switch (move) {
      case 0:
        return { { 0, b }, "GOLESTE A" };
      case 1:
      return { { a, 0 }, "GOLESTE B" };
      case 2:
      return { { A, b }, "UMPLE A" };
      case 3:
      return { { a, B }, "UMPLE B" };
      case 4:
      {
        int mv = min(a, B - b);
        return { { a - mv, b + mv }, "VARSA A IN B" };
      }
      case 5:
      {
        int mv = min(A - a, b);
        return { { a + mv, b - mv }, "VARSA B IN A" };
      }
    }
    assert(false);
  };

  dp[0][0] = { 0, 0, "" };
  vector <pair <int, int>> q = { { 0, 0 } };
  for (int t = 0; t < (int)q.size(); t++) {
    auto [a, b] = q[t];
    for (int mv = 0; mv < 6; mv++) {
      auto [new_poz, name] = ApplyMove(a, b, mv);
      auto [na, nb] = new_poz;

      if (get<0>(dp[na][nb]) == -1) {
        dp[na][nb] = { a, b, name };
        q.push_back({ na, nb });
      }
    }
  }

  vector <string> operations;
  int a = -1, b = -1;

  for (int i = 0; i <= A; i++)
    for (int j = 0; j <= B; j++)
      if (get<0>(dp[i][j]) != -1 && (i == D || j == D))
        a = i, b = j;

  if (a == -1) {
    cout << "IMPOSIBIL\n";
    return 0;
  }

  while (a != 0 || b != 0) {
    auto [na, nb, name] = dp[a][b];
    operations.push_back(name);
    a = na, b = nb;
  }

  reverse(operations.begin(), operations.end());
  cout << operations.size() << '\n';
  for (auto& op : operations)
    cout << op << '\n';

  return 0;
}