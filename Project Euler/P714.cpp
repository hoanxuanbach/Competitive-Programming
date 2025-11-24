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
vector<ull> factor(ull n) {
	if (n == 1) return {};
	if (is_prime(n)) return {n};
	ull x = get_factor(n);
	auto l = factor(x), r = factor(n / x);
	l.insert(l.end(),r.begin(),r.end());
	return l;
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
const int inf = 1e17;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ld long double
void solve(){
    int N;cin >> N;
    vector<int> f(N+1,inf);
    
    int S=500000000;
    //int S=0;
    vector<bool> g(S+1);
    for(int i=1;i<=S;i++){
        int x=i;
        int a=-1,b=-1;
        g[i]=true;
        while(x){
            int d=x%10;x/=10;
            if(a==-1) a=d;
            else if(a!=d){
                if(b==-1) b=d;
                else if(b!=d){
                    g[i]=false;
                    break;
                }
            }
        }
    }

    ld val = -1;
    bool has = false;
    auto cal = [&](int x,int a,int b){
        vector<bool> ins(x,false);
        vector<ld> d(x);

        queue<int> q;
        if(a){
            d[a%x]=a;
            ins[a%x]=true;
            q.push(a%x);
        }
        if(b){
            d[b%x]=b;
            ins[b%x]=true;
            q.push(b%x);
        }
        while(!q.empty()){
            int u=q.front();q.pop();
            if(!u){
                if(has) val=min(val,d[u]);
                else has=true,val=d[u];
                return;
            }
            for(int k:{a,b}){
                int v=(u*10+k)%x;
                if(!ins[v]){
                    d[v]=d[u]*10+k;
                    ins[v]=true;
                    q.push(v);
                }
            }
        }
    };
    int cnt=0,fst=-1;
    
    ld res=0;
    for(int i=1;i<=N;i++){
        for(int x=i;x<=S;x+=i) if(g[x]){
            f[i]=x;
            break;
        }
        if(f[i]!=inf) res+=f[i];
        else{
            cnt++;
            cout << '*' << i << ' ' << cnt << endl;
            has = false;
            for(int a=0;a<=9;a++) for(int b=a+1;b<=9;b++) cal(i,a,b);
            if(!has) assert(false);
            res+=val;
        }
    }
    cout << scientific << setprecision(13) << res << '\n';
    //cout << res << ' ' << fst << ' ' << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
