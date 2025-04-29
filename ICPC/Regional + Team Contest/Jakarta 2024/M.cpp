#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second 
using namespace std;
typedef long long ll;
const int maxn=2e5+5;
int n;
ll a[maxn];
signed main(){
	// freopen("input.inp","r",stdin);
	// freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
	}
	sort(a+1,a+1+n);
	ll sum=0;
	for(int i=1;i<n;i++){
		sum+=a[i];
	}
	if(sum*2<a[n]){
		cout << sum;
	}
	else{
		cout << (sum+a[n])/3 << '\n';
	}
}