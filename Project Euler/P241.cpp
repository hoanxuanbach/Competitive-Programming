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
ull factorize(ull n){
	assert(n > 0);
	auto recurse = [&](auto self, ull n)->ull{
		if(n == 1) return 0LL;
		if(is_prime(n)) return n;
		ull x = get_factor(n);
		auto l = self(self, x), r = self(self, n / x);
		return max(l,r);
	};
	return recurse(recurse, n);
}

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

void solve(){
    int res=0;
    function<void(int,int,int)> dfs = [&](int x,int a,int b){
        cout << x << ' ' << a << ' ' << b << endl;
        if(a<b || x>inf/b || __gcd(x,b)!=1) return;
        if(b==1){
            if(a==1){
                res+=x;
                cout << '*' << x << '\n';
            }
            return;
        }
        int p=factorize(b),d=1;
        while(((b/d)%p==0)) d*=p;
        while(x<=inf/d){
            int nx=x*d;
            int na=a*d,nb=(__int128)b*(d*p-1)/(p-1);
            int g=__gcd(na,nb);na/=g;nb/=g;
            dfs(nx,na,nb);
            d*=p;
        }

    };
    for(int i=3;i<=13;i+=2) dfs(1,i,2);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
