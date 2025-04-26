#include <bits/stdc++.h>
using namespace std;

const int maxn = 2005;
const int mod = 1e9+7;
#define pii pair<int,int>
#define fi first
#define se second
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=1LL*res*a%mod;
        a=1LL*a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn];
void combi(int N){
    fac[0]=1;
    for(int i=1;i<=N;i++) fac[i]=1LL*fac[i-1]*i%mod;
    dfac[N]=power(fac[N],mod-2);
    for(int i=N;i>=1;i--) dfac[i-1]=1LL*dfac[i]*i%mod;
    //cout << dfac[2] << '\n';
}

int num[maxn];
int cnt[2*maxn][2*maxn],dp[2*maxn][2*maxn];
int sum[2*maxn][2*maxn],ls[2*maxn][2*maxn],rs[2*maxn][2*maxn];
int lt[2*maxn],rt[2*maxn];

int count_removals(std::vector<int> S, std::vector<int> E){
	int N = S.size();combi(N);
    for(int i=0;i<N;i++){
        cnt[S[i]][E[i]]++;
        rt[S[i]]=E[i];
        lt[E[i]]=S[i];
    }
    for(int l=2*N;l>=1;l--) for(int r=l+1;r<=2*N;r++) cnt[l][r]+=cnt[l+1][r]+cnt[l][r-1]-cnt[l+1][r-1];

    int cc=0,mx=0;
    vector<pii> p;
    for(int i=1;i<=2*N;i++){
        if(mx<i){
            if(cnt[cc][mx]) p.push_back({cc,mx});
            cc=mx=i;
        }
        mx=max(mx,rt[i]);
    }
    if(cnt[cc][mx]) p.push_back({cc,mx});

    int res=1,M;
    for(auto [L,R]:p){
        num[M=cnt[L][R]]++;
        for(int i=L;i<=R;i++) if(lt[i]) dp[lt[i]][i]=fac[M-1];

        for(int len=1;len<=R-L+1;len++){
            for(int l=L;l<=R-len+1;l++){
                int r=l+len-1;
                sum[l][r]=((sum[l+1][r]+sum[l][r-1]-sum[l+1][r-1])%mod+mod)%mod;
                rs[l][r]=rs[l+1][r];ls[l][r]=ls[l][r-1];

                if(rt[l]==r) dp[l][r]=(dp[l][r]+sum[l][r])%mod;
                if(rt[l] && rt[l]<r) dp[l][r]=((dp[l][r]+rs[l][r])%mod+mod-rs[rt[l]+1][r])%mod;
                if(lt[r] && lt[r]>l) dp[l][r]=((dp[l][r]+ls[l][r])%mod+mod-ls[l][lt[r]-1])%mod;
                dp[l][r]=1LL*dp[l][r]*dfac[M-cnt[l][r]]%mod;


                if(cnt[l][r]<M){
                    int val=1LL*dp[l][r]*fac[M-cnt[l][r]-1]%mod;
                    sum[l][r]=(sum[l][r]+val)%mod;
                    ls[l][r]=(ls[l][r]+val)%mod;
                    rs[l][r]=(rs[l][r]+val)%mod;
                }

                //cout << l << ' ' << r << ' ' << dp[l][r] << ' ' << ls[l][r] << ' ' << rs[l][r] << '\n';
            }
        }

        res=1LL*res*dp[L][R]%mod;
    }
    for(int i=1;i<=N;i++) res=1LL*res*fac[num[i]]%mod;
	return res;
}
