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

void DFT(vector<complex<double>> &a, bool rev)
{
    int n = a.size();
    auto b = a;
    for (int step = n / 2; step; step /= 2)
    {
        for (int i = 0; i < n / 2; i += step)
        {
            auto wn = polar(1.0, 2.0 * M_PI * (rev ? -i : i) / n);
            for (int j = 0; j < step; ++j)
            {
                auto u = a[i * 2 + j], v = wn * a[i * 2 + j + step];
                b[i + j] = u + v;
                b[i + n / 2 + j] = u - v;
            }
        }
        swap(a, b);
    }
    if (rev)
        for (auto &x : a)
            x /= n;
}

vector <int> FFT(vector <int> a, vector <int> b)
{
    int n = 1;
    while (n < a.size() + b.size())
        n *= 2;
    vector <complex <double>> fa(n), fb(n);
    for (int i = 0; i < a.size(); i++)
        fa[i] = a[i];
    for (int i = 0; i < b.size(); i++)
        fb[i] = b[i];
    DFT(fa, false);
    DFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    DFT(fa, true);
    vector <int> c(n);
    for (int i = 0; i < n; i++)
        c[i] = round(fa[i].real());
    return c;
}

int main()
{
    vector<int> a = ReadNr();
    vector<int> b = ReadNr();
    vector<int> c = FFT(a, b);


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