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

int fA0[165][10005],f1A[165][10005],f0B[165][10005],fB1[165][10005];

void solve(){
    int L,N,T;cin >> L >> N >> T;T/=2;
    vector<pii> p(N);
    for(int i=0;i<N;i++) cin >> p[i].fi >> p[i].se;
    sort(p.begin(),p.end(),[&](pii x,pii y){
        return x.fi+x.se<y.fi+y.se;
    });
    for(int pos=0;pos<=N;pos++){
        vector<pii> A(p.begin(),p.begin()+pos),B(p.begin()+pos,p.end());
        sort(A.begin(),A.end(),[&](pii x,pii y){
            return x.fi-x.se<y.fi-y.se;
        });
        sort(B.begin(),B.end(),[&](pii x,pii y){
            return x.fi-x.se<y.fi-y.se;
        });
        int sA=(int)A.size(),sB=(int)B.size();
        for(int i=1;i<=sA;i++){
            int x=A[i-1].fi+A[i-1].se-2,y=A[i-1].fi-A[i-1].se+L-1;
            for(int j=0;j<=T;j++){
                fA0[i][j]=fA0[i-1][j]+y;
                if(j>=x) fA0[i][j]=min(fA0[i][j],fA0[i-1][j-x]);
            }

            x=A[sA-i].se-A[sA-i].fi+L-1,y=A[sA-i].fi+A[sA-i].se-2;
            for(int j=0;j<=T;j++){
                f1A[i][j]=f1A[i-1][j]+y;
                if(j>=x) f1A[i][j]=min(f1A[i][j],f1A[i-1][j-x]);
            }
        }
        for(int i=1;i<=sB;i++){
            int x=2*L-(B[sB-i].fi+B[sB-i].se),y=B[sB-i].se-B[sB-i].fi+L-1;
            for(int j=0;j<=T;j++){
                fB1[i][j]=fB1[i-1][j]+y;
                if(j>=x) fB1[i][j]=min(fB1[i][j],fB1[i-1][j-x]);
            }

            x=B[i-1].fi-B[i-1].se+L-1,y=2*L-(B[i-1].fi+B[i-1].se);
            for(int j=0;j<=T;j++){
                f0B[i][j]=f0B[i-1][j]+y;
                if(j>=x) f0B[i][j]=min(f0B[i][j],f0B[i-1][j-x]);
            }
        }
        int pA=0,pB=0;
        while(pA<=sA && pB<=sB){
            for(int i=0;i<=T;i++){
                int x=fA0[pA][i];
                if(x>T) continue;
                x=f0B[pB][T-x];
                if(x>T) continue;
                x=fB1[sB-pB][T-x];
                if(x>T) continue;
                x=f1A[sA-pA][T-x];
                if(x+i<=T){
                    cout << "Yes\n";
                    return;
                }
            }

            if(pA==sA) pB++;
            else if(pB==sB) pA++;
            else if(A[pA].fi-A[pA].se<B[pB].fi-B[pB].se) pA++;
            else pB++;
        }
    }
    cout << "No\n";
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
