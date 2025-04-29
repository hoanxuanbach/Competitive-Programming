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
typedef unsigned long long ull;
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

ull mask[15][65];
int d[15];

void solve(){
    string s;cin >> s;
    for(int i=0;i<12;i++){
        if(s[i]=='B') d[i]=1;
        else if(s[i]=='R') d[i]=2;
        else if(s[i]=='Q') d[i]=3;
        else if(s[i]=='A') d[i]=5;
        else if(s[i]=='C') d[i]=6;
        else if(s[i]=='M') d[i]=7;
    }
    for(int i=0;i<8;i++) for(int j=0;j<8;j++){
        mask[4][i*8+j]|=(1ULL<<(i*8+j));
        for(int p=0;p<8;p++) for(int q=0;q<8;q++){
            if(p-q==i-j || p+q==i+j) mask[1][i*8+j]|=(1ULL<<(p*8+q));
            if(p==i || q==j) mask[2][i*8+j]|=(1ULL<<(p*8+q));
            if(abs(p-i)+abs(q-j)==3 && i!=p && j!=q) mask[4][i*8+j]|=(1ULL<<(p*8+q));
        }
        mask[3][i*8+j]=mask[1][i*8+j]|mask[2][i*8+j];
        mask[5][i*8+j]=mask[1][i*8+j]|mask[4][i*8+j];
        mask[6][i*8+j]=mask[2][i*8+j]|mask[4][i*8+j];
        mask[7][i*8+j]=mask[3][i*8+j]|mask[4][i*8+j];
    }
    function<bool(int,ull,ull)> dfs = [&](int dep,ull cur_mask,ull pos){
        if(dep==12) return false;
        int id=d[dep];
        bool res=false;
        for(ull x=cur_mask;x;x-=(x&(-x))){
            int k=__builtin_ctzll(x);
            if(pos&mask[id][k]) continue;
            bool nxt=dfs(dep+1,cur_mask&(~mask[id][k]),pos|(1ULL<<k));
            if(!nxt){
                res=true;
                break;
            }
        }

        return res;
    };
    bool res=dfs(0,ULLONG_MAX,0);
    cout << (res?"Alice":"Bob") << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
