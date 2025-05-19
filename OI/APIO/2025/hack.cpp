#include "hack.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int hack(){
    auto check = [&](int &l,int &r){
        if(l==r) return collisions({1,l+1});
        int sz=r-l;
        int d=sqrt(sz);
        vector<ll> val(d,1);
        val.push_back(l);
        for(int i=0;i<sz/d;i++) val.push_back(d);
        for(int i=1;i<(int)val.size();i++) val[i]+=val[i-1];
        r=l+(sz/d+1)*d-1;
        return collisions(val);
    };

    int r=1000000000,l=r/2;
    while(l<r){
        //cout << l << ' ' << r << '\n';
        int mid=(l+r)>>1;
        if(check(l,mid)) r=mid;
        else l=mid+1;
    }
    
    vector<int> p;
    for(int i=2;i*i<=l;i++){
        if(l%i==0){
            while(l%i==0){
                p.push_back(i);
                l/=i;
            }
        }
    }
    if(l>1) p.push_back(l);
    for(int x:p) if(collisions({1,r/x+1})) r/=x;
    
    return r;
}