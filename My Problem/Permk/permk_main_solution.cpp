#include<bits/stdc++.h>
using namespace std;
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

const int root = 3;
const int iroot = power(3,mod-2);
const int maxn = 2e5+5;

/*
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

typedef vector<ll> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		ll z[] = {1, power(root, mod >> s)};
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
vl mul(const vl &a, const vl &b) {
	if (a.empty() || b.empty()) return {};
	int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s),
	    n = 1 << B;
	int inv = power(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
*/

void fft(vector<int> &a,bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit){j^=bit;bit>>=1;}
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        int wn=power((invert?iroot:root),(mod-1)/len);
        for(int i=0;i<n;i+=len){
            int w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j],v=a[i+j+len/2]*w%mod;
                a[i+j]=(u+v)%mod;
                a[i+j+len/2]=(u-v+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(invert){
        int dd=power(n,mod-2);
        for(int i=0;i<n;i++) a[i]=a[i]*dd%mod;
    }
    return;
}
 
vector<int> mul(vector<int> &a,vector<int> &b){
    int n=(int)a.size()+(int)b.size(),sz=1;
    while(sz<n) sz<<=1;
    a.resize(sz);b.resize(sz);
    fft(a,false);fft(b,false);
    for(int i=0;i<sz;i++) a[i]=a[i]*b[i]%mod;
    fft(a,true);
    return a;
}

int fac[maxn],f[maxn],g[maxn];


void solve(){
    int n,k;cin >> n >> k;

    fac[0]=1;
    for(int i=1;i<=n;i++){
        fac[i]=fac[i-1]*i%mod;
        f[i]=fac[i];
        g[i]=0;
    }
    g[k]=f[k];

    function<void(int,int)> calf = [&](int l,int r){
        if(l==r) return;
        int mid=(l+r)>>1;
        calf(l,mid);
        vector<int> a(mid-l+1);
        for(int i=l;i<=mid;i++) a[i-l]=f[i];
        vector<int> b(r-l);
        for(int i=1;i<=r-l;i++) b[i-1]=fac[i];
        a=mul(a,b);
        for(int i=mid+1;i<=r;i++) if(i-l-1<(int)a.size()) f[i]=(f[i]-a[i-l-1]+mod)%mod;
        calf(mid+1,r);
    };
    calf(1,k);

    function<void(int,int)> calg = [&](int l,int r){
        if(l==r) return;
        int mid=(l+r)>>1;
        calg(l,mid);
        vector<int> a(mid-l+1);
        for(int i=l;i<=mid;i++) a[i-l]=g[i];
        vector<int> b(min(k,r-l));
        for(int i=1;i<=min(k,r-l);i++) b[i-1]=f[i];
        a=mul(a,b);
        for(int i=mid+1;i<=r;i++) if(i-l-1<(int)a.size()) g[i]=(g[i]+a[i-l-1])%mod;
        calg(mid+1,r);
    };
    calg(k,n);

    cout << g[n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}