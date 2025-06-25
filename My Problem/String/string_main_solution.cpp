#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1e9+7;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    
    int n,k;cin >> n >> k;
    string s;cin >> s;

    vector<vector<int>> dp(n+5,vector<int>(k+1,0));
    dp[0][0]=1;

    vector<bool> p(26,false);

    for(int i=0;i<n;i++) for(int j=0;j<=k;j++){
        for(int x=i;x<min(i+k-j+1,n);x++){
            int c=s[x]-'a';
            if(p[c]) continue;
            (dp[x+1][j+x-i]+=dp[i][j])%=mod;
            p[c]=true;
        }
        for(int x=i;x<min(i+k-j+1,n);x++) p[s[x]-'a']=false;
    }

    vector<int> res(k+1,0);
    for(int i=n-k;i<=n;i++){
        for(int j=0;j<=k-n+i;j++) (res[j+n-i]+=dp[i][j])%=mod;
    }

    for(int i=0;i<=k;i++) cout << res[i] << ' ';
    cout << '\n';
}