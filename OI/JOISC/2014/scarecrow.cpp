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
const int mod=998244353;
const int maxn=200005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=250000;
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
const int base=101;
struct BIT{
    int n;
    vector<int> bit;
    BIT(int N):n(N){
        bit.assign(n+1,0);
    };
    void update(int x,int val){
        for(int i=x;i<=n;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
};
void solve(){
    int n;cin >> n;
    vector<int> x(n),y(n),cx,cy;
    for(int i=0;i<n;i++){
        cin >> x[i] >> y[i];
        cx.push_back(x[i]);
        cy.push_back(y[i]);
    }
    sort(cx.begin(),cx.end());
    sort(cy.begin(),cy.end());
    for(int i=0;i<n;i++){
        x[i]=lower_bound(cx.begin(),cx.end(),x[i])-cx.begin();
        y[i]=lower_bound(cy.begin(),cy.end(),y[i])-cy.begin();
    }
    int ans=0;
    vector<int> pos(n,0);
    for(int i=0;i<n;i++) pos[x[i]]=y[i]+1;

    BIT bit(n);

    function<void(int,int)> dnc = [&](int l,int r){
        if(r-l<=1) return;
        int mid=(l+r)>>1;
        dnc(l,mid);dnc(mid,r);
        //cout << l << ' ' << r << '\n';
        set<int> ss;
        vector<pii> q;
        for(int i=mid;i<r;i++){
            if(pos[i]){
                auto it=ss.upper_bound(pos[i]);
                int t=(it==ss.begin()?0LL:*(--it));
                q.push_back({pos[i],t});
                ss.insert(pos[i]);
            }
        }
        ss.clear();
        for(int i=mid-1;i>=l;i--){
            if(pos[i]){
                auto it=ss.lower_bound(pos[i]);
                int t=(it==ss.end()?n+1:*it);
                q.push_back({pos[i],-n-1});
                q.push_back({t,-pos[i]});
                ss.insert(pos[i]);
            }
        }
        sort(q.begin(),q.end());
        for(auto [a,b]:q){
            //cout << "* " << a << ' ' << b << '\n';
            if(b<-n) bit.update(a,1);
            else if(b<0) bit.update(-b,-1);
            else ans+=bit.query(a)-bit.query(b);
        }
    };
    dnc(0,n);
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
