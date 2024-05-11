#include <bits/stdc++.h>
using namespace std;

vector<int> ReadNr()
{
    string s;
    cin >> s;
    vector<int> v;
    for (int i = 0; i < s.size(); i++)
        v.push_back(s[i] - '0');
    reverse(v.begin(), v.end());
    return v;
}

void PrintNr(vector<int> v)
{
    while (!v.empty() && v.back() == 0)
        v.pop_back();
    reverse(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
        cout << v[i];
    cout << endl;
}

int main()
{
    vector<int> a = ReadNr();
    vector<int> b = ReadNr();
    vector<int> c(a.size() + b.size());

    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            c[i + j] += a[i] * b[j];


    int carry = 0;
    for (int i = 0; i < c.size(); i++) {
        c[i] += carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
    while (carry) {
        c.push_back(carry % 10);
        carry /= 10;
    }

    PrintNr(c);
    return 0;
}