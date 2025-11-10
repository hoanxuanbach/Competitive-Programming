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
#define A array<int,3>
const int inf = 1e18;

void solve(){   
    vector<int> X;

    int N;cin >> N;
    vector<int> p(N);
    for(int i=2;i<N;i++) if(!p[i]){
        X.push_back(i);
        for(int j=i*i;j<N;j+=i) p[j]=1;
    }

    priority_queue<A,vector<A>,greater<A>> pq;
    pq.push({X[0]*X[0]*X[0]*X[1]*X[1],0,1});

    int T=200;
    while(!pq.empty()){
        auto [x,a,b]=pq.top();pq.pop();
        string s=to_string(x);
        
        bool proof=true;
        for(int i=0;i<(int)s.size();i++){
            for(int j=0;j<=9;j++){
                if(!j && !i) continue;
                if(s[i]-'0'==j) continue;
                char pre=s[i];
                s[i]=char(j+'0');
                if(is_prime(stoll(s))){
                    proof=false;
                    break;
                }
                s[i]=pre;
            }
            if(!proof) break;
        }

        bool has=false;
        for(int i=0;i+2<(int)s.size();i++) if(s[i]=='2' && s[i+1]=='0' && s[i+2]=='0') has=true;
        if(has && proof){
            T--;
            cout << T << ' ' << x << endl;
            if(!T) return;
        }
        int c=b+1;
        if(c==a) c++;
        __int128 val=(__int128)X[a]*X[a]*X[a]*X[c]*X[c];
        if(val<=inf) pq.push({(int)val,a,c});

        if(b==0 || (a==0 && b==1)){
            a++;b=0;
            val=(__int128)X[a]*X[a]*X[a]*X[b]*X[b];
            if(val<=inf) pq.push({(int)val,a,b});
        }
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
