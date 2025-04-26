#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 3005;
const int inf = 1e18;
int N,Q,D,L,W;
vector<int> f[maxn];

signed main(){
    cin >> N >> Q >> D >> L >> W;
    for(int i=1;i<=N;i++){
        int k,p;cin >> k >> p;
        f[k].push_back(p+D);
    }

    vector<int> num(N+1,-inf);
    num[0]=0;
    for(int i=1;i<=L;i++){
        sort(f[i].begin(),f[i].end());
        int sz=(int)f[i].size();
        vector<pair<int,int>> dp(sz+1,{-inf,0});
        dp[0]={0,0};
        for(int j=0;j<(int)f[i].size();j++){
            int x=f[i][j];
            for(int k=j;k>=0;k--){
                pair<int,int> cur=dp[k];
                int cnt=(x+cur.second)/D;
                dp[k]=max(dp[k],{cur.first+cnt,cur.second-cnt*D});
                dp[k+1]=max(dp[k+1],{cur.first+cnt-1,-x});
            }
        }
        vector<int> cnt(sz+1);
        for(int j=0;j<=sz;j++){
            pair<int,int> cur=dp[j];
            cnt[j]=cur.first+(W+cur.second)/D;
        }
        for(int j=N;j>=0;j--){
            if(num[j]==-inf) continue;
            for(int k=sz;k>=0;k--) num[j+k]=max(num[j+k],num[j]+cnt[k]);
        }
    }
    for(int i=1;i<=Q;i++){
        int m;cin >> m;
        int l=0,r=N,res=-1;
        while(l<=r){
            int mid=(l+r)>>1;
            if(num[mid]>=m+N-mid) res=N-mid,l=mid+1;
            else r=mid-1;
        }
        cout << res << '\n';
    }
}