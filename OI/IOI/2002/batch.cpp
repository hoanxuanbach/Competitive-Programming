#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 1e4+5;
const int inf = 1e18;
int N,S,C[maxn],T[maxn],dp[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> S;
    for(int i=1;i<=N;i++){
        cin >> T[i] >> C[i];
        T[i]+=T[i-1],C[i]+=C[i-1];
    }
    for(int i=1;i<=N;i++){
        dp[i]=inf;
        for(int j=0;j<i;j++) dp[i]=min(dp[i],dp[j]+S*(C[N]-C[j])+T[i]*(C[i]-C[j]));
    }
    cout << dp[N] << '\n';
}
