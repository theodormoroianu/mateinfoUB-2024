#include <bits/stdc++.h>

using namespace std;

const int MOD = 1'000'000'007;

int Putere(int a, int p) {
  int ans = 1;
  while (p) {
    if (p & 1)
      ans = 1LL * ans * a % MOD;
    a = 1LL * a * a % MOD;
    p >>= 1;
  }
  return ans;
}

int InversModular(int a) { return Putere(a, MOD - 2); }

/*
 * In general putem aduna, scadea, inmulti si imparti (pentru impartire folosim
 * InversModular()). ATENTIE LA OVERFLOW!!! (Nu uitati de 1LL si % MOD)
 */
int main() {
  int a = 34, b = 34, c = 123, d = 12112;

  // Asa calculam valoarea unei fractii
  int a_pe_b = 1LL * a * InversModular(b) % MOD;
  int c_pe_d = 1LL * c * InversModular(d) % MOD;

  // (a/b) * b = a (mod MOD)
  assert(1LL * a_pe_b * b % MOD == a);

  // (a/b) + (c/d) = (a*d + c*b) / (b*d) (mod MOD)
  int suma1 = (a_pe_b + c_pe_d) % MOD;
  int suma2 = 1LL * (1LL * a * d % MOD + 1LL * c * b % MOD) *
              InversModular(1LL * b * d % MOD) % MOD;
  assert(suma1 == suma2);

  cout << "OK!!\n";

  return 0;
}
