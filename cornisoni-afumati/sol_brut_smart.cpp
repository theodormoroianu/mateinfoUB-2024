/**
 * Author: Theodor Moroianu
 * Intended: ?
 * Complexity: O(N)
*/
#include <bits/stdc++.h>
using namespace std;

vector <string> limbaj = {
  "0. IF_DIFF_GOTO A N 2",
  "1. END",

  "2. ASSIGN B A",
  "3. INC B",

  "4. IF_DIFF_GOTO B N 7",
  "5. INC A",
  "6. IF_DIFF_GOTO Z N 0",
  "7. ASSIGN C A",
  "8. ASSIGN D B",
  "9. PLOAD C",
  "10. PLOAD D",
  "11. IF_LESS_GOTO C D 13",
  "12. PSWAP A B",
  "13. IF_DIFF_GOTO Z N 3"
};

int main()
{
  for (auto line : limbaj)
    cout << line << '\n';
}