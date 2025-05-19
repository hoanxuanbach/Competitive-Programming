#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
const int maxa = 200000;
const int Min = 50000, Max = 100000;
 
signed main(int argc, char* argv[])
{
    registerGen(argc, argv, 1);
    int subtask = atoi(argv[1]), id = atoi(argv[2]);
    int n = (subtask == 1 ? 300 : subtask == 2 ? 2000 : (int)2e5);
    int lim = (subtask == 3 ? 20 : max(10, n /(100*id)));
 
    if(subtask <= 2){
        cout << n << endl;
        for (int i = 1; i <= n; i++)
            cout << rnd.next(1, lim) << " \n"[i == n];
    }
    else{
        vector<int> p(maxa);
        iota(p.begin(),p.end(),1);
        mt19937_64 rng(id);
        if(subtask == 4) shuffle(p.begin(),p.end(),rng);
        
        
        int mx = rnd.next(Min,Max);
        int d = rnd.next(1,min(lim,mx)),k = mx/d;
 
        
        vector<int> order(k-1);
        iota(order.begin(),order.end(),1);
        shuffle(order.begin(),order.end(),rng);
 
        int sz=rnd.next(0,min({k-1,k/2,20}));
 
        vector<int> pos;
        for(int i=0;i<sz;i++) pos.push_back(order[i]);
        sort(pos.begin(),pos.end());
        
        vector<int> a;
        auto add = [&](int x){
            vector<int> b(x*d);
            for(int i=0;i<x;i++) for(int j=0;j<d;j++) b[i*d+j]=p[j];
            shuffle(b.begin(),b.end(),rng);
            for(int i:b) a.push_back(i);
        };
        
        int lst=0;
        for(int x:pos) add(x-lst),lst=x;
        add(k-lst);
 
        vector<int> lt,rt;
        for(int i=0;i<n-k*d;i++){
            int side = rnd.next(0,1);
            int val=rnd.next(0,lim-1);
            if(side) rt.push_back(p[val]);
            else lt.push_back(p[val]);
        }
 
        cout << n << '\n';
        for(int x:a) lt.push_back(x);   
        for(int x:rt) lt.push_back(x);
        for(int i=0;i<n;i++) cout << lt[i] << " \n"[i==n-1];
    }   
}
