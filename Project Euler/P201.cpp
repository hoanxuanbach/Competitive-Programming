#include<bits/stdc++.h>
using namespace std;


int f[400005][55];

void solve(){
    int N=100,K=50,S=0;
    for(int i=1;i<=N;i++) S+=i*i;

    f[0][0]=1;
    for(int x=1;x<=N;x++){
        cout << x << endl;
        int d=x*x;
        for(int j=K;j>=1;j--) for(int i=d;i<=S;i++) f[i][j]=min(2,f[i][j]+f[i-d][j-1]);
    }
    int res=0;
    for(int i=1;i<=S;i++) if(f[i][K]==1) res+=i;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
