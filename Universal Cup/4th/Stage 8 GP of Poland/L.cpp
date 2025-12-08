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
 
const int maxn = 2e5+5;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ld long double
struct Line {
	mutable ld k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ld x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ld inf = 1/0.000000000000000001;
	ld div(ld a, ld b) { // floored division
		return a/b;}
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ld k, ld m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ld query(ld x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

const int inf = 1e18;
void solve(){
    int n,k,m;cin >> n >> m >> k;
    vector<int> a(n+1),f(n+1);
    for(int i=1;i<=n;i++) cin >> a[i],f[i]=a[i]+f[i-1];
    
    vector<int> p(n+1);
    for(int i=1;i+k<=n+1;i++) p[i]=f[i+k-1]-f[i-1];
    
    set<pii> S;
    vector<int> mn(m+1,inf),mx(m+1,-inf);
    for(int i=1;i<=n;i++){
        if(i+k<=n+1) S.insert({p[i],i});
        if(i>k) S.erase({p[i-k],i-k});
        mn[a[i]]=min(mn[a[i]],S.begin()->first);
        mx[a[i]]=max(mx[a[i]],S.rbegin()->first);
    }

    vector<ld> res(m+1,inf);
    for(int i=1;i<=n;i++) res[a[i]]=0;

    LineContainer T;
    for(int i=1;i<=m;i++){
        if(i*k<mx[i]){
            T.add((ld)k/(mx[i]-i*k),(ld)i*k/(mx[i]-i*k));
        }
        if(!T.empty()) res[i]=min(res[i],-T.query(-i));
    }   
    T.clear();
    for(int i=m;i>=1;i--){
        if(i*k>mn[i]){
            T.add((ld)k/(i*k-mn[i]),(ld)-i*k/(i*k-mn[i]));
        }
        if(!T.empty()) res[i]=min(res[i],-T.query(i));
    }

    for(int i=1;i<=m;i++){
        if(res[i]>1) cout << -1 << '\n';
        else cout << setprecision(10) << fixed << abs(res[i]) << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
