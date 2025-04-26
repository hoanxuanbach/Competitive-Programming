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
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int inf=1e18;
const int mod=998244353;
const int maxn=2005;
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
const int p=101,q=103;
int h[maxn][maxn],cc[maxn][maxn];
int n,m,pp[maxn],pq[maxn],ip[maxn],iq[maxn];
int check[maxn],kmp[maxn];

void solve(){
    cin >> n >> m;
    pp[0]=pq[0]=ip[0]=iq[0]=1;
    int inv_p=power(p,mod-2),inv_q=power(q,mod-2);
    for(int i=1;i<=n;i++){
        pp[i]=pp[i-1]*p%mod;
        ip[i]=ip[i-1]*inv_p%mod;
    }
    for(int i=1;i<=m;i++){
        pq[i]=pq[i-1]*q%mod;
        iq[i]=iq[i-1]*inv_q%mod;
    }
    auto get_hash = [&](int x1,int y1,int x2,int y2){
        int total=(h[x2][y2]-h[x1-1][y2]-h[x2][y1-1]+h[x1-1][y1-1])%mod;
        total=(total+mod)%mod;
        total=total*ip[x1-1]%mod*iq[y1-1]%mod;
        return total;
    };
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;cin >> c;
            cc[i][j]=h[i][j]=c-'A'+1;
            h[i][j]=h[i][j]*pp[i]%mod*pq[j]%mod;
            h[i][j]=(h[i][j]+h[i-1][j]+h[i][j-1]-h[i-1][j-1]+mod)%mod;
        }
    }
    int res_r=n,res_c=m,res_s=-1;
    auto cal_kmp = [&](int x){
        kmp[0]=-1;kmp[1]=0;
        for(int i=2;i<=m;i++){
            int j=kmp[i-1];
            while(j>=0 && cc[x][j+1]!=cc[x][i]) j=kmp[j];
            kmp[i]=j+1;
        }
    };

    for(int i=1;i<=n;i++){
        cal_kmp(i);
        int cur=m;
        while(cur){
            check[m-kmp[cur]]++;
            cur=kmp[cur];
        }
    }
    for(int j=1;j<=n/2;j++){
        int p=1;
        for(int i=1;i<=m/2;i++){
            if(check[i]==n){
                p=max(p,i);
                int st=get_hash(1,1,j,i),ss=-1;
                while(p<2*i && get_hash(j+1,p-i+1,2*j,p)!=st) p++;
                if(p==2*i) continue;
                ss=p-i;
                int d=i,ok=1,k=1;
                while(k<=n){
                    if(k+j-1<=n){
                        if(get_hash(k,d-i+1,k+j-1,d)!=st) ok=0;
                    }
                    else{
                        if(get_hash(k,d-i+1,n,d)!=get_hash(1,1,n-k+1,i)) ok=0;
                    }
                    d=(d+ss)%i+i;k+=j;
                }
                if(!ok) continue;
                if(i*j<res_r*res_c){
                    res_r=j;res_c=i;res_s=ss;
                }
            }
        }
    }
    cout << res_r << ' ' << res_c << ' ' << res_s << '\n';
}

signed main(){
    //freopen("SHUTTLE.INP","r",stdin);
    //freopen("SHUTTLE.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
