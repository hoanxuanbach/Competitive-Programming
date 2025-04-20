#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int maxn = 150005;
const int mx = 150;
int n,m,d,cf[mx+5],cs[mx+5];
int dp[maxn],tf,ts;
void add(int x){
    for(int i=d;i>=x;i--) dp[i]|=dp[i-x];
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> d >> n >> m;
    for(int i=1;i<=n;i++){int x;cin >> x;cf[x]++;tf+=x;}
    for(int i=1;i<=m;i++){int x;cin >> x;cs[x]++;ts+=x;}
    if(tf+ts<=d){
        cout << tf+ts-m << '\n';
        return 0;
    }
    dp[0]=1;
    for(int i=1;i<=mx;i++){
        for(int j=1;j<=cf[i];j<<=1){
            cf[i]-=j;
            add(i*j);
        }
        if(cf[i]) add(i*cf[i]);
    }
    if(tf>=d){
        if(dp[d]) cout << d << '\n';
        else cout << d-1 << '\n';
        return 0;
    }
    int ans=d,total=d-tf;
    for(int i=mx;i>=1;i--){
        while(total>0 && cs[i]){
            total-=i,cs[i]--;
            ans--;
        }
    }
    cout << ans << '\n';
}
