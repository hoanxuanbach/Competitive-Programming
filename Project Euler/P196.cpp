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

pii is_up(int n,int x){
    int T=n*(n-1)/2+1,i=x-T;

    pii res={-1,-1};
    if(i>0 && is_prime(x-n)) res.first=x-n;
    if(i<n-1 && is_prime(x-n+1)) res.first=x-n+1;
    if(i+1<n-1 && is_prime(x-n+2)) res.second=x-n+2;
    if(res.first==-1) swap(res.first,res.second);
    return res;
}


pii is_down(int n,int x){
    int T=n*(n-1)/2+1,i=x-T;

    pii res={-1,-1};
    if(i>0 && is_prime(x+n-1)) res.first=x+n-1;
    if(is_prime(x+n)) res.first=x+n;
    if(is_prime(x+n+1)) res.second=x+n+1;
    if(res.first==-1) swap(res.first,res.second);
    return res;
}

int S(int n){
    int T=n*(n-1)/2+1;

    int res=0;
    for(int i=0;i<n;i++){
        int x=T+i;
        if(!is_prime(x)) continue;
        pii A=is_down(n,x),B=is_up(n,x);
        if(A.first!=-1 && B.first!=-1) res+=x;
        else if(A.first!=-1 && A.second!=-1) res+=x;
        else if(B.first!=-1 && B.second!=-1) res+=x;
        else if(A.first!=-1){
            if(is_down(n+1,A.first).first!=-1) res+=x;
            else{
                int k=A.first-(x+n);
                if(k==-1 && i>=2 && is_prime(x-2)) res+=x;
                else if(k==1 && i+2<n && is_prime(x+2)) res+=x;
            }
        }
        else if(B.first!=-1){
            if(is_up(n-1,B.first).first!=-1) res+=x;
            else{
                int k=B.first-(x-n+1);
                if(k==-1 && i>=2 && is_prime(x-2)) res+=x;
                else if(k==1 && (i+2)<n && is_prime(x+2)) res+=x;
            }
        }
    }
    return res;
}

void solve(){
    int n,m;cin >> n >> m;
    cout << S(n)+S(m) << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
