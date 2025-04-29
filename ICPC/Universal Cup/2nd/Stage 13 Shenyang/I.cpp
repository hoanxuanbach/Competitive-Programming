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
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=131;

void solve(){
    int H,W;cin >> H >> W;
    bool check_H=false,check_W=false,check_all=false;
    vector<pii> p(3);
    for(int i=0;i<3;i++){
        cin >> p[i].fi >> p[i].se;
        if(p[i].fi==H) check_H=true;
        if(p[i].se==W) check_W=true;
        if(p[i].fi==H && p[i].se==W) check_all=true;
    }
    if(check_all){
        int res=1;
        for(pii x:p) res=res*(H-x.fi+1)%mod*(W-x.se+1)%mod;
        cout << res << '\n';
        return;
    }
    if(!check_H && !check_W){
        cout << 0 << '\n';
        return;
    }
    if(!check_H){
        swap(H,W);
        for(pii &x:p) swap(x.fi,x.se);
        swap(check_H,check_W);
    }
    sort(p.begin(),p.end(),[](pii x,pii y){
        if(x.fi!=y.fi) return x.fi>y.fi;
        else return x.se<y.se;
    });
    int res=0;
    //mid
    if(p[1].fi==H && p[2].fi==H){
        int d=W-p[1].se-p[2].se;
        if(d<=0) res+=2*(W-1-p[0].se);
        else res+=2*max(0LL,p[0].se-d+1);
    }
    if(p[1].se==W && p[2].se==W && p[1].fi+p[2].fi>=H) res+=2*(W-1-p[0].se);
    res%=mod;
    //last
    int d=W-p[0].se,add=0;
    if(p[1].fi==H && p[2].fi==H){
        if(p[1].se>=d) add+=(H-p[2].fi+1)*(W-p[2].se+1);
        else if(p[2].se>=d-p[1].se){
            int d2=d-p[1].se;
            int l=max(1LL,d2+p[0].se-p[2].se+1),r=min(W-p[2].se+1,p[0].se+1);
            //cout << l << ' ' << r << '\n';
            add+=r-l+1;
        }
        if(p[2].se>=d) add+=(H-p[1].fi+1)*(W-p[1].se+1);
        else if(p[1].se>=d-p[2].se){
            int d2=d-p[2].se;
            int l=max(1LL,d2+p[0].se-p[1].se+1),r=min(W-p[1].se+1,p[0].se+1);
            add+=r-l+1;
        }
        if(max(p[1].se,p[2].se)>=d) add+=mod-1;
    }
    else if(p[2].fi==H){
        if(p[2].se>=d) add+=(H-p[1].fi+1)*(W-p[1].se+1);
    }
    else if(p[1].fi==H){
        if(p[1].se>=d) add+=(H-p[2].fi+1)*(W-p[2].se+1);
    }
    else{
        if(min(p[1].se,p[2].se)>=d && p[1].fi+p[2].fi>=H) add+=2;
    }
    res=(res+add*2)%mod;
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}

