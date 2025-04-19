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
//#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e8;
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


int mn[20][maxn],pre[maxn],cur[maxn],cnt[maxn];
int A[maxn],L[maxn],R[maxn],res[maxn],P[maxn];

void solve(){
    int N;cin >> N;

    int S=0;
    for(int i=1;i<=N;i++) cin >> A[i],S=max(S,A[i]);   

    int Q;cin >> Q;
    for(int i=0;i<Q;i++) cin >> L[i] >> R[i];

    int LG=0;
    while((1<<LG)<=N) LG++;
    
    for(int i=1;i<=N;i++) pre[i]=pre[i-1]+A[i];

    for(int x=1;x<=S;x++){
        for(int i=1;i<=N;i++){
            cur[i]=(A[i]<=x?-A[i]:A[i]);
            cnt[i]=cnt[i-1]+(A[i]==x);
            mn[0][i]=min(0,cur[i]);
            cur[i]+=cur[i-1];
            //cout << cur[i] << ' ';
        }
        //cout << '\n';
        for(int j=1;j<LG;j++){
            for(int i=(1<<j);i<=N;i++) mn[j][i]=min(mn[j-1][i-(1<<(j-1))],cur[i-(1<<(j-1))]-cur[i-(1<<j)]+mn[j-1][i]);
        }
        for(int i=0;i<Q;i++){
            int l=L[i],r=R[i],val=0;
            if(l>r) continue;
            for(int j=LG-1;j>=0;j--){
                if(r-(1<<j)+1<l) continue;
                int base=P[i]+pre[r-(1<<j)]-pre[l-1];
                //if(i==0) cout << '*' << r << ' ' << j << ' ' << mn[j][r] << '\n';
                int nval=min(mn[j][r],cur[r]-cur[r-(1<<j)]+val);
                if(base+nval>=0) val=nval,r-=(1<<j);
            }
            res[i]+=cnt[R[i]]-cnt[r];
            P[i]+=pre[r]-pre[L[i]-1];
            L[i]=r+1;
            //if(i==0) cout << res[i] << ' ' << r << ' ' << P[i] << ' ' << L[i] << '\n';
        }
        for(int i=1;i<=N;i++) swap(pre[i],cur[i]);
    }

    for(int i=0;i<Q;i++) cout << res[i] << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
