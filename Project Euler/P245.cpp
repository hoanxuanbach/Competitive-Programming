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
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N;cin >> N;

    int S=sqrtl(N)+1;
    vector<int> f(S),p;
    for(int i=2;i<S;i++) if(!f[i]){
        p.push_back(i);
        for(int j=i*2;j<S;j+=i) f[j]=i;
    }

    int res=0;

    int e=0,M=(int)p.size();
    function<void(int,int,int)> dfs = [&](int x,int y,int s){
        int mx=sqrtl(N/x);
        for(int i=s+1;i<M && p[i]<=mx;i++) dfs(x*p[i],y*(p[i]-1),i);

        e++;
        if(e%1000000==0) cout << e << endl;
        
        if(s!=-1){
            /*
            (x-y)*p+y | p*x-1
            */

            int d=(s+1<M?p[s+1]:p[s]+2);
            int A=d*x-1,B=d*(x-y)+y;
            int l=(A+B-1)/B;
            if(l&1) l++;
            
            d=N/x;
            A=d*x-1,B=d*(x-y)+y;
            int r=A/B;

            for(int k=l;k<=r;k+=2){
                A=k*y+1;
                B=x-k*x+k*y;
                if(A%B==0 && is_prime(A/B)) res+=x*(A/B);
            }
        }
    };
    dfs(1,1,-1);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
