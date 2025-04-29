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

void solve(){
    string s;cin >> s;
    if(s=="prepare"){
        int t;cin >> t;
        while(t--){
            string x;
            cin >> x;
            string res;
            vector<bool> d(25,false);
            for(char c:x){
                if(d[c-'A']) res+='0';
                else res+='1';
                d[c-'A']=true;
            }
            cout << res << '\n';
        }
    }
    else{
        int t;cin >> t;
        while(t--){
            auto query = [&](int p){
                cout << p+1 << endl;
                string c;cin >> c;
                return c[0]-'A';
            };
            string x;cin >> x;
            vector<int> pos(25,-1),cur;
            for(int i=0;i<50;i++){
                if(x[i]=='1') cur.push_back(i);
                else{
                    int d=query(i);
                    if(pos[d]!=-1) query(pos[d]);
                    else{
                        int p=cur.back();cur.pop_back();
                        int pd=query(p);
                        if(pd!=d){
                            pos[d]=i;
                            if(pos[pd]!=-1){
                                query(p);
                                query(pos[pd]);
                            }
                            else pos[pd]=p;
                        }
                    }
                }
            }
            while(!cur.empty()){
                int p=cur.back();
                cur.pop_back();
                int d=query(p);
                query(pos[d]);
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