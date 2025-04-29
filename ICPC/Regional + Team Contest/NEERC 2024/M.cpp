#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second 
using namespace std;
typedef long long ll;
bool dp[1005][1005];
int chuyen(char x){
	if(x>='A' && x<='Z')return x-'A';
	if(x>='a' && x<='z')return x-'a';
	if(x=='-')return 27;
	return 0;
}
signed main(){
	// freopen("input.inp","r",stdin);
	// freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	string s,t;
	cin >> s >> t;
	s=' ' +s;
	t=' ' +t;
	dp[0][0]=1;
	for(int i=1;i<(int)t.size();i++){
		for(int j=0;j<=min((int)s.size(),i);j++){
			if(chuyen(t[i])==chuyen(s[j]) && j && dp[i-1][j-1]){
				dp[i][j]=1;
			}
			if(chuyen(t[i])==chuyen('e') || chuyen(t[i])==chuyen('u') || chuyen(t[i])==chuyen('a') ||chuyen(t[i])==chuyen('o') || chuyen(t[i])==chuyen('i') || chuyen(t[i])==chuyen('y')){
				if(dp[i-1][j]){
					dp[i][j]=1;
				}
			}
			// cout << i << ' ' << j << ' ' << dp[i][j] << '\n';
		}
	}
	// cout << chuyen('b') << '\n';
	// cout << dp[2][1] << '\n';
	if(dp[t.size()-1][s.size()-1]){
		cout << "Same";
	}
	else{
		cout << "Different";
	}
}