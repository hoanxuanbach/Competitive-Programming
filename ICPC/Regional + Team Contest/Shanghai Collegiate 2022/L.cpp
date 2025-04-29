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
const int maxn=200005;
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

struct node{
    int val=0,nxt[26],slink=0,elink=0,dep=0;
    node(){memset(nxt,0,sizeof(nxt));}
};

vector<node> T;
namespace Aho_Corasick{
    void add(string s,int val){
        int u=0;
        for(char a:s){
            int c=a-'a';
            if(!T[u].nxt[c]){
                T[u].nxt[c]=(int)T.size();
                T.push_back(node());
            }
            u=T[u].nxt[c];
        }
        T[u].val=val;
    }
    void build(){
        queue<int> q;q.push(0);
        while(!q.empty()){
            int u=q.front(),p=T[u].slink;q.pop();
            T[u].elink=(T[p].val?p:T[p].elink);
            //cout << u << ' ' << T[u].slink << ' ' << T[u].elink << ' ' << T[u].val << ' ' << T[u].dep << '\n';
            for(int i=0;i<26;i++){
                if(T[u].nxt[i]){
                    int v=T[u].nxt[i];
                    T[v].dep=T[u].dep+1;
                    T[v].slink=(u?T[p].nxt[i]:0);
                    q.push(v);
                }
                else T[u].nxt[i]=T[p].nxt[i];
            }
        }
    }
}

int dp[maxn];

void solve(){
    T.push_back(node());
    string s;cin >> s;
    Aho_Corasick::add(s,0);
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        string t;int val;cin >> t >> val;
        Aho_Corasick::add(t,val);
    }
    Aho_Corasick::build();
    int u=0;dp[0]=1;
    for(int i=1;i<=(int)s.length();i++){
        int c=s[i-1]-'a';
        u=T[u].nxt[c];
        int v=u;dp[i]=dp[i-1];
        if(!T[v].val) v=T[v].elink;
        while(v){
            dp[i]=(dp[i]+T[v].val*dp[i-T[v].dep])%mod;
            v=T[v].elink;
        }
        cout << dp[i] << ' ';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
