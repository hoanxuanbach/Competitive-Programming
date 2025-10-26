#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 1e9+7;
const int T=2000;
#define pii array<int,2>

void solve(){
    int n,X,K;cin >> n >> K >> X;
	
	vector<pii> d(T);
	for(int i=0;i<T;i++) d[i]={0,0};
	d[0][1]=1;
	for(int i=1;i<=K;i++){
		for(int j=T-1;j>=0;j--) for(int k=0;k<=1;k++){
			if(!d[j][k]) continue;
			d[j+i][k]=(d[j+i][k]+d[j][k])%mod;
			if(k) d[j][0]=(d[j][0]+d[j][k])%mod,d[j][k]=0;
		}
	}

	vector<int> dp(T);dp[0]=1;
	for(int i=59;i>=0;i--){
		int t=(X>>i&1);
		vector<int> ndp(T);
		for(int j=0;j<T;j++){
			int nj=j*2+(n>>i&1);
			for(int x=0;x<=nj && x<T;x++){
				int k=min(nj-x,T-1);
				ndp[k]=(ndp[k]+dp[j]*d[x][t])%mod;
			}
		}
		dp=ndp;
	}
	int total=0;
	for(int i=0;i<T;i++) total=(total+dp[i])%mod;
	cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
