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
const int base=131;

int res[maxn][maxn],cnt;

void f22(int x,int y,int cc){
    for(int i=0;i<=1;i++) for(int j=0;j<=1;j++) res[x+i][y+j]=cc;
}

void f24(int x,int y){
    for(int i=0;i<2;i++) for(int j=0;j<4;j++) res[x+i][y+j]=cnt+!!((j&(i+1)));
    cnt+=2;
}
void f42(int x,int y){
    for(int i=0;i<4;i++) for(int j=0;j<2;j++) res[x+i][y+j]=cnt+!!((i&(j+1)));
    cnt+=2;
}
void ft33(int x,int y){
    f22(x+1,y,cnt);
    f22(x,y+1,cnt+1);
    res[x+1][y+2]=cnt;
    res[x+2][y+2]=cnt+1;
    cnt+=2;
}
void fd33(int x,int y){
    f22(x+1,y+1,cnt+1);
    f22(x,y,cnt);
    res[x][y+2]=cnt;
    res[x][y+1]=cnt+1;
    cnt+=2;
}
void fl222(int x,int y){
    f22(x,y,cnt);
    f22(x+2,y+1,cnt+1);
    res[x+2][y+1]=cnt;
    res[x+1][y+1]=cnt+1;
    cnt+=2;
}
void fr222(int x,int y){
    f22(x,y+2,cnt);
    f22(x+1,y,cnt+1);
    res[x+1][y+1]=cnt;
    res[x+1][y+2]=cnt+1;
    cnt+=2;
}
void fL222(int x,int y){
    f22(x,y,cnt);
    f22(x+1,y+2,cnt+1);
    res[x+1][y+1]=cnt+1;
    res[x+1][y+2]=cnt;
    cnt+=2;
}
void rev33(int x,int y){
    for(int i=0;i<=2;i++) swap(res[x+i][y],res[x+i][y+2]);
}

void build(int x,int y,int n){
    if(n<=2) return;
    if(n==9){
        f24(x+1,y+1);
        fd33(x+1,y+5);
        f42(x+1,y+8);
        fL222(x+3,y+4);
        fd33(x+3,y+1);
        rev33(x+3,y+1);
        ft33(x+5,y+7);
        f24(x+8,y+6);
        f42(x+6,y+1);
        ft33(x+7,y+3);
        rev33(x+7,y+3);
        fL222(x+5,y+3);
    }
    else if(n==5){
        f24(x+1,y+1);
        ft33(x+3,y+3);
        res[x+3][y+1]=res[x+3][y+3]=res[x+4][y+1]=res[x+4][y+2]=cnt++;
    }
    else if(n%2==0){
        for(int i=1;i<=n;i+=2){
            f24(x+i,y+n-3);
            if(i<n-3) f42(x+n-3,y+i);
        }
        build(x,y,n-4);
    }
    else if(n%4==1){
        for(int i=1;i<=n-5;i+=4){
            f24(x+1,y+i);
            f24(x+n-1,y+i);
        }
        fl222(x+1,y+n-4);
        fd33(x+1,y+n-2);
        ft33(x+n-2,y+n-4);
        f42(x+n-3,y+n-1);
        for(int i=4;i<=n-4;i+=2) fr222(x+i,y+n-3);
        build(x+2,y,n-4);
    }
    else if(n%4==3){
        ft33(x+n-2,y+n-2);
        for(int i=1;i<=n-3;i+=4){
            f42(x+i,y+n-1);
            f24(x+n-1,y+i);
        }
        build(x,y,n-2);
    }
}

void solve(){
    int n;cin >> n;cnt=1;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) res[i][j]=0;
    build(0,0,n);
    cout << cnt-1 << '\n';
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) cout << res[i][j] << " \n"[j==n];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
