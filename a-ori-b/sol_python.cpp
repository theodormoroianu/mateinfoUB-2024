#include <bits/stdc++.h>
using namespace std;

int main()
{
    string a, b;
    cin >> a >> b;
    
    string command = "echo -e \"import sys\nsys.set_int_max_str_digits(10**9)\nprint(int(\'" + a + "\') * int(\'" + b + "\'))\" | python";
    system(command.c_str());
    return 0;

}