#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int min_n = atoi(argv[1]),max_n = atoi(argv[2]),subtask = atoi(argv[3]),T = atoi(argv[4]);

    int n;
    if(T==1) n=max_n;
    else n=rnd.next(min_n,max_n);
    int k;
    if(subtask==1) k=rnd.next((n+1)/2,n);
    else if(T&1) k=rnd.next(n/10,n/2);
    else k=rnd.next(1,n/10);
    cout << n << ' ' << k << '\n';
}