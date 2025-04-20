#include "aliens.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pii pair<int,int>
#define pli pair<ll,int>
#define fi first
#define se second
const ll inf = 1e18;
const int maxn = 1e5+5;
const int maxm = 1e6+5;
int mn[maxm];

struct line{
    ll a,b,p;
    int c;
    bool operator<(line l){return a>l.a;}
    bool operator<(ll k){return p<k;}
};
struct cvht{
    line x[maxn];
    int sz=0;
    void reset(){
        sz=0;
    }
    ll div(ll a,ll b){
        return a/b-((a^b)<0 && a%b);
    }
    bool isect(line &l,line y){
        if(l.a==y.a){
            if(l.b<y.b) l.p=inf;
            else if(l.b>y.b) l.p=-inf;
            else l.p=(l.c<y.c?inf:-inf);
        }
        else l.p=div(y.b-l.b,l.a-y.a);
        return l.p>=y.p;
    }
    void add(line l){
        if(sz>0) isect(x[sz],l);
        while(sz>=2 && x[sz-1].p>=x[sz].p) isect(x[--sz],l);
        x[++sz]=l;
    }
    pli query(ll v){
        auto l=*lower_bound(x+1,x+sz+1,v);
        return {l.a*v+l.b,l.c};
    }
}cht;

long long take_photos(int n, int m, int k, std::vector<int> R, std::vector<int> C) {
    for(int i=0;i<m;i++) mn[i]=i+1;
    for(int i=0;i<n;i++){
        if(R[i]<C[i]) swap(C[i],R[i]);
        mn[R[i]]=min(mn[R[i]],C[i]);
    }
    vector<pii> p;
    for(int i=0;i<m;i++) if(mn[i]<=i){
        while(!p.empty() && p.back().se>=mn[i]) p.pop_back();
        p.push_back({i+1,mn[i]});
    }
    n=(int)p.size();
    auto check = [&](ll d){
        cht.reset();
        ll dp=0;
        int px=0,cnt=0;
        for(auto [x,a]:p){
            int v=max(px-a,0);
            cht.add({-2*a,dp+(ll)a*a-(ll)v*v,inf,cnt});
            tie(dp,cnt)=cht.query(x);
            dp+=(ll)x*x+d;cnt++;px=x;
        }
        return make_pair(dp,cnt);
    };
    ll l=0,r=(ll)m*m,ans=r;
    while(l<=r){
        ll mid=(l+r)>>1;
        pli res=check(mid);
        if(res.se<=k) ans=res.fi-k*mid,r=mid-1;
        else l=mid+1;
    }
    return ans;
}
