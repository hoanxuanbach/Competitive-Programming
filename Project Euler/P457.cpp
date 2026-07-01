#include<bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
ull mod_mul(ull a, ull b, ull M){
	long long res = a * b - M * ull(1.L / M * a * b);
	return res + M * (res < 0) - M * (res >= (long long)M);
}
ull mod_pow(ull b, ull e, ull mod){
	ull res = 1;
	for(; e; b = mod_mul(b, b, mod), e >>= 1) if(e & 1) res = mod_mul(res, b, mod);
	return res;
}
// Millar Rabin Primality Test
// 7 times slower than a^b mod c
bool is_prime(ull n){
	if(n < 2 || n % 6 % 4 != 1) return (n | 1) == 3;
	ull s = __builtin_ctzll(n - 1), d = n >> s;
	for(ull a: {2, 325, 9375, 28178, 450775, 9780504, 1795265022}){
		ull p = mod_pow(a, d, n), i = s;
		while(p != 1 && p != n - 1 && a % n && i --) p = mod_mul(p, p, n);
		if(p != n - 1 && i != s) return false;
	}
	return true;
}
// Pollard rho algorithm
// O(n^{1/4})
ull get_factor(ull n){
	auto f = [n](ull x){ return mod_mul(x, x, n) + 1; };
	ull x = 0, y = 0, t = 30, prd = 2, i = 1, q;
	while(t ++ % 40 || __gcd(prd, n) == 1){
		if(x == y) x = ++ i, y = f(x);
		if(q = mod_mul(prd, max(x, y) - min(x, y), n)) prd = q;
		x = f(x), y = f(f(y));
	}
	return __gcd(prd, n);
}
// Returns {p, e} in increasing order of p
vector<ull> factorize(ull n){
	assert(n > 0);
	auto recurse = [&](auto self, ull n)->vector<ull>{
		if(n == 1) return {};
		if(is_prime(n)) return {n};
		ull x = get_factor(n);
		auto l = self(self, x), r = self(self, n / x);
        l.insert(l.end(),r.begin(),r.end());
		return l;
	};
	return recurse(recurse, n);
}


#define int long long 
#define pii pair<int,int>
int power(int a,int n,int mod){
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

void solve(){
    int N;cin >> N;
    auto get = [&](int p,int a){
        //cout << p << ' ' << a << '\n';
        int x=2*a-3;
        int y=(a*a-3*a-1)/p;
        int g=__gcd(x,y);
        if(g%p==0) return a;
        x/=g;y/=g;
        x=(p+x%p)%p,y=(p+y%p)%p;
        if(x%p==0) return inf;
        int t=(p-y%p)*power(x,p-2,p)%p;
        return p*t+a;
    };
    vector<int> f(N,inf);
    for(int n=1;n<N;n++){
        if(n%10000==0) cout << n << endl;
        int x=abs(n*n-3*n-1);
        vector<ull> g=factorize(x);
        sort(g.begin(),g.end());
        g.erase(unique(g.begin(),g.end()),g.end());
        for(int k:g) if(n<k && k<N) f[k]=min(f[k],get(k,n));
    }

    int res=0;
    vector<int> p(N);
    for(int i=2;i<N;i++){
        if(!p[i]){
            for(int j=i;j<N;j+=i) p[j]=i;
            int x=1;
            while(x<i*i && (x*x-3*x-1)%(i*i)!=0) x++; 
            if(f[i]!=inf){
                res+=f[i];
            }
            cout << i << ' ' << min(f[i],x) << ' ' << x << '\n'; 
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
