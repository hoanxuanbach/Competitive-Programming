#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

const int inf = 1e18;
const int maxn = 2e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ll long long
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

void solve(){
    int n,q;cin >> n >> q;
    vector<int> a(n+1),d(n+1),f(n+1);
    for(int i=0;i<n;i++){
        cin >> a[i];d[i+1]=max(d[i+1],d[i]);
        if(i+1<n) d[i+2]=max(d[i+2],d[i]+a[i]);
    }
    for(int i=n-1;i>=0;i--) f[i]=f[i+1]+a[i];

    vector<int> res(q);
    vector<vector<pii>> qq(n+1);
    for(int i=0;i<q;i++){
        int x;cin >> x;
        int k=upper_bound(d.begin(),d.end(),x)-d.begin()-1;
        for(int j=k;j>=max(0LL,k-2);j--) if(d[j]<=x && x<d[j]+a[j]) qq[j].push_back({x,i});
    }   
    LineContainer cht;
    for(int i=n-1;i>=0;i--){
        cht.add(-i-1,-a[i+1]);
        for(auto [x,id]:qq[i]){
            int k=x-d[i];
            res[id]=max(res[id],f[i]+i*k+cht.query(k));
        }
    }
    for(int i=0;i<q;i++) cout << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}