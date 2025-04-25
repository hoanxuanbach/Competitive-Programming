#include <bits/stdc++.h>
#include "light.h"
using namespace std;
#define ll long long
ll n=1;
vector<ll> f;

vector<ll> get(){
    vector<ll> a=f;
    for(ll &x:a) x=n+1-x;
    reverse(a.begin(),a.end());
    return a;
}

void prepare() {
    f.push_back(1);
}

pair<ll, vector<ll>> join(ll p) {
    n+=p;
    if((int)f.size()>2 && f.back()!=f.end()[-2]*2+1) f.pop_back();
    while(f.back()<n){
        ll x=min(n,f.back()*2+1);
        f.push_back(x);
    }
    return {p,get()};
}

pair<ll, vector<ll>> leave(ll p) {
    n-=p;
    vector<ll> g;
    ll x=0;
    while(x<n){
        ll y=2*x+1;
        for(ll u:f){
            if(u-2*p>2*x+1) break;
            y=min(u-p,2*x+1);
        }
        g.push_back(y),x=y;
    }
    f=g;
    return {p,get()};
}
#undef ll
