#include<bits/stdc++.h>
using namespace std;

#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

template<class T>
tuple<T, vector<int>, vector<int>> hungarian_weighted_bipartite_matching(vector<vector<T>> a){
	if(a.empty()) return {0, {}, {}};
	int n = (int)a.size() + 1, m = (int)a[0].size() + 1;
	for(auto i = 0; i < n - 1; ++ i) for(auto j = 0; j < m - 1; ++ j) a[i][j] = -a[i][j];
	vector<T> u(n), v(m);
	vector<int> p(m), mu(n - 1);
	for(auto i = 1; i < n; ++ i){
		p[0] = i;
		int j0 = 0; // add "dummy" worker 0
		vector<T> dist(m, numeric_limits<T>::max());
		vector<int> pv(m, -1), done(m + 1);
		do{ // dijkstra
			done[j0] = true;
			int i0 = p[j0], j1;
			T delta = numeric_limits<T>::max();
			for(auto j = 1; j < m; ++ j) if(!done[j]){
				T cur = a[i0 - 1][j - 1] - u[i0] - v[j];
				if(cur < dist[j]) dist[j] = cur, pv[j] = j0;
				if(dist[j] < delta) delta = dist[j], j1 = j;
			}
			for(auto j = 0; j < m; ++ j){
				if(done[j]) u[p[j]] += delta, v[j] -= delta;
				else dist[j] -= delta;
			}
			j0 = j1;
		}while(p[j0]);
		while(j0){ // update alternating path
			int j1 = pv[j0];
			p[j0] = p[j1], j0 = j1;
		}
	}
	vector<int> mv(m - 1, -1);
	for(auto j = 1; j < m; ++ j) if(p[j]) mu[p[j] - 1] = j - 1, mv[j - 1] = p[j] - 1;
	return {v[0], u, v};
}

void solve(){
    int n;cin >> n;
    vector<vector<int>> A(n,vector<int>(n));
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) cin >> A[i][j];
    auto [T,X,Y]=hungarian_weighted_bipartite_matching(A);
    cout << n*T << '\n';
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++) cout << -(X[i]+Y[j]) << ' ';
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
