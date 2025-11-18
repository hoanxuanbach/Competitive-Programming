#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1000000;
int dp[105][2];

void solve(){
    int N;cin >> N;
    vector<int> s(N*N);
    for(int i=1;i<=55;i++) s[i-1]=(100003-200003*i+300007*i*i*i)%mod-(mod/2);
    for(int i=55;i<N*N;i++) s[i]=(s[i-24]+s[i-55]+mod)%mod-(mod/2);

    vector<vector<int>> a(N,vector<int>(N));
    for(int i=0;i<N;i++) for(int j=0;j<N;j++) a[i][j]=s[i*N+j];

    cout << "first" << endl;
    int mx=0;
    for(int i=0;i<N;i++){
        int d=0;
        for(int j=0;j<N;j++) d=max(0LL,d+a[i][j]),mx=max(mx,d);
        d=0;
        for(int j=0;j<N;j++) d=max(0LL,d+a[j][i]),mx=max(mx,d);
    }
    cout << "second" << endl;
    for(int k=1-N;k<=N-1;k++){
        int l=max(0LL,k),r=N-1-max(0LL,-k);

        int d=0;
        for(int x=l;x<=r;x++) d=max(0LL,d+a[x][x-k]),mx=max(mx,d);
    }
    for(int k=0;k<2*N-1;k++){
        int l=max(0LL,k-(N-1)),r=min(N-1,k);
        
        int d=0;
        for(int x=l;x<=r;x++) d=max(0LL,d+a[x][k-x]),mx=max(mx,d);
    }
    cout << mx << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
