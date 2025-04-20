#include<bits/stdc++.h>
using namespace std;
const int maxn = 5005;
int n,dp[3][maxn];
string s;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> s;s="#"+s;
    int t=0;
    for(int d=1;d<=n;d++){
        t=(t+1)%3;
        for(int l=1;l<=n-d+1;l++){
            int r=l+d-1;
            dp[t][l]=max({dp[(t+2)%3][l+1],dp[(t+2)%3][l]});
            if(s[l]==s[r]) dp[t][l]=max(dp[t][l],dp[(t+1)%3][l+1]+1+(l!=r));
        }
    }
    cout << n-dp[t][1] << '\n';
}
