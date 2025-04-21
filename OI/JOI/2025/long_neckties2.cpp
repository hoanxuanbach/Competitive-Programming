#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 5e6+5;
#define pii pair<int,int>

int a[maxn];
int dp[(1<<21)+5],cnt[(1<<21)+5];
int A[maxn][21],B[maxn][21];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    for(int i=0;i<n;i++) cin >> a[i];
    int m = *max_element(a,a+n);
    for(int i=0;i<n;i++) a[i]=m-a[i];

    for(int i=0;i<m;i++) A[n][i]=n;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<m;j++) A[i][j]=A[i+1][j];
        A[i][a[i]]=i;
    }

    for(int i=0;i<m;i++) B[n][i]=n;
    for(int i=n-1;i>=0;i--){
        int x=A[i+1][a[i]];
        for(int j=0;j<m;j++) B[i][j]=B[x][j];
        if(i+1<n) B[i][a[i+1]]=i;
    }

    for(int i=1;i<(1<<m);i++) cnt[i]=cnt[i^(i&(-i))]+1;

    vector<int> order(1<<m);
    iota(order.begin(),order.end(),0);
    sort(order.begin(),order.end(),[&](int x,int y){
        return pii{cnt[x],-x}<pii{cnt[y],-y};
    });
    memset(dp,-1,sizeof(dp));

    int res=m;
    for(int mask:order){
        int pos=n,x=dp[mask];
        for(int i=0;i<m;i++){
            if(mask>>i&1) continue;
            for(int j=0;j<m;j++){
                if(mask>>j&1) continue;
                pos=min(pos,B[A[x+1][i]][j]);
            }
        }
        //cout << mask << ' ' << pos << ' ' << x << '\n';
        if(pos>=n){
            //cout << "! " << mask << '\n';
            res=min(res,cnt[mask]);
            continue;
        }
        int lst=0;
        for(int j=m-1;j>=0;j--){
            if(mask>>j&1){lst=j;continue;}
            int nmask=mask^(1<<j);
            if(lst) nmask^=(1<<lst);
            //cout << '*' << nmask << ' ' << j << '\n';
            if(j==a[pos+1]) dp[nmask]=max(dp[nmask],pos+1);
            else if(j==a[pos]) dp[nmask]=max(dp[nmask],pos);
        }
    }
    cout << res << '\n';
}