#include "prize.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int a[maxn];
set<int> s[maxn];

int find_best(int n) {
    function<int(int,int)> f = [&](int l,int r){
        if(l>r) return -1;
        int m=(l+r)>>1;
        vector<int> v=ask(m);
        int k=(a[m]=v[0])+v[1];
        if(!k) return m;
        auto it=s[k].insert(m).first;
        if(it==s[k].begin() || a[*prev(it)]!=a[m]){
            int x=f(l,m-1);
            if(x!=-1) return x;
        }
        if(next(it)==s[k].end() || a[m]!=a[*next(it)]){
            int x=f(m+1,r);
            if(x!=-1) return x;
        }
        return -1;
    };
    return f(0,n-1);
}
