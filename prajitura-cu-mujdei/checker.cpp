/**
 * Author: Theodor Moroianu
*/
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char** argv) {
  string input_file(argv[1]);
  string output_file(argv[2]);
  string answer_file(argv[3]);

  ifstream input_stream(input_file);
  ifstream output_stream(output_file);
  ifstream answer_stream(answer_file);

  int A, B, D;
  input_stream >> A >> B >> D;

  try {
    if (D % __gcd(A, B) != 0) {
      string rez;
      output_stream >> rez;
      if (rez == "IMPOSIBIL") {
        cout << "OK\n";
      } else {
        cout << "WA\n";
      }
      return 0;
    }

    int in_a = 0, in_b = 0;
    int nr_op;
    output_stream >> nr_op;
    if (nr_op > 1e6) {
      cout << "WA\n";
      return 0;
    }

    while (nr_op--) {
      string op;
      output_stream >> op;
      if (op == "UMPLE") {
        string care;
        output_stream >> care;
        if (care == "A") {
          in_a = A;
        } else if (care == "B") {
          in_b = B;
        } else
          throw "Invalid input";
      }
      else if (op == "VARSA") {
        string care, dummy, unde;
        output_stream >> care >> dummy >> unde;
        if (dummy != "IN")
          throw "Invalid input";
        if (care == "A") {
          if (unde != "B")
            throw "Invalid input";
          int cat = min(in_a, B - in_b);
          in_a -= cat;
          in_b += cat;
        }
        else if (care == "B") {
          if (unde != "A")
            throw "Invalid input";
          int cat = min(in_b, A - in_a);
          in_b -= cat;
          in_a += cat;
        }
        else
          throw "Invalid input";
      }
      else if (op == "GOLESTE") {
        string care;
        output_stream >> care;
        if (care == "A") {
          in_a = 0;
        } else if (care == "B") {
          in_b = 0;
        } else
          throw "Invalid input";
      }
      else
        throw "Invalid input";
    }

    if (in_a == D || in_b == D)
      cout << "OK\n";
    else
      cout << "WA\n";
  }
  catch(...) {
    cout << "WA\n";
  }  
}
