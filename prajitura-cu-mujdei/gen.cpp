#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
  int A = stoi(argv[1]);
  int B = stoi(argv[2]);
  int D = stoi(argv[3]);

  assert(A > 0 && B > 0 && D > 0);
  assert(D < A && D < B);

  cout << A << ' ' << B << ' ' << D << '\n';
}