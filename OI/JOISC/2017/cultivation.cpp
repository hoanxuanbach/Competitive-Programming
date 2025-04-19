// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e9;
const int maxn=305;

int R,C,n;
long long ans=1e18;
pii p[maxn];
struct Data{
    int a=0,b=0,c=0;
}f[maxn][maxn];

int cur[maxn];
void init(){
    for(int l=1;l<=n;l++){
        int sz=0;
        for(int r=l;r<=n;r++){
            int d=p[r].se;
            for(int i=1;i<=sz;i++) if(d<cur[i]) swap(d,cur[i]);
            cur[++sz]=d;
            f[l][r].a=cur[1]-1;
            f[l][r].b=C-cur[sz];
            for(int i=1;i<sz;i++) f[l][r].c=max(f[l][r].c,cur[i+1]-cur[i]-1);
            //cout << l << ' ' << r << ' ' << f[l][r].a << ' ' << f[l][r].b << ' ' << f[l][r].c << '\n';
        }
    }
}

int num[2*maxn];
Data dd[2*maxn];
void cal(int len){
    if(len>=ans) return;
    int sz=0;
    for(int i=1,pos=1;i<=n;i++){
        while(pos<=n && p[pos].fi<p[i].fi+len+1){
            int val=p[pos++].fi;
            if(val>num[sz]) num[++sz]=val;
        }
        int val=p[i].fi+len+1;
        if(val>num[sz]) num[++sz]=val;
    }
    for(int i=1,l=1,r=1;i<=sz;i++){
        while(l<=n && !(p[l].fi<=num[i] && num[i]<=p[l].fi+len)) l++;
        r=max(r,l);
        while(r<=n && p[r].fi<=num[i] && num[i]<=p[r].fi+len) r++;
        if(l>n) dd[i]={inf,inf,inf};
        else dd[i]=f[l][r-1];
        //cout << num[i] << ' ' << dd[i].a << ' ' << dd[i].b << ' ' << dd[i].c << '\n';
    }
    deque<pii> a,b,c;
    auto add = [&](deque<pii> &dq,pii x){
        while(!dq.empty() && dq.back().fi<=x.fi) dq.pop_back();
        dq.push_back(x);
    };
    auto del = [&](deque<pii> &dq,int x){
        if(!dq.empty() && dq.front().se<=x) dq.pop_front();
    };
    auto get = [&](deque<pii> &dq){
        if(!dq.empty()) return dq[0].fi;
        else return inf;
    };
    //cout << '*' << len <<  '\n';
    for(int l=1,r=1;l<=sz;l++){
        r=max(r,l);
        while(r<=sz && num[r]<num[l]+R){
            add(a,{dd[r].a,r});
            add(b,{dd[r].b,r});
            add(c,{dd[r].c,r});
            r++;
        }
        ans=min(ans,0LL+len+max(get(a)+get(b),get(c)));
        del(a,l);del(b,l);del(c,l);
    }
}

void solve(){
    cin >> R >> C >> n;
    for(int i=1;i<=n;i++) cin >> p[i].fi >> p[i].se;
    sort(p+1,p+n+1);
    init();
    vector<int> d;
    for(int i=1;i<=n;i++){
        d.push_back(p[i].fi-1);
        d.push_back(R-p[i].fi);
        for(int j=1;j<=n;j++){
            d.push_back(max(0,p[i].fi-p[j].fi-1));
            d.push_back(p[i].fi-1+R-p[j].fi);
        }
    }
    sort(d.begin(),d.end());
    d.erase(unique(d.begin(),d.end()),d.end());
    for(auto len:d) cal(len);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
