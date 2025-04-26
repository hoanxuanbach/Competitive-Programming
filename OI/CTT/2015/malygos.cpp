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
#define ull unsigned long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=75;
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

struct xor_basis{
    int cnt=0;
    vector<ull> mask;
    vector<int> bit;
    xor_basis(vector<int> bit={}):bit(bit){
        mask.assign((int)bit.size(),0);
    }
    void add(int x){
        for(int i=(int)bit.size()-1;i>=0;i--){
            if(x>>bit[i]&1){
                if(mask[i]) x^=mask[i];
                else{
                    cnt++;
                    mask[i]=x;
                    return;
                }
            }
        }
    }
    vector<ull> get(){
        vector<ull> res;
        for(int i=0;i<(int)mask.size();i++) if(mask[i]) res.push_back(mask[i]);
        return res;
    }
    bool query(ull x){
        for(int i=(int)bit.size()-1;i>=0;i--){
            if(x>>bit[i]&1) x^=mask[i];
        }
        return !x;
    }
};

int n,k;
ull a[maxn];
int check[maxl];

void solve(){
    cin >> n >> k;

    vector<int> bit;
    for(int i=0;i<n;i++){
        cin >> a[i];
        for(int j=0;j<64;j++) check[j]|=(a[i]>>j&1);
    }
    for(int i=0;i<64;i++){
        if(check[i]) bit.push_back(i);
        check[i]=0;
    }

    xor_basis S(bit);
    for(int i=0;i<n;i++) S.add(a[i]);
    vector<ull> A=S.get();


    __int128 res=0;
    function<void(int,ull,int,vector<int>)> dfs = [&](int t,ull mask,int total,vector<int> cur){
        if(t==k){
            xor_basis cc(cur);
            for(ull x:A) cc.add(x&mask);
            if(cc.query(mask)){
                total-=cc.cnt;
                res+=((__int128)1)<<(total+5);
                //cout << '*' << total << '\n';
            }
            return;
        }
        for(int i=0;i<(int)bit.size();i++){
            if(!check[i]) cur.push_back(bit[i]);
            check[i]++;
            dfs(t+1,mask|(1ULL<<bit[i]),total+bit[i],cur);
            check[i]--;
            if(!check[i]) cur.pop_back();
        }
    };
    vector<int> C;
    dfs(0,0,0,C);
    for(int i=0;i<5;i++) res*=5;

    string s;
    for(int i=0;i<100;i++){
        if(!res) break;
        int x=res%10;res/=10;
        if(i==5 && !s.empty()) s+='.';
        if(!s.empty() || x!=0 || i>=5) s+=char('0'+x);
    }
    reverse(s.begin(),s.end());
    cout << s << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}