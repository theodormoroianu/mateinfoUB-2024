/**
 * Author: Theodor Moroianu
 * Intended: ??
 * Complexity: O(N^2)
*/
#include <bits/stdc++.h>
using namespace std;

int main()
{
  int N;
  cin >> N;

  vector <string> instr;

  for (int i = 0; i < N; i++) {
    instr.push_back("ASSIGN B A");
    for (int j = i + 1; j < N; j++) {
      instr.push_back("INC B");

      // load a in c and b in d
      instr.push_back("ASSIGN C A");
      instr.push_back("PLOAD C");

      instr.push_back("ASSIGN D B");
      instr.push_back("PLOAD D");

      // if C > D then pswap a and b
      int pos = instr.size();
      instr.push_back("IF_LESS_GOTO C D " + to_string(pos + 2));
      instr.push_back("PSWAP A B");
    }
  }

  for (int i = 0; i < (int)instr.size(); i++)
    cout << i << ". " << instr[i] << '\n';
}