#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
  int len_a = stoi(argv[1]);
  int len_b = stoi(argv[2]);

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  string a(len_a, '0');
  string b(len_b, '0');

  for (auto& c : a)
    c = '0' + rng() % 10;
  for (auto& c : b)
    c = '0' + rng() % 10;

  if (a[0] == '0')
    a[0] = '1';
  if (b[0] == '0')
    b[0] = '1';

  cout << a << " " << b << endl;
}