/**
 * Author:     Theodor Moroianu
 * Indented:   100
 * Complexity: N log(VMAX)
*/

#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1'000'000;
const int MMAX = 1'000'000;
const int RAMA_MAX = 1'000'000;

int main()
{
  int N, M;
  cin >> N >> M;

  assert(N <= NMAX);
  assert(M <= MMAX);

  vector <int> rame(N);
  for (auto& i : rame) {
    cin >> i;
    assert(i <= RAMA_MAX);
  }

  auto CheckAnswer = [&](int l) {
    long long rez = 0;
    for (int i = 0; i < N; i++) {
      rez += rame[i] / l;
    }
    return rez >= M;
  };

  int answer = 0;

  for (int pas = (1 << 20); pas; pas >>= 1) {
    if (answer + pas <= RAMA_MAX && CheckAnswer(answer + pas)) {
      answer += pas;
    }
  }

  assert(CheckAnswer(answer) && !CheckAnswer(answer + 1));

  cout << answer << '\n';

  return 0;
}