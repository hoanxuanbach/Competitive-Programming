#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e9+5;
const int maxn = 1e5+5;

int n,m;
int s[maxn],f[maxn];
int dp[maxn],cnt[maxn],trace[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> s[i];
    for(int i=1;i<=m;i++) cin >> f[i];
    s[0]=-inf-1;

    auto get = [&](int l,int r){
        int p=upper_bound(f+1,f+m+1,l)-f;
        return (p<=m && f[p]<r);
    };
    auto check = [&](int d){
        dp[0]=0;
        for(int i=1;i<=n;i++){
            int l=lower_bound(s+1,s+n+1,s[i]-d)-s;

            dp[i]=-1;trace[i]=inf;
            if(dp[i-1]!=-1 && !get(max(s[i-1],s[dp[i-1]]+d),s[i])) dp[i]=i,trace[i]=-1;
            if(l<i){
                int val=cnt[i-2]-cnt[l-1];
                if(val>0 && i-1>dp[i]) dp[i]=i-1,trace[i]=-2;
                if(dp[i-1]>dp[i]) dp[i]=dp[i-1],trace[i]=-3;
            }
            int val=(l<i?i-1:dp[l-1]);
            if(dp[l-1]!=-1 && !get(max(s[l-1],s[dp[l-1]]+d),s[i]-d) && val>dp[i]) dp[i]=val,trace[i]=l;
            //cout << i << ' ' << l << ' ' << dp[i] << '\n';
            cnt[i]=cnt[i-1]+(dp[i]>=0);
        }
        return dp[n]!=-1 && !get(max(s[n],s[dp[n]]+d),inf);
    };
    int l=0,r=inf;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) r=mid;
        else l=mid+1;
    }
    if(l==inf){
        cout << -1 << '\n';
        return 0;
    }
    check(l);
    int x=n;
    string res;
    while(x){
        if(trace[x]>0){
            res+='L';
            for(int i=x;i>trace[x];i--) res+='R';
            x=trace[x]-1;
        }
        else if(trace[x]==-1){
            res+='R';
            x--;
        }
        else if(trace[x]==-2){
            res+="LR";x-=2;
            while(dp[x]<0) x--;
        }
        else{
            res+='L';
            x--;
        }
    }
    reverse(res.begin(),res.end());
    cout << l << '\n' << res << '\n';
}
