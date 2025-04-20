#include<bits/stdc++.h>
using namespace std;
#define maxn 505
#define int long long
const int mod=1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(res*a)%mod;
        a=(a*a)%mod;n>>=1;
    }
    return res;
}
vector<int> x;
int n,l[maxn],r[maxn],dp[maxn][2*maxn],divs[maxn],sum[maxn][2*maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;divs[0]=1;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
        divs[i]=power(i,mod-2)%mod;r[i]++;
        x.push_back(l[i]);x.push_back(r[i]);
    }
    sort(x.begin(),x.end());
    x.erase(unique(x.begin(),x.end()),x.end());
    int m=(int)x.size();
    for(int i=1;i<=n;i++){
        l[i]=lower_bound(x.begin(),x.end(),l[i])-x.begin()+1;
        r[i]=lower_bound(x.begin(),x.end(),r[i])-x.begin();
    }
    dp[0][0]=1;
    for(int i=0;i<m;i++) sum[0][i]=1;
    for(int i=1;i<=n;i++){
        for(int j=1;j<m;j++){
            int mul=1,len=x[j]-x[j-1],cnt=0;
            for(int k=i;k>=1;k--){
                if(j<l[k] || j>r[k]) continue;
                mul=mul*(len+cnt)%mod*divs[++cnt]%mod;
                dp[i][j]=(dp[i][j]+sum[k-1][j-1]*mul)%mod;
            }
        }
        sum[i][0]=dp[i][0]=1;
        for(int j=1;j<m;j++) sum[i][j]=(dp[i][j]+sum[i][j-1])%mod;
    }
    cout << (sum[n][m-1]+mod-1)%mod << '\n';
}
