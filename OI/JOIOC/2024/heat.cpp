#include<bits/stdc++.h>
using namespace std;
const int maxn = 8005;
const int inf = 1e9;
int L,C[maxn],N,X[maxn];
vector<int> P[maxn];
int dp[maxn][maxn],cnt[maxn],ndp[maxn][maxn];
int val[maxn][maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> L;
    for(int i=1;i<=L;i++) cin >> C[i];
    cin >> N;
    for(int i=1;i<=N;i++){
        cin >> X[i];
        P[X[i]].push_back(i);
    }
    int A=0;
    for(int i=0;i<=N+1;i++) dp[0][i]=0;

    for(int i=0;i<=N;i++) for(int j=0;j<=N;j++) val[i][j]=-inf;
    for(int t=1;t<L;t++){

        int B=min(C[t+1],(int)P[t].size()),S=(int)P[t].size();
        for(int i=0;i<=B;i++) for(int j=0;j<=N+1;j++) ndp[i][j]=-inf;

        for(int i=0;i<=N+1;i++) cnt[i]=0;
        for(int x:P[t]) cnt[x]++;
        for(int i=1;i<=N+1;i++) cnt[i]+=cnt[i-1];

        //j=N+1
        int mx=-inf;
        for(int i=0;i<=A;i++) mx=max(mx,dp[i][N+1]);
        for(int i=0;i<=N+1;i++) ndp[min(B,cnt[i])][i]=max(ndp[min(B,cnt[i])][i],mx);

        //nj>=j, cnt[j]>=C[t]-i, ni=cnt[nj]-(C[t]-i)
        //cout << t << ' ' << C[t] << '\n';
        for(int i=0;i<=A;i++){
            for(int j=0;j<=N;j++){
                if(cnt[j]<C[t]-i || dp[i][j]==-inf) continue;
                //cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
                int x=C[t]-i;
                ndp[B][N+1]=max(ndp[B][N+1],dp[i][j]);
                val[x][j]=max(val[x][j],dp[i][j]);
            }
            //if(dp[i][N+1]!=-inf) cout << i << ' ' << N+1 << ' ' << dp[i][N+1] << '\n';
        }
        //cout << mx << '\n';

        for(int i=0;i<=S;i++) for(int j=0;j<=N;j++){
            if(j<N) val[i][j+1]=max(val[i][j+1],val[i][j]);
            if(val[i][j]==-inf || cnt[j]<i) continue;
            int ni=min(B,cnt[j]-i);
            ndp[ni][j]=max(ndp[ni][j],val[i][j]+S-cnt[j]);
            val[i][j]=-inf;
        }
        //nj<=j, cnt[j]>=C[t]-i ni=min(cnt[j]-(C[t]-i),cnt[nj])
        for(int i=0;i<=A;i++) for(int j=0;j<=N;j++){
            if(cnt[j]<C[t]-i || dp[i][j]==-inf) continue;
            int x=cnt[j]+i-C[t];
            val[x][j]=max(val[x][j],dp[i][j]+S-cnt[j]);
        }

        for(int i=0;i<=S;i++){
            for(int j=N;j>=0;j--){
                if(j) val[i][j-1]=max(val[i][j-1],val[i][j]);
                if(val[i][j]==-inf) continue;
                int ni=min({B,cnt[j],i});
                ndp[ni][j]=max(ndp[ni][j],val[i][j]);
                val[i][j]=-inf;
            }
        }

        for(int i=0;i<=B;i++) for(int j=0;j<=N+1;j++) dp[i][j]=ndp[i][j];
        A=B;
    }

    int res=0;
    for(int i=0;i<=A;i++){
        if(i==C[L]){
            for(int j=0;j<=N;j++) res=max(res,dp[i][j]);
        }
        res=max(res,dp[i][N+1]);
    }
    cout << res << '\n';
}
