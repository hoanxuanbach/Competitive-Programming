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

int N,M,res[maxn];
vector<piii> qq;
int P[maxn];

namespace List{
    int pre[maxn],nxt[maxn];
    void init(int n){
        for(int i=0;i<=n;i++){
            nxt[i]=i+1;
            pre[i+1]=i;
        }
    }
};

void solve(){
    cin >> N >> M;
    for(int i=1;i<=N;i++){
        int a,b;cin >> a >> b;
        qq.push_back({b-a,{a,i}});
    }
    sort(qq.begin(),qq.end());

    int n=0;
    for(int i=1;i<=M;i++){
        int x;cin >> x;
        if(x==P[n] && n) continue;
        else if(n<=1 || (P[n-1]<P[n] && P[n]>x) || (P[n-1]>P[n] && P[n]<x)) P[++n]=x;
        else P[n]=x;
    }

    if(n==1){
        for(auto [sz,x]:qq){
            int l=x.fi,r=x.fi+sz,id=x.se;
            if(l<=P[n] && P[n]<=r) res[id]=0;
            else if(r<P[n]) res[id]=P[n]-r;
            else res[id]=l-P[n];
        }
        for(int i=1;i<=N;i++) cout << res[i] << '\n';
        return;
    }

    //cout << "array\n";
    //for(int i=1;i<=n;i++) cout << P[i] << ' ';
    //cout << '\n';

    List::init(n);
    set<pii> ss;
    int sum=0,cnt=0;
    for(int i=1;i<n;i++){
        ss.insert({abs(P[i+1]-P[i]),i+1});
        sum+=abs(P[i]-P[i+1]);
        cnt++;
    }
    function<void(int)> del = [&](int x){
        //cout << "del " << x << '\n';
        int l=List::pre[x],r=List::nxt[x];
        int nl=List::pre[l];
        //cout << "del " << nl << ' ' << l << ' ' << x << ' ' << r << '\n';
        int sz=abs(P[x]-P[l]);
        if(r>n){
            sum-=sz;cnt--;
            ss.erase({sz,x});
            List::nxt[l]=r;
            List::pre[r]=l;
        }
        else if(!nl){
            sum-=sz;cnt--;
            ss.erase({sz,x});
            List::nxt[nl]=x;
            List::pre[x]=nl;
        }
        else{
            sum-=2*sz;cnt-=2;
            List::nxt[nl]=r;
            List::pre[r]=nl;
            ss.erase({sz,x});
            ss.erase({abs(P[nl]-P[l]),l});
            ss.erase({abs(P[r]-P[x]),r});
            ss.insert({abs(P[r]-P[nl]),r});
        }

    };
    for(auto [sz,x]:qq){
        auto [l,id]=x;
        int r=l+sz;
        //cout << "*" << sz << ' ' << l << ' ' << r  << ' ' << id << '\n';
        while((int)ss.size()>1 && ss.begin()->fi<=sz) del(ss.begin()->se);
        int p=List::nxt[0],c=List::nxt[p];
        if((int)ss.size()<=1 && abs(P[p]-P[c])<=sz){
            if(P[p]>P[c]) swap(p,c);
            if(l<=P[p] && P[c]<=r) res[id]=0;
            else if(r<P[c]) res[id]=P[c]-r;
            else res[id]=l-P[p];
            continue;
        }
        if(P[p]<P[c]) res[id]=abs(l-P[p]);
        else res[id]=abs(P[p]-r);
        res[id]+=sum-cnt*sz;
    }
    for(int i=1;i<=N;i++) cout << res[i] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
