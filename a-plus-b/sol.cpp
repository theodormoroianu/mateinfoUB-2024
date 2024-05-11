#include <bits/stdc++.h>
using namespace std;

vector <int> ReadNr()
{
    string s;
    cin >> s;
    vector <int> v;
    for (int i = 0; i < s.size(); i++)
        v.push_back(s[i] - '0');
    reverse(v.begin(), v.end());
    return v;
}

void PrintNr(vector <int> v)
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
    vector <int> a = ReadNr();
    vector <int> b = ReadNr();
    vector <int> c(max(a.size(), b.size()) + 1, 0);
    
    int carry = 0;
    for (int i = 0; i < c.size(); i++) {
        int sum = carry;
        if (i < a.size())
            sum += a[i];
        if (i < b.size())
            sum += b[i];
        c[i] = sum % 10;
        carry = sum / 10;
    }
    assert(carry == 0);
    PrintNr(c);
    return 0;

}