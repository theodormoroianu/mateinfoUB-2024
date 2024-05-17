#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
  int v = stoi(argv[1]);
  int R = stoi(argv[2]);
  int P = stoi(argv[3]);
  int VMAX = stoi(argv[4]);
  int X = stoi(argv[5]);

  mt19937 rng(v);
  uniform_int_distribution <int> distr(1, VMAX);

  cout << R << ' ' << P << ' ' << X << '\n';

  for (int i = 0; i < R; i++)
    cout << distr(rng) << ' ';

  cout << '\n';

  for (int i = 0; i < P; i++) {
    int val = distr(rng);
    if (v / 10 == 4)
      val = val % 5 + 1;
    cout << val << ' ';
  }

  cout << '\n';
}
