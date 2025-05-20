#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int mod=998244353;
const int maxn=1e6+5;
const int maxa=1e6;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}
int n,prime[maxa+5];
vector<int> num[maxa+5];
vector<pii> p[maxn];
int a[maxn],Max[maxa+5],sum[maxn];
void pre_cal(){
    for(int i=2;i<=maxa;i++){
        if(prime[i]==0){
            for(int j=i;j<=maxa;j+=i) prime[j]=i;
            int cur=1,cnt=0;
            while(cur<=maxa/i){cur*=i;cnt++;}
            num[i].assign(cnt+1,-1);
        }
    }
}
void solve(){
    cin >> n;
    pre_cal();
    for(int i=0;i<n;i++){
        cin >> a[i];
        int x=a[i];
        while(x>1){
            int j=prime[x],cnt=0;
            while(x%j==0){x/=j;cnt++;}
            p[i].push_back({j,cnt});
        }
    }
    int ans=0;
    for(int i=1;i<(1<<n);i++){
        int sz=__builtin_popcount(i);
        for(int j=0;j<n;j++){
            if((i&(1<<j))==0) continue;
            for(pii x:p[j]){
                if(num[x.fi][0]==-1) num[x.fi][0]=sz-1;
                else num[x.fi][0]--;
                if(num[x.fi][x.se]==-1) num[x.fi][x.se]=1;
                else num[x.fi][x.se]++;
            }
        }
        for(int j=0;j<n;j++){
            if((i&(1<<j))==0) continue;
            for(pii x:p[j]){
                sum[Max[x.fi]]--;
                Max[x.fi]=max(Max[x.fi],max(num[x.fi][0],num[x.fi][x.se]));
                sum[Max[x.fi]]++;
            }
        }
        for(int j=1;j<sz;j++) ans=(ans+sum[j]*(sz-j))%mod;
        for(int j=0;j<n;j++){
            sum[j]=0;
            if((i&(1<<j))==0) continue;
            for(pii x:p[j]){Max[x.fi]=0;num[x.fi][x.se]=-1;num[x.fi][0]=-1;}
        }
    }
    cout << ans << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
