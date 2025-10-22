#include<bits/stdc++.h>
using namespace std;
#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const ll mod = 998244353;

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

typedef vector<ll> vl;

const int root = 62;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, modpow(root, mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vi rev(n);
	rep(i,0,n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
	rep(i,0,n) if (i < rev[i]) swap(a[i], a[rev[i]]);
	for (int k = 1; k < n; k *= 2)
		for (int i = 0; i < n; i += 2 * k) rep(j,0,k) {
			ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
			a[i + j + k] = ai - z + (z > ai ? mod : 0);
			ai += (ai + z >= mod ? z - mod : z);
		}
}
vl conv(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
	    n = 1 << B;
	int inv = modpow(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}

#define int long long
const int maxn = 2e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=(res*a)%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}


void solve(){
    int n,m;cin >> n >> m;

    int total=0;
    vector<vector<int>> f(n+30);
    for(int i=1;i<=m;i++){
        int x,a,b;cin >> x >> a >> b;
        a=a*power(b,mod-2)%mod;
        total=(total+2*a)%mod;
        f[x].push_back(a);
    }

    vector<int> d={1};
    for(int i=0;i<=n+20;i++){
        int sz=((int)d.size()-1)/2+1;
        vector<int> nd(sz);
        for(int i=0;i<(int)d.size();i++) nd[i/2]=(nd[i/2]+d[i])%mod;
        swap(d,nd);

        sz=(int)f[i].size();
        if(sz){
            vector<vector<int>> P(sz);
            for(int j=0;j<sz;j++) P[j]={(mod+1-f[i][j])%mod,f[i][j]};

            priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
            for(int j=0;j<sz;j++) pq.push({(int)P[j].size(),j});
            while((int)pq.size()>1){
                auto [sx,x]=pq.top();pq.pop();
                auto [sy,y]=pq.top();pq.pop();
                P[x]=conv(P[x],P[y]);
                pq.push({(int)P[x].size(),x});
            }
            int x=pq.top().second;
            d=conv(d,P[x]);
        }

        for(int j=1;j<(int)d.size();j+=2) total=(total+mod-d[j])%mod;
    }
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    int test=1;//cin >> test;
    while(test--) solve();
}