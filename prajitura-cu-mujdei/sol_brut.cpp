#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll A, B, D;
map <pair <ll, ll>, int> vis;
// const int MAP_SIZE_LIMIT = 5e6;

int a_star(ll a, ll b, int depth, vector <string> &instr) {
    vis[{a, b}] = 1;
    
    if (a == D){
        return 1;
    }

    if (b == D){
        if (a > 0){
            instr.push_back("GOLESTE A");
        }
        instr.push_back("VARSA B IN A");
        return 1;
    }

    // if ((int) vis.size() > MAP_SIZE_LIMIT){
    //     return 0;
    // }

    // varsa a in b
    {
        ll left_b = B - b;
        ll what = min(a, left_b);

        if (what > 0){
            int new_b = b + what;
            int new_a = a - what;

            if (vis[{new_a, new_b}] == 0){
                instr.push_back("VARSA A IN B");
                if (a_star(new_a, new_b, depth + 1, instr)){
                    return 1;
                }
                instr.pop_back();
            }
        }
    }

    // varsa b in a
    {
        ll left_a = A - a;
        ll what = min(b, left_a);

        if (what > 0){
            int new_a = a + what;
            int new_b = b - what;

            if (vis[{new_a, new_b}] == 0){
                instr.push_back("VARSA B IN A");
                if (a_star(new_a, new_b, depth + 1, instr)){
                    return 1;
                }
                instr.pop_back();
            }
        }
    }

    // umple a
    {
        if (a < A && vis[{A, b}] == 0){
            instr.push_back("UMPLE A");
            if (a_star(A, b, depth + 1, instr)){
                return 1;
            }
            instr.pop_back();
        }
    }

    // umple b
    {
        if (b < B && vis[{a, B}] == 0){
            instr.push_back("UMPLE B");
            if (a_star(a, B, depth + 1, instr)){
                return 1;
            }
            instr.pop_back();
        }
    }

    // goleste a
    {
        if (a > 0 && vis[{0, b}] == 0){
            instr.push_back("GOLESTE A");
            if (a_star(0, b, depth + 1, instr)){
                return 1;
            }
            instr.pop_back();
        }
    }

    // goleste b
    {
        if (b > 0 && vis[{a, 0}] == 0){
            instr.push_back("GOLESTE B");
            if (a_star(a, 0, depth + 1, instr)){
                return 1;
            }
            instr.pop_back();
        }
    }

    return 0;
}

int main(){
    cin >> A >> B >> D;
    vector <string> instr;

    int res = a_star(0, 0, 0, instr);

    if (res == 0){
        cout << "IMPOSIBIL\n";
    } else {
        cout << instr.size() << '\n';
        for (auto &x : instr){
            cout << x << '\n';
        }
    }

    return 0;
}