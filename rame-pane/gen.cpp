/**
 * Author: Theodor Moroianu
*/
#include <bits/stdc++.h>
#include <random>
using namespace std;

int main(int argc, char** argv) {
  int v = stoi(argv[1]);
  int N = stoi(argv[2]);
  int M = stoi(argv[3]);
  int RAMA_MAX = stoi(argv[4]);
  
  mt19937 rng(v);
  uniform_int_distribution<int> dist(1, RAMA_MAX);

  cout << N << " " << M << endl;
  for (int i = 0; i < N; i++) {
    cout << dist(rng) << " ";
  }
}
