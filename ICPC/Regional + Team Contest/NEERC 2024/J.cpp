#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second 
using namespace std;
typedef long long ll;
int a[200005];
int b[200005];
int n;
signed main(){
	// freopen("input.inp","r",stdin);
	// freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	for(int i=1;i<=n;i++){
		cin >> b[i];
	}	
	int j=1;
	int ansma=0;
	int ansmi=n;
	for(int i=1;i<=n;i++){
		while(j<=n && a[j]<b[i]){
			j++;
		}
		if(j>n){
			break;
		}
		else{
			ansma=i;
		
			j++;
		}
	}

	j=n;
	for(int i=n;i>=1;i--){
		while(j>=1 && a[j]>b[i]){
			j--;
		}
		if(j<=0){
			break;
		}
		else{
			ansmi=i-1;
			j--;
		}	
		// cout << i << '\n';
	}
	cout << ansma-ansmi+1 << '\n';
	for(int i=ansmi;i<=ansma;i++){
		cout << i << ' ';
	}
}