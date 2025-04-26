#include "dzilib.h"
#include<bits/stdc++.h>
using namespace std;
#define int long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return (int)(rng()%(r-l+1))+l;
}

const int A=1e9;
int N,T;
map<int,int> mp;
int query(int x){
    if(mp.find(x)==mp.end()) return mp[x]=Ask(x);
    return mp[x];
}

int get(int x,int k){
    if((1LL<<k)>N) return (1LL<<k)-x;
    auto cal = [&](int p,int q){
        int a=query(p),b=query(q);
        if(b%(k+1)!=0) return -1LL;
        for(int i=k+2;i<=60;i++) if(a%i==0) return get(p,k+1);
        return -1LL;
    };
    int p=cal(x,x+(1LL<<k));
    return (p==-1?cal(x+(1LL<<k),x):p);
}

void solve(){
    mp.clear();
    int x=(N==A?rand_int(0,2137):rand_int(0,40000000000000));
    Answer(get(x,0));
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    N=max(GetN(),A);
    T=GetT();
    while(T--) solve();
}

