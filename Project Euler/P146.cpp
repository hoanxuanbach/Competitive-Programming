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
    vector<int> A={1,3,7,9,13,27};
    vector<int> P={2,3,5,7,11,13,17,19,23};
    vector<int> T=P;
    int S=(int)P.size();
    for(int i=1;i<S;i++) T[i]=T[i-1]*P[i];

    int N,res=0;cin >> N;
    function<void(int,int)> dfs = [&](int i,int x){
        if(i==S){
            if(x<=N){
                bool ok=true;
                for(int d:A) if(!is_prime(x*x+d)) ok=false;
                if(ok){
                    if(is_prime(x*x+11)) ok=false;
                    for(int d=15;d<=25;d+=2) if(is_prime(x*x+d)) ok=false;
                    if(ok) res+=x;
                }
            }
            return;
        }
        int K=T[i]/P[i];
        for(int j=0;j<P[i];j++){
            bool ok=true;
            for(int d:A){
                int c=x%P[i];
                c=(c*c+d)%P[i];
                if(!c) ok=false;
            }
            if(ok) dfs(i+1,x);
            x+=K;
        }
    };
    dfs(0,0);
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
