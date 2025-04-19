#include<bits/stdc++.h>
using namespace std;
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
*/
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
//int mod=998244353;
const int maxn=300005;
const int B=650;
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
const int base=101;

int rand(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn],p2[maxn];

void combi(int n){
    fac[0]=p2[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod,p2[i]=p2[i-1]*2%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(k>n || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

struct BIT{
    int sz=0;
    vector<int> bit;
    BIT(int _sz = 0):sz(_sz){
        bit.assign(sz+1,0);
    }
    void update(int x,int val){
        x++;
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        x++;
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
};

void solve(){
    int N,X;cin >> N >> X;
    vector<int> A(2*N),C(2*N);
    for(int i=0;i<2*N;i++) cin >> A[i],A[i]--,A.push_back(A[i]);
    for(int i=0;i<2*N;i++) cin >> C[i];

    BIT f0(4*N),f1(4*N);

    int total=0;
    vector<int> cur(N,-1);
    for(int i=0;i<2*N;i++){
        if(cur[A[i]]==-1){
            total+=f1.query(i);
            f0.update(i,1);
        }
        else f1.update(i,1);
        cur[A[i]]=i;
    }

    vector<pii> P(2*N);
    for(int i=0;i<2*N;i++){
        P[i]={N*N-total,C[i]};
        int x=cur[A[i]];
        total-=(N-f0.query(x));
        f0.update(x,1);
        f0.update(i,-1);
        f1.update(x,-1);
        f1.update(i+2*N,1);
        total+=f1.query(x);
        cur[A[i]]=i+2*N;
    }
    sort(P.begin(),P.end());
    vector<int> suf(2*N,inf),pre(2*N,inf);
    for(int i=2*N-1;i>=0;i--) suf[i]=(i==2*N-1?P[i].se:min(P[i].se,suf[i+1]));   
    for(int i=0;i<2*N;i++) pre[i]=(i==0?P[i].se-P[i].fi*X:min(pre[i-1],P[i].se-P[i].fi*X));

    int Q;cin >> Q;
    for(int i=0;i<Q;i++){
        int K;cin >> K;
        int pos=lower_bound(P.begin(),P.end(),make_pair(K,0LL))-P.begin();
        int res=2*inf;
        if(pos<2*N) res=min(res,suf[pos]);
        if(pos) res=min(res,pre[pos-1]+X*K);
        cout << res << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
