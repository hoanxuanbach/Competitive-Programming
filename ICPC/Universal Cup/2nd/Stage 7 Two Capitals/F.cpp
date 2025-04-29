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

void print(vector<vector<char>> c){
    cout << (int)c.size() << ' ' << (int)c[0].size() << '\n';
    for(auto x:c){
        for(auto v:x) cout << v;
        cout << '\n';
    }
}

void solve(){
    int p,q;cin >> p >> q;
    int g=__gcd(p,q);p/=g;q/=g;
    if(5*p>4*q){
        cout << -1 << ' ' << -1 << '\n';
    }
    if(3*p<=2*q){
        q-=p;
        if(p&1) p*=2,q*=2;
        string res;
        for(int i=1;i<=p/2;i++) res+="##.";
        q-=p/2;
        for(int i=1;i<=q;i++) res+='.';
        cout << 1 << ' ' << (int)res.length() << '\n';
        cout << res << '\n';
    }
    else if(p==3 && q==4){
        vector<vector<char>> c(4,vector<char>(4,'#'));
        c[0][0]=c[0][1]=c[2][2]=c[2][3]='.';
        print(c);
    }
    else if(p==4 && q==5){
        vector<vector<char>> c(5,vector<char>(5,'#'));
        c[0][0]=c[1][3]=c[2][1]=c[3][4]=c[4][2]='.';
        print(c);
    }
    else if(p==7 && q==10){
        vector<vector<char>> c(4,vector<char>(5,'#'));
        c[0][0]=c[0][1]=c[1][0]=c[1][1]=c[2][3]=c[3][3]='.';
        print(c);
    }
    else if(p==5 && q==7){
        vector<vector<char>> c(6,vector<char>(7,'#'));
        c[1][0]=c[1][1]=c[2][0]=c[2][1]='.';
        c[0][4]=c[1][4]=c[2][4]=c[3][4]='.';
        c[4][2]=c[4][6]=c[5][2]=c[5][6]='.';
        print(c);
    }
    else if(p==7 && q==9){
        vector<vector<char>> c(6,vector<char>(18,'#'));
        c[0][0]=c[0][5]=c[0][8]=c[0][13]='.';
        c[1][3]=c[1][8]=c[1][11]=c[1][16]='.';
        c[2][1]=c[2][6]=c[2][11]=c[2][14]='.';
        c[3][4]=c[3][9]=c[3][14]=c[3][17]='.';
        c[4][2]=c[4][7]=c[4][12]=c[4][17]='.';
        c[5][2]=c[5][5]=c[5][10]=c[5][15]='.';
        print(c);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
