#include <bits/stdc++.h>
using namespace std;

int main(){
    /*
    Vreau sa produc ceva de genu
    $reg = 1
    while $reg <= N:
        while $reg != p[$reg]:
            swap(p[$reg], p[p[$reg]])
        $reg = $reg + 1

    Doar ca indexat de la 0

    0. IF_SAME_GOTO N A 10
    1. ASSIGN B A
    2. PLOAD B
    3. ASSIGN C B
    4. PLOAD C
    5. IF_SAME_GOTO A B 8
    6. PSWAP A B
    7. IF_SAME_GOTO Z Z 1
    8. INC A
    9. IF_SAME_GOTO Z Z 0
    10. END
    */
    int n;
    cin >> n;
    cout << "0. IF_SAME_GOTO N A 10\n";
    cout << "1. ASSIGN B A\n";
    cout << "2. PLOAD B\n";
    cout << "3. ASSIGN C B\n";
    cout << "4. PLOAD C\n";
    cout << "5. IF_SAME_GOTO A B 8\n";
    cout << "6. PSWAP A B\n";
    cout << "7. IF_SAME_GOTO Z Z 1\n";
    cout << "8. INC A\n";
    cout << "9. IF_SAME_GOTO Z Z 0\n";
    cout << "10. END\n";
    return 0;
}