#include<bits/stdc++.h>
using namespace std;
#define int long long
const int mod=1e9+7;
const int maxn=2e5+5;
int n,q,c[maxn],cnt[2],num,total,dp[maxn][3];
map<char,int> mp;
int query(){
    int res=(dp[num][(5-total)%3]+dp[num][(4-total)%3])%mod;
    if(cnt[0]==0 && n%2==1 && n!=1) res--;
    if(cnt[1]==0 && n%2==1 && n!=1) res--;
    res=(res+mod)%mod;
    return res;
}
signed main(){
    //freopen("WZT.INP","r",stdin);
    //freopen("WZT.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    mp['C']=1;mp['Z']=2;mp['N']=0;
    for(int i=1;i<=n;i++){
        char x;cin >> x;c[i]=mp[x];
        if(c[i]) cnt[((c[i]-i)%2+2)%2]++;
        else num++;
        total=(total+c[i])%3;
    }
    dp[0][0]=1;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=2;j++){
            for(int k=1;k<=2;k++) dp[i][j]=(dp[i][j]+dp[i-1][(j-k+3)%3])%mod;
        }
    }
    cout << query() << '\n';
    for(int i=1;i<=q;i++){
        int p;char x;cin >> p >> x;
        int k=mp[x];
        if(c[p]) cnt[((c[p]-p)%2+2)%2]--;
        else num--;
        total=(total-c[p]+3)%3;
        c[p]=k;
        if(c[p]) cnt[((c[p]-p)%2+2)%2]++;
        else num++;
        total=(total+c[p])%3;
        cout << query() << '\n';
    }
}
