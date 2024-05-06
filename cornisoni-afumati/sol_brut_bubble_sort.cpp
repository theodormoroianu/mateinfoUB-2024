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
    "2. INC A",
    "3. ASSIGN B Z",
    "4. ASSIGN C B",
    "5. INC C",
    "6. IF_SAME_GOTO C N 0",
    "7. ASSIGN D B",
    "8. ASSIGN E C",
    "9. PLOAD D",
    "10. PLOAD E",
    "11. IF_LESS_GOTO D E 13",
    "12. PSWAP B C",
    "13. INC B",
    "14. IF_DIFF_GOTO Z N 4"
};

int main()
{
  for (auto line : limbaj)
    cout << line << '\n';
}