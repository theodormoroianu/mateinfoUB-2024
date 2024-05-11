#include <bits/stdc++.h>
using namespace std;

int main()
{
    string command = "python -c \"import sys\nsys.set_int_max_str_digits(10**9)\nprint( sum([ int(i) for i in input().split() ]) )\"";
    system(command.c_str());
    return 0;

}