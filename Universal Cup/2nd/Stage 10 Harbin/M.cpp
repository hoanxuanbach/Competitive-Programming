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
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=2005;
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
const int base=101;

struct color{
    int x1,y1,x2,y2;
    char c;
};
int sz;
color qq[maxn];

char get(int x,int y){
    for(int i=sz;i>=1;i--){
        if(qq[i].y2==-inf){
            int sum=(qq[i].x1-x)*(qq[i].x1-x)+(qq[i].y1-y)*(qq[i].y1-y);
            if(sum<=qq[i].x2*qq[i].x2) return qq[i].c;
        }
        else{
            if(qq[i].x1<=x && x<=qq[i].x2 && qq[i].y1<=y && y<=qq[i].y2) return qq[i].c;
        }
    }
    return '.';
}

void solve(){
    int n;cin >> n;
    for(int _=1;_<=n;_++){
        string s;cin >> s;
        if(s[0]=='C'){
            int x,y,r;cin >> x >> y >> r;
            char c;cin >> c;
            qq[++sz]={x,y,r,-inf,c};
        }
        else if(s.back()=='e'){
            int x1,y1,x2,y2;cin >> x1 >> y1 >> x2 >> y2;
            char c;cin >> c;
            qq[++sz]={x1,y1,x2,y2,c};
        }
        else{
            int x1,y1,x2,y2;cin >> x1 >> y1 >> x2 >> y2;
            for(int j=y2;j>=y1;j--){
                for(int i=x1;i<=x2;i++){
                    cout << get(i,j);
                }
                cout << '\n';
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
