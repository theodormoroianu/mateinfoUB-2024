/**
 * Author: Theodor Moroianu
 * Intended: 0
 * Complexity: O(N)
*/
#include <bits/stdc++.h>
using namespace std;

vector <string> limbaj = {
  // A salveaza pozitia curenta a primului element din ciclu
  "0. IF_DIFF_GOTO A N 2",
  "1. END",
  "2. ASSIGN B E",
  "3. PLOAD C",
  "4. ASSIGN C E",
  "5. PLOAD ",
  "6. IF_DIFF_GOTO A B 9",
  "7. INC A",
  "8. IF_DIFF_GOTO Z N 0",
  "9. PSWAP A B",
  "10. ASSIGN B C",
  "11. PLOAD C",
  "12. IF_DIFF_GOTO Z N 6",
};

int main()
{
  for (auto line : limbaj)
    cout << line << '\n';
}