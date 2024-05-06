Daca limbajul vi se pare incomplet/aveti sugestii pentru imbunatatire va rog ne contactati!

Detalii limbaj:
  - Registri disponibili: A, B, C, D, E initial toti au valoarea 0
  - Registri constanti:
      - N => citeste mereu valoarea lui N (nu se poate scrie)
      - Z => citeste mereu valoarea 0 (nu se poate scrie)

  - Instructiuni:
       - IF_LESS_GOTO r1 r2 x 
            + daca r1 < r2 atunci goto x
       - IF_DIFF_GOTO r1 r2 x 
            + daca r1 != r2 atunci goto x
       - ASSIGN r1 r2 
            + r1 ia valoarea lui r2 (r1 nu poate fi constatn)
       - INC r
           + incrementeaza r (r nu poate fi constant)
       - DEC r
           + decrementeaza r (r nu poate fi constant)
       - SWAP r1 r2
           + swap(r1, r2) (r1, r2 nu pot fi constanti)
       - PLOAD r
           + r ia valoarea lui perm[r] (r nu poate fi constant)
       - PWASP r1 r2
           + swap(perm[r1], perm[r2]) (r1, r2 nu pot fi constanti)


TODO:
  - de stabilit numarul maxim de operatii pe care le permitem
  - de bagat surse si de stabilit benchmark-ul pe care trebuie sa il bata concurentii
  - de gasit solutii cu numar minim de registri folositi pentru departajare a concurentilor (?)
  - de testat checker-ul !!!!
