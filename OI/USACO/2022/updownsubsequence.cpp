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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
//const int inf=1e18;
const int mod=998244353;
const int maxn=300005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
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
const int base=101;

int n,a[maxn];
char c[maxn];

pii LIDS(int st,char cc,int cnt){
    //cout << st << ' ' << cc << ' ' << cnt << '\n';
    vector<int> pos;
    if(cc=='U'){
        for(int i=st;i<=n;i++){
            int p=lower_bound(pos.begin(),pos.end(),a[i])-pos.begin();
            if(p==(int)pos.size()) pos.push_back(a[i]);
            else pos[p]=a[i];
            //cout << (int)pos.size() << ' ' << p << '\n';
            if((int)pos.size()==cnt) return {(int)pos.size(),i};
        }
        return {(int)pos.size(),n+1};
    }
    else{
        for(int i=st;i<=n;i++){
            int p=0,l=0,r=(int)pos.size()-1;
            while(r>=l){
                int mid=(l+r)>>1;
                if(pos[mid]>a[i]) p=mid+1,l=mid+1;
                else r=mid-1;
            }

            if(p==(int)pos.size()) pos.push_back(a[i]);
            else pos[p]=a[i];
            if((int)pos.size()==cnt) return {(int)pos.size(),i};
        }
        return {(int)pos.size(),n+1};
    }
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    c[1]='U';
    for(int i=2;i<=n;i++) cin >> c[i];
    int p=0,res=0,l=1;
    while(l<=n){
        int r=l;
        while(r+1<=n && c[r+1]==c[l]) r++;
        pii nxt=LIDS(p,c[l],r-l+2);
        res+=nxt.fi-1;
        if(nxt.se>n) break;
        else p=nxt.se;
        l=r+1;
    }
    cout << res-1 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
