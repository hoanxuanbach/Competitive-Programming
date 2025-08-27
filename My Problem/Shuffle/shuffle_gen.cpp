#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int min_n = atoi(argv[1]),max_n = atoi(argv[2]),min_q = atoi(argv[3]),max_q = atoi(argv[4]),subtask = atoi(argv[5]),T=atoi(argv[6]);
    int n=rnd.next(min_n,max_n);
    cout << n << '\n';
    for(int i=1;i<=n;i++) cout << rnd.next(0,mod-1) << " \n"[i==n];
    int q=rnd.next(min_q,max_q);
    cout << q << '\n';

    if(subtask > 1){
        for(int i=0;i<q;i++){
            int id=min(2,rnd.next(1,3));
            int l=rnd.next(1,n),r=rnd.next(1,n);
            if(l>r) swap(l,r);
            cout << id << ' ' << l << ' ' << r << '\n';
        }
    }
    else{
        mt19937_64 rng(T);
        int cnt=min(10,q/2);
        vector<int> ID(q,2);
        for(int i=0;i<cnt;i++) ID[i]=1;
        shuffle(ID.begin(),ID.end(),rng);

        for(int i=0;i<q;i++){
            int id=ID[i];
            int l=rnd.next(1,n),r=rnd.next(1,n);
            if(l>r) swap(l,r);
            if(id==1) r=min(r,l+1);
            else if(id==2){
                if(l==1 && r==n){
                    int t=rnd.next(0,1);
                    if(t) l++;
                    else r--;
                }
            }
            else{
                if(r>l+n/2) r=rnd.next(l,l+n/2);
            }
            cout << id << ' ' << l << ' ' << r << '\n';
        }
    }
}