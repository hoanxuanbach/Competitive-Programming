#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int min_n = atoi(argv[1]),max_n = atoi(argv[2]),lim = atoi(argv[3]),subtask = atoi(argv[4]),T = atoi(argv[5]);

    int n=rnd.next(min_n,max_n);
    cout << n << '\n';
    for(int i=1;i<=n;i++) cout << rnd.next(0,lim) << " \n"[i==n];
    int q=rnd.next(min_n,max_n);
    cout << q << '\n';
    for(int i=1;i<=q;i++){
        int l=rnd.next(1,n),r=rnd.next(1,n);
        if(l>r) swap(l,r);
        if((r-l+1)&1){
            if(l>1) l--;
            else if(r<n) r++;
            else l++;
        }
        cout << l << ' ' << r << '\n';
    }
}