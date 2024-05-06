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

  vector <int> rame(N);
  for (auto& i : rame) {
    cin >> i;
  }

  auto CheckAnswer = [&](int l) {
    long long rez = 0;
    for (int i = 0; i < N; i++) {
      rez += rame[i] / l;
    }
    return rez >= M;
  };

  int answer = 0;
  while (CheckAnswer(answer + 1)) {
    answer++;
  }

  cout << answer << '\n';

  return 0;
}