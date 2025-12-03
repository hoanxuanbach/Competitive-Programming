#include<bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = b * b % mod, e /= 2)
		if (e & 1) ans = ans * b % mod;
	return ans;
}

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
const int inf = 1e18;

void solve(){
    string S;cin >> S;
    int n=(int)S.length();
    vector<int> A(n),B(n);

    int cnt=0;
    for(char c:S) cnt+=(c=='Y');
    for(int i=0;i<n;i++){
        if(S[i]=='Y') A[i]=cnt,cnt--;
        else if(S[i]=='B') cnt++;
    }
    cnt=0;
    for(int i=n-1;i>=0;i--){
        if(S[i]=='R') cnt++,B[i]=cnt;
        else if(S[i]=='Y') cnt--;
    }

    vector<int> X(n+1);
    function<void(int,int)> dnc = [&](int l,int r){
        if(l==r) return;
        int m=(l+r)>>1;
        dnc(l,m);dnc(m+1,r);

        int lA=inf,rA=-inf,lB=inf,rB=-inf;
        for(int i=l;i<=m;i++) if(S[i]=='Y') lA=min(lA,A[i]),rA=max(rA,A[i]);
        for(int i=m+1;i<=r;i++) if(S[i]=='R') lB=min(lB,B[i]),rB=max(rB,B[i]);

        if(lA==inf || lB==inf) return;
        int sA=rA-lA+1,sB=rB-lB+1;

        vector<int> a(sA),b(sB);
        for(int i=l;i<=m;i++) if(S[i]=='Y') a[A[i]-lA]++;
        for(int i=m+1;i<=r;i++) if(S[i]=='R') b[B[i]-lB]++;

        a=conv(a,b);
        int sz=(int)a.size();
        for(int i=0;i<sz;i++) if(a[i]) X[lA+lB+i]=(X[lA+lB+i]+a[i])%mod;
    };
    dnc(0,n-1);

    vector<int> fac(n+1,1),dfac(n+1);
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=modpow(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
    auto C = [&](int N,int K){
        if(N<0 || K<0 || N<K) return 0LL;
        return fac[N]*dfac[K]%mod*dfac[N-K]%mod;
    };

    vector<int> D(n+1),f(n+1);
    A.assign(n,0);cnt=0;
    for(int i=0;i<n;i++){
        cnt+=(S[i]=='B');
        A[i]=cnt;
    }
    for(int i=1;i<=cnt;i++) f[i]=(f[i]-C(cnt,i)+mod)%mod;
    
    cnt=0;
    for(int i=n-1;i>=0;i--){
        if(S[i]=='B') D[A[i]+cnt]++;
        cnt+=(S[i]=='R');
    }
    for(int i=1;i<=cnt;i++) f[i]=(f[i]+C(cnt,i))%mod;

    cnt=0;
    for(int i=n-1;i>=0;i--){
        if(S[i]=='B') D[A[i]+cnt]++;
        cnt+=(S[i]=='Y');
    }
    for(int i=1;i<=cnt;i++) f[i]=(f[i]+C(cnt,i))%mod;

    vector<int> g(n+1);
    for(int i=0;i<=n;i++) g[i]=dfac[n-i];

    for(int i=1;i<=n;i++) D[i]=D[i]*fac[i-1]%mod;
    D=conv(D,g);
    for(int j=1;j<=n;j++) f[j]=(f[j]+D[n+j]*dfac[j-1])%mod;

    for(int i=2;i<=n;i++) X[i]=X[i]*fac[i-2]%mod;
    X=conv(X,g);
    for(int j=2;j<=n;j++) f[j]=(f[j]+X[n+j]*dfac[j-2])%mod;

    int res=0;
    for(int i=1;i<=n;i++) res=(res+f[i]*fac[i]%mod*fac[n-i]%mod+mod)%mod;
    res=(n-res*dfac[n]%mod+mod)%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
