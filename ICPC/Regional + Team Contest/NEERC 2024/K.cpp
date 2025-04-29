#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second 
using namespace std;
typedef long long ll;
signed main(){
	// freopen("input.inp","r",stdin);
	// freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	int t;
	cin >> t;
	while(t--){
		ll x;
		cin >> x;
		for(ll i=1;i<=65;i++){
			if(__builtin_popcountll(x+i)<=i){
				cout << i-1 << '\n';
				break;
			}
		}
	}
}