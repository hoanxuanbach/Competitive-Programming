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
const int maxn=150005;
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

int n;

struct node{
    int ans=inf,sz=0;
    vector<int> a,b;
    //a[i]: minimum x so that i->n is subsequence of 1->x or maximum j that i->j-1 cover
    //b[i]: minimum x so that 1->i is subsequence of sz-x+1->sz or minimum j that j+1->i is cover
    node(int _sz=0):sz(_sz){
        a.assign(n+1,0),b.assign(n+1,0);
    }
    friend node operator+(node x,node y){
        node res(x.sz+y.sz);
        res.ans=min(x.ans,y.ans);
        for(int i=1;i<=n;i++){
            if(x.a[i]<0){
                int val=y.a[-x.a[i]];
                if(val>0) res.a[i]=x.sz+val;
                else res.a[i]=val;
            }
            else res.a[i]=x.a[i];

            if(y.b[i]<0){
                int val=x.b[-y.b[i]];
                if(val>0) res.b[i]=y.sz+val;
                else res.b[i]=val;
            }
            else res.b[i]=y.b[i];
        }
        for(int i=1;i<n;i++) if(x.b[i]>0 && y.a[i+1]>0) res.ans=min(res.ans,x.b[i]+y.a[i+1]);
        return res;
    }
};

void solve(){
    string s;cin >> s;
    n=(int)s.length();
    if(n==1){
        cout << 1 << '\n';
        return;
    }
    node A(1),B(1);
    for(int i=1;i<=n;i++){
        if(s[i-1]=='a'){
            A.a[i]=A.b[i]=-i;
            B.a[i]=(i==n?1:-(i+1));
            B.b[i]=(i==1?1:-(i-1));
        }
        else{
            B.a[i]=B.b[i]=-i;
            A.a[i]=(i==n?1:-(i+1));
            A.b[i]=(i==1?1:-(i-1));
        }
    }
    for(int i=0;i<=30;i++) swap(B,A),B=A+B;
    cout << B.ans << '\n';
}   

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
