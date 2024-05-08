#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
  int R = stoi(argv[1]);
  int P = stoi(argv[2]);
  int VMAX = stoi(argv[3]);
  int X = stoi(argv[4]);

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
  uniform_int_distribution <int> distr(1, VMAX);

  cout << R << ' ' << P << ' ' << X << '\n';

  for (int i = 0; i < R; i++)
    cout << distr(rng) << ' ';

  cout << '\n';

  for (int i = 0; i < P; i++)
    cout << distr(rng) << ' ';

  cout << '\n';
}