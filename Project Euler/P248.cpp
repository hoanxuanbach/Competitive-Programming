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
    vector<int> P={2,3,5,7,11,13};
    vector<int> S={10,5,2,1,1,1};
    
    int T=1;
    for(int i=1;i<=13;i++) T*=i;

    vector<int> prime;
    priority_queue<array<int,3>,vector<array<int,3>>,greater<array<int,3>>> pq;
    function<void(int,int,int)> dfs = [&](int i,int x,int y){
        if(i==(int)P.size()){
            if(T%y==0) pq.push({x,T/y,0});
            if(T%x==0 && x>=13 && is_prime(x+1)) prime.push_back(x+1);  
            return;
        }

        for(int k=0;k<=S[i]+1;k++){
            if(k){
                x*=P[i];
                if(k>1) y*=P[i];
                else y*=(P[i]-1);
            }
            dfs(i+1,x,y);
        }
    };
    dfs(0,1,1);
    sort(prime.begin(),prime.end());
    
    int id=0;
    while(!pq.empty()){
        auto [x,y,k]=pq.top();pq.pop();
        if(y==1){
            id++;
            if(id%100==0){
                cout << id << ' ' << x << endl;
            }
        }
        else{
            for(int i=k;i<(int)prime.size();i++){
                if(y%(prime[i]-1)==0) pq.push({x*prime[i],y/(prime[i]-1),i+1});
            }
        }
    }

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
