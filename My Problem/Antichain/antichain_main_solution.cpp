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

void solve(){
    int n;cin >> n;
    vector<ull> f=factorize(n);
    map<int,int> g;
    for(int x:f) g[x]++;

    vector<vector<int>> S={{1}};
    auto add = [&](int x,int d){
        vector<vector<int>> nS;
        for(auto v:S){
            int m=(int)v.size();
            for(int i=0;i<min(d+1,m);i++){
                vector<int> nv;

                int cur=v[i];
                for(int j=0;j<=d-i;j++){
                    if(j) cur*=x;
                    nv.push_back(cur);
                }
                for(int j=i+1;j<m;j++){
                    cur*=v[j]/v[j-1];
                    nv.push_back(cur);
                }

                nS.push_back(nv);
            }
        }
        swap(S,nS);
    };
    for(auto [x,d]:g) add(x,d);
    cout << (int)S.size() << '\n';
    for(auto v:S){
        cout << (int)v.size() << '\n';
        for(int x:v) cout << x << ' ';
        cout << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}