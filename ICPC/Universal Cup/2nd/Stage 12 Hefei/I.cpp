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

int n,a[65],b[65],a2[65],b2[65];
string s[65*65];
int F[305],res[65];
char C[65];

void solve(){
    cin >> n;
    vector<int> all;
    for(int i=0;i<n;i++) a[i]=b[i]=a2[i]=b2[i]=0;
    for(int i=0;i<n;i++) for(int j=0;j<n;j++){
        int x=i*j;
        if(x/n) a[x/n]++;
        b[x%n]++;
        all.push_back(x);
    }
    sort(all.begin(),all.end());
    for(int i=0;i<n*n;i++){
        cin >> s[i];
        b2[F[s[i].back()]]++;
        if((int)s[i].size()>=2) a2[F[s[i][0]]]++;
    }
    map<pii,vector<int>> mp,mp2;
    vector<pii> com;
    for(int i=0;i<n;i++){
        mp[{a[i],b[i]}].push_back(i);
        mp2[{a2[i],b2[i]}].push_back(i);
        com.push_back({a[i],b[i]});
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    bool check=false;
    auto ok = [&]{
        vector<int> all2;
        for(int i=0;i<n*n;i++){
            int val=0;
            for(char c:s[i]) val=val*n+res[F[c]];
            all2.push_back(val);
        }
        sort(all2.begin(),all2.end());
        return all2==all;
    };
    function<void(int)> backtrack = [&](int pos){
        if(pos==(int)com.size()){
            if(ok()) check=true;
            return;
        }
        vector<int> v=mp[com[pos]],v2=mp2[com[pos]];
        sort(v2.begin(),v2.end());
        do{
            for(int i=0;i<(int)v.size();i++) res[v2[i]]=v[i];
            backtrack(pos+1);
            if(check) return;
        }while(next_permutation(v2.begin(),v2.end()));
    };
    backtrack(0);
    string ans(n,'0');
    for(int i=0;i<n;i++) ans[res[i]]=C[i];
    cout << ans << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int i=0;i<26;i++) F['a'+i]=i,C[i]='a'+i;
    for(int i=0;i<26;i++) F['A'+i]=26+i,C[26+i]='A'+i;
    int test;cin >> test;
    while(test--) solve();
}
