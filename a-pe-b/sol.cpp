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

vector <int> Mult(vector <int> a, vector <int> b)
{
    vector<int> c(a.size() + b.size());

    for (int i = 0; i < (int)a.size(); i++)
        for (int j = 0; j < (int)b.size(); j++)
            c[i + j] += a[i] * b[j];


    int carry = 0;
    for (int i = 0; i < (int)c.size(); i++) {
        c[i] += carry;
        carry = c[i] / 10;
        c[i] %= 10;
    }
    while (carry) {
        c.push_back(carry % 10);
        carry /= 10;
    }

    while (!c.empty() && c.back() == 0)
        c.pop_back();
    return c;
}

bool Smaller(vector <int> a, vector <int> b)
{
    if (a.size() != b.size())
        return a.size() < b.size();
    for (int i = (int)a.size() - 1; i >= 0; i--)
        if (a[i] != b[i])
            return a[i] < b[i];
    return false;
}

int main()
{
    vector<int> a = ReadNr();
    vector<int> b = ReadNr();
    vector<int> c = a;
    fill(c.begin(), c.end(), 0);

    for (int i = (int)c.size() - 1; i >= 0; i--) {
        while (c[i] < 9) {
            c[i]++;
            if (Smaller(a, Mult(b, c))) {
                c[i]--;
                break;
            }
        }
    }

    PrintNr(c);
    return 0;
}