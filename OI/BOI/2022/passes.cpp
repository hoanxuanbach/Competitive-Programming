#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e5+5;
const int inf = 1e18;
const int G = 15;

string S;
int N,pre[maxn][G],suf[maxn][G];
vector<int> f[G];
int dp[(1<<G)+5];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> S;
    N=(int)S.length();S="#"+S;
    for(int i=1;i<=N;i++){
        f[S[i]-'A'].push_back(i);
        for(int j=0;j<G;j++) pre[i][j]=pre[i-1][j];
        pre[i][S[i]-'A']++;
    }
    for(int i=N;i>=1;i--){
        for(int j=0;j<G;j++) suf[i][j]+=suf[i+1][j];
        suf[i][S[i]-'A']++;
    }
    for(int i=0;i<G;i++){
        for(int j=1;j<(int)f[i].size();j++){
            int x=f[i][j],y=f[i][j-1];
            for(int k=0;k<G;k++) pre[x][k]+=pre[y][k];
        }
        for(int j=(int)f[i].size()-2;j>=0;j--){
            int x=f[i][j],y=f[i][j+1];
            for(int k=0;k<G;k++) suf[x][k]+=suf[y][k];
        }
    } 
    for(int i=0;i<(1<<G);i++) dp[i]=inf;
    dp[0]=0;
    for(int mask=1;mask<(1<<G);mask++){
        for(int i=0;i<G;i++){
            if(!(mask>>i&1)) continue;
            int sz=(int)f[i].size();
            auto cal = [&](int mask,int j){
                if(j>sz) return inf;
                int val=j*(j-1)/2+(sz-j)*(sz-j-1)/2;
                int x=(j?f[i][j-1]:0),y=(j<sz?f[i][j]:N+1);
                for(int k=0;k<G;k++) if(mask>>k&1) val+=2*(pre[x][k]+suf[y][k]);
                return val;
            };
            int l=0,r=sz;
            while(l<r){
                int m=(l+r)>>1;
                if(cal(mask^(1<<i),m)<cal(mask^(1<<i),m+1)) r=m;
                else l=m+1;
            }
            dp[mask]=min(dp[mask],min(cal(mask^(1<<i),l),cal(mask^(1<<i),l+1))+dp[mask^(1<<i)]);
        }
    }
    cout << setprecision(1) << fixed << (double)dp[(1<<G)-1]/2.0 << '\n';
}