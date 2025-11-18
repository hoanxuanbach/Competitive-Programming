#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mod = (119 << 23) + 1, root = 62; // = 998244353

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vector<ll> vl;
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

int fac[maxn],dfac[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=modpow(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}

int C(int n,int k){
    if(n<0 || k<0 || n<k) return 0;
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

void solve(){
    int n;cin >> n;
    combi(n);
    vector<int> x(n),y(n);
    for(int i=0;i<n;i++) cin >> x[i] >> y[n-1-i];
    for(int i=0;i<n;i++) x[i]=(x[i]%mod+mod)%mod,y[i]=(y[i]%mod+mod)%mod;
    vector<int> A=conv(x,y),f(n+1);

    vector<int> aX(n),aY(n);    
    for(int d=1;d<n;d++){
        //x[i]*y[j] j-i == d f[k] += (C(n-(d+1),k-2)-C(d-1,k-2))*A[n-1-d]
        //x[i]*y[j] i-j == d f[k] += (C(d-1,k-2)-C(n-(d+1),k-2))*A[n-1+d]
        int val=(A[n-1-d]-A[n-1+d]+mod)%mod;

        int X=val*fac[n-d-1]%mod;
        int Y=val*fac[d-1]%mod;
        aX[d]=X;aY[d]=Y;
        //f[k] += X*dfac[n+1-d-k]
        //f[k] -= Y*dfac[d-k+1]

        /*
        for(int k=3;k<=n;k++){
            int mul=(C(n-d-1,k-2)-C(d-1,k-2)+mod)%mod;
            f[k]=(f[k]+mul*val)%mod;
        }
        */
    }
    vector<int> bX(n+1);
    for(int i=0;i<=n;i++) bX[i]=dfac[i];
    aX=conv(aX,bX);
    for(int k=3;k<=n;k++) f[k]=(f[k]+aX[n+1-k])%mod;

    vector<int> bY(n+1);
    for(int i=0;i<=n;i++) bY[i]=dfac[n-i];
    aY=conv(aY,bY);
    for(int k=3;k<=n;k++) f[k]=(f[k]-aY[n+k-1]+mod)%mod;


    for(int k=3;k<=n;k++) cout << f[k]*dfac[k-2]%mod << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
