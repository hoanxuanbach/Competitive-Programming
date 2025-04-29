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
const int maxn=5005;
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

int n,m;
string s,t;

int f[maxn][maxn];
bool g[maxn][maxn];

void solve(){
    cin >> n >> m >> s >> t;
    for(int i=0;i<=m;i++) for(int j=0;j<=i+1;j++) g[i][j]=false;
    for(int i=0;i<=n+m;i++) f[m][i]=0;
    for(int i=m-1;i>=0;i--){
        for(int j=0;j<=n+i;j++){

            if(t[i]=='B') f[i][j]=f[i+1][j+1]+1;
            else if(t[i]=='Q') f[i][j]=max(1LL,f[i+1][j]);
            else f[i][j]=f[i+1][j]+1;

            if(j){
                int d2=-1,d1=0;
                if(t[i]=='B') d2++;
                else if(t[i]=='Q') d1++;
                f[i][j]=min(f[i][j],f[min(m,i+2)][j+d2]-d1);
            }
            f[i][j]=max(f[i][j],0LL);
            //cout << f[i][j] << ' ';
        }
        //cout << '\n';
    }
    int S1=0,S2=0;
    for(char c:s){
        if(c=='Q') S1++;
        else if(c=='B') S2++;
    }
    g[0][0]=1;
    for(int i=0;i<m;i++){
        for(int j=0;j<=i/2;j++){
            int d2=S2-j,d1=S1-(i-2*j);
            if(d2<0 || d1<0 || !g[i][j]) continue;
            if(d2) g[min(i+2,m)][j+1]=true;
            if(d1) g[i+1][j]=true;
        }
        if(t[i]=='Q') S1++;
        else if(t[i]=='B') S2++;
    }

    for(int k=n;k<=n+m;k++){
        S1=0,S2=0;
        for(char c:s){
            if(c=='Q') S1++;
            else if(c=='B') S2++;
        }
        bool check=false;
        for(int i=0;i<=m;i++){
            int d2=k-n,d1=i-(k-n)*2;
            if(d2>=0 && d1>=0 && d2<=S2 && d1<=S1){
                if(g[i][d2] && f[i][S2-d2]<=S1-d1){
                    //cout << d2 << ' ' << i << ' ' << S2-d2 << ' ' << S1-d1 << '\n';
                    check=true;
                }
            }
            if(i<m){
                if(t[i]=='Q') S1++;
                else if(t[i]=='B') S2++;
            }
        }
        if(check){
            cout << k << '\n';
            return;
        }
    }
    cout << "IMPOSSIBLE\n";
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
