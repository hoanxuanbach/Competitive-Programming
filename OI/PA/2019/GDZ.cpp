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
- insert(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include "gdzlib.h"
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int mod2=1e9+7;
const int maxn=200005;
const int bl=650;
const int maxs=650;
const int maxm=200005;
const int maxq=500005;
const int maxl=20;
const int maxa=1000000;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
int n;
vector<pii> d;
//vector<int> p={3,2,6,7,0,1,5,8,4};
int MyAsk(int i,int j){
    i--;j--;
    //return __gcd(p[i],p[j]);
    return Ask(i,j);
}
void MyAnswer(int x){
    x--;
    //cout << x << '\n';
    //assert(p[x]==1);
    Answer(x);
}
/*
int cnt=0;
int GetN(){
    cnt++;
    if(cnt==1) return (int)p.size();
    else return -1;
    if(cnt>100) return -1;
    int N=rng()%100+3;p.clear();
    for(int i=0;i<N;i++) p.push_back(i);
    shuffle(p.begin(),p.end(),rng);
    for(int v:p) cout << v << ' ';
    cout << '\n';
    return N;
}
*/
pii dnc(int x,vector<int> v,int Max){
    if((int)v.size()==1) return {v[0],-1};
    else if((int)v.size()==2) return {v[0],v[1]};
    /*
    cout << x << '\n';
    for(int a:v) cout << a << ' ';
    cout << '\n';
    */
    int p=v[0],pre=Max;
    vector<pii> nd;v.push_back(x);
    for(int a:v){
        if(a==p) continue;
        int cur=MyAsk(p,a);
        nd.push_back({cur,a});
    }
    sort(nd.begin(),nd.end());
    bool check=true;v.clear();
    for(int i=0;i<(int)nd.size();i++){
        if((i+1)*Max!=nd[i].fi) check=false;
    }
    Max=nd.back().fi;
    for(int i=0;i<(int)nd.size();i++){
        if(nd[i].fi==Max) v.push_back(nd[i].se);
    }
    if(check) return {p,-1};
    else{
        pii res=dnc(p,v,Max);
        if(res.se==-1) return res;
        v={0,Max,2*Max};
        for(pii x:nd){
            if(x.se==res.fi || x.se==res.se) continue;
            v.push_back(MyAsk(res.fi,x.se));
        }
        sort(v.begin(),v.end());
        bool ok=true;
        for(int i=0;i<(int)v.size();i++){
            if(v[i]!=pre*i) ok=false;
        }
        if(!ok) res.fi=res.se;
        res.se=-1;
        return res;
    }
}
void solve(){
    if(n==3){
        int x12=MyAsk(1,2),x13=MyAsk(1,3),x23=MyAsk(2,3);
        if(x12==x13) MyAnswer(1);
        else if(x12==x23) MyAnswer(2);
        else MyAnswer(3);
        return;
    }
    d.clear();
    for(int i=2;i<=n;i++) d.push_back({MyAsk(1,i),i});
    sort(d.begin(),d.end());
    bool check0=true,check1=true;
    for(int i=1;i<=n-1;i++){
        if(d[i-1].fi!=i) check0=false;
        if(d[i-1].fi!=1) check1=false;
    }
    if(check0){
        MyAnswer(d[0].se);
        return;
    }
    else if(check1){
        MyAnswer(1);
        return;
    }
    int Max=d.back().fi;
    vector<int> v;
    for(pii x:d){
        if(x.fi==Max) v.push_back(x.se);
    }
    pii pos=dnc(1,v,Max);
    for(pii x:d){
        if(x.fi>1) continue;
        else if(pos.se!=-1){
            int f1=MyAsk(pos.fi,x.se),f2=MyAsk(pos.se,x.se);
            if(f1==1 && f2==1){
                MyAnswer(x.se);
                return;
            }
            if(f2>f1) pos.fi=pos.se;
            if(f2!=f1) pos.se=-1;
        }
        else if(MyAsk(pos.fi,x.se)==1){
            MyAnswer(x.se);
            return;
        }
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    while(true){
        n=GetN();
        if(n==-1) return 0;
        solve();
    }
}
