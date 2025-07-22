#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2=(mod+1)/2;
const int maxn = 4e3+5;
const int maxa = 1e6+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef vector<int> vi;

const int root=3;
const int iroot=power(3,mod-2);
typedef vector<int> vl;
void ntt(vl &a) {
	int n = sz(a), L = 31 - __builtin_clz(n);
	static vl rt(2, 1);
	for (static int k = 2, s = 2; k < n; k *= 2, s++) {
		rt.resize(n);
		int z[] = {1, power(root, mod >> s)};
		rep(i,k,2*k) rt[i] = rt[i / 2] * z[i & 1] % mod;
	}
	vl rev(n);
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
	int inv = power(n, mod - 2);
	vl L(a), R(b), out(n);
	L.resize(n), R.resize(n);
	ntt(L), ntt(R);
	rep(i,0,n)
		out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
	ntt(out);
	return {out.begin(), out.begin() + s};
}
 
const int N = 2000;
int D[maxn][maxn];

void init(){
    combi(2*N);
    D[0][0]=1;
    for(int i=1;i<=N;i++){
        for(int k=1;k<=i;k++){
            D[i][k]=C(2*i,i);
            for(int j=1;(j-1)*(k+1)<=i;j++){
                D[i][k]+=2*C(2*i,i+j+j*(k+1))-C(2*i,i+j+(j-1)*(k+1))-C(2*i,i+(j-1)+j*(k+1));
            }
            D[i][k]%=mod;
        }
    }
}

void solve(){   
    int n;cin >> n;
    string s;cin >> s;
    s="."+s;

    vector<int> pos;
    for(int i=1;i<=n;i++) if(s[i]=='g') pos.push_back(i);
    int sz=(int)pos.size();
    
    vector<int> dp(n+1);dp[1]=1;
    int total=(n==1?1:0);
    for(int i=2;i<=n;i++){
        vector<int> ndp(n+1);
        auto cal = [&](int x,int y){
            while(x<y && !dp[x]) x++;
            if(x==y) return;
            vector<int> a(dp.begin()+x,dp.begin()+y),b(y-x);
            for(int j=0;j<y-x;j+=2) b[j]=D[j/2][min(j/2,i-1)];
            
            a=conv(a,b);

            for(int j=x+1;j<=y;j++){
                if(s[j]=='e') continue;
                ndp[j]=a[j-x-1];
            }
        };
        for(int j=1;j<min(i,sz);j++) cal(pos[j-1],pos[j]);
        swap(dp,ndp);
        total=(total+dp[n])%mod;
    }
    total=(total%mod+mod)%mod;
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    init();
    int test=1;cin >> test;
    while(test--) solve();
}