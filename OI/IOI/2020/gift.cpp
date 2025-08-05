#include "gift.h"
#include<bits/stdc++.h>
using namespace std;

int construct(int n, int m, std::vector<int> a, std::vector<int> b, std::vector<int> x) {
    vector<int> r(n);
    iota(r.begin(),r.end(),0);
    for(int i=0;i<m;i++) if(x[i]==1) r[a[i]]=max(r[a[i]],b[i]);
    vector<int> v;
    for(int i=n-1;i>=0;i--){
        while(!v.empty() && v.back()<=r[i]) v.pop_back();
        r[i]=(v.empty()?n-1:v.back()-1);
        v.push_back(i);
    }
    for(int i=1;i<n;i++) r[i]=max(r[i],r[i-1]);
    for(int i=0;i<m;i++) if(x[i]==2 && b[i]<=r[a[i]]) return 0;
    int t=0;
    string res;
    for(int i=0;i<n;i=r[i]+1){
        t^=1;
        for(int j=i;j<=r[i];j++) res+=(t?'R':'B');
    }
    craft(res);
    return 1;
}
