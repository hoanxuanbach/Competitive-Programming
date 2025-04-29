#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second 
using namespace std;
typedef long long ll;
int n,k;
int ans[2056];
int ask(int i,int j){
	cout << i << ' ' << j << endl;
	int x;
	cin >> x;
	return x;
}
signed main(){
	// freopen("input.inp","r",stdin);
	// freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	cin >> n >> k;
	for(int i=1;i<=n;i++){
		memset(ans,-1,sizeof(ans));
		ans[0]=k;
		for(int j=1;j<1<<(n-i+1);j++){
			int bit=j^(j>>1);
			int bit1=(j-1)^((j-1)>>1);
			int chuyen=31-__builtin_clz(bit1^bit);
			k=ask(i,i+chuyen);
			ans[bit]=k;
			if(ans[bit^1]!=-1 && abs(ans[bit^1]-ans[bit])==1){
				if(ans[bit^1]>ans[bit]){
					k=ask(i,i);
				}
				break;
			}
		}
		if(k==n){
			break;
		}
	}
}