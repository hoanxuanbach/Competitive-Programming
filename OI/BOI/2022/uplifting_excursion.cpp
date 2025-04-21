#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 180000;
const int inf = 1e18;
int n,m,dp[2][2*N+5],a[605];
vector<int> val[45];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for(int i=0;i<=2*n;i++){
        cin >> a[i];
        if(i==n) continue;
        for(int j=0;j<40;j++) if(a[i]>=(1LL<<j)){
            val[j].push_back(i-n);
            a[i]-=(1LL<<j);
        }
        for(int j=39;j>=0;j--) if(a[i]>=(1LL<<j)){
            val[j].push_back(i-n);
            a[i]-=(1LL<<j);
        }
    }
    int l=N,r=N,t=0;dp[t][N]=0;
    for(int i=0;i<40;i++){
        for(int x:val[i]){
            int nl=min(l,max(0LL,l+x));
            int nr=max(r,min(2*N,r+x));
            for(int j=nl;j<=nr;j++) dp[t^1][j]=(l<=j && j<=r?dp[t][j]:-inf);
            for(int j=l;j<=r;j++){
                int k=(j+x);
                if(k>=0 && k<=2*N) dp[t^1][k]=max(dp[t^1][k],dp[t][j]+(1LL<<i));
            }
            l=nl,r=nr,t^=1;
        }
        for(int j=l;j<=r;j++) dp[t^1][j]=-inf;
        int nl=N,nr=N;
        for(int j=l;j<=r;j++) if((j&1)==(m>>i&1)){
            int k=N+((j-N)>>1);
            dp[t^1][k]=max(dp[t^1][k],dp[t][j]);
            nl=min(nl,k),nr=max(nr,k);
        }
        l=nl,r=nr,t^=1;
    }
    m>>=40;
    if((m+N)<l || r<(m+N) || dp[t][m+N]<0){
        cout << "impossible\n";
        return 0;
    }
    else cout << dp[t][m+N]+a[n] << '\n';
}