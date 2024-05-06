/**
 * Author: Theodor Moroianu
 * Intended: 100
 * Complexity: O(A + B)
*/
#include <bits/stdc++.h>
using namespace std;

int Gcd(int a, int b, int& x, int& y)
{
  if (a == 0) {
    x = 0, y = 1;
    return b;
  }

  int x1, y1;
  int d = Gcd(b % a, a, x1, y1);

  // d = (b % a) * x1 + a * y1
  // d = (b - b / a * a) * x1 + a * y1
  // d = a * (y1 - b / a * x1) + b * x1
  x = y1 - b / a * x1;
  y = x1;
  return d;
}

int main()
{
  int A, B, D;
  cin >> A >> B >> D;
  assert(D < A && D < B && D > 0);

  // Dorim sa varsam din cel mic in cel mare, ca sa putem varsa
  // un recipient in cel mult doua mutari.
  string galeata_a = "A", galeata_b = "B";
  if (A < B) {
    swap(A, B);
    swap(galeata_a, galeata_b);
  }

  int x, y, d;
  d = Gcd(A, B, x, y);
  assert(1LL * A * x + 1LL * B * y == d);
  if (D % d != 0)
    return cout << "IMPOSIBIL\n", 0;

  int turnari_din_B = 1LL * y * (D / d) % A;
  if (turnari_din_B < 0)
    turnari_din_B += A;

  int curent_a = 0;
  vector <string> instructiuni;

  while (turnari_din_B--) {
    // Umplem B.
    instructiuni.push_back("UMPLE " + galeata_b);

    // Varsam cat putem din B in A.
    instructiuni.push_back("VARSA " + galeata_b + " IN " + galeata_a);
    int cat = min(A - curent_a, B);
    curent_a += cat;

    // Daca am umplut A, golim.
    if (curent_a == A) {
      instructiuni.push_back("GOLESTE " + galeata_a);
      curent_a = 0;
    }

    // Daca nu am varsat tot din B, varsam ce ramane.
    if (cat < B) {
      instructiuni.push_back("VARSA " + galeata_b + " IN " + galeata_a);
      curent_a += B - cat;
    }
  }

  cout << instructiuni.size() << '\n';
  for (auto instr : instructiuni) {
    cout << instr << '\n';
  }
  return 0;
}