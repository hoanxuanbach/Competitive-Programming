#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll mod = (119 << 23) + 1, root = 62; // = 998244353
// For p < 2^30 there is a lso e . g . 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root) . The l as t two are > 10^9.

ll power(ll a,ll n){
    ll res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

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
vl conv(const vl &a, const vl &b) {
    if (a.empty() || b.empty()) return {};
    int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
    int inv = power(n, mod - 2);
    vl L(a), R(b), out(n);
    L.resize(n), R.resize(n);
    ntt(L), ntt(R);
    rep(i,0,n)
        out[-i & (n - 1)] = (ll)L[i] * R[i] % mod * inv % mod;
    ntt(out);
    return {out.begin(), out.begin() + s};
}


#define int long long 
#define pii pair<int,int>
 
const int maxn = 4e6+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

int fac[maxn],dfac[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;
}
void solve(){
    int U,T,P,C;cin >> U >> T >> P >> C;
    combi(U+T+P+C);

    int M=((U*2+T)*C)/(C+1);
    
    int S=U+T;

    int m=1;
    while(m<=S+2*P+2) m<<=1;
    int inv=power(m,mod-2);


    vector<int> fA(m),gA(m);
    for(int k=0;k<=P;k++) fA[P-k]=dfac[k]*dfac[P-k]%mod;
    for(int x=0;x<=S+P;x++) gA[x]=fac[x+C]*fac[S+P-x]%mod;
    ntt(fA);ntt(gA);
    //fA=conv(fA,gA);

    vector<int> fB(m),gB(m);
    for(int k=0;k<P;k++) fB[P-k]=dfac[k]*dfac[P-k-1]%mod;
    for(int x=0;x<S+P;x++) gB[x]=fac[x+C]*fac[S+P-x-1]%mod;
    ntt(fB);ntt(gB);
    //fB=conv(fB,gB);

    vector<int> A(m),B(m),F(m);
    for(int i=0;i<m;i++) A[-i&(m-1)]=fA[i]*gA[i]%mod*inv%mod;
    for(int i=0;i<m;i++) B[-i&(m-1)]=fB[i]*gB[i]%mod*inv%mod;
    for(int i=0;i<m;i++) F[-i&(m-i)]=fA[i]*gB[i]%mod*inv%mod;
    ntt(A);ntt(B);ntt(F);

    /*
    vector<int> fC(P+1),gC(S+P+1);
    for(int k=0;k<=P;k++) fC[P-k]=dfac[k]*dfac[P-k]%mod;
    for(int x=0;x<S+P;x++) gC[x]=fac[x+C]*fac[S+P-x-1]%mod;
    fC=conv(fC,gC);
    */

    int res=0;
    for(int i=0;2*i<=M && i<=U;i++){
        int j=M-2*i;
        if(j<=T){
            int all=dfac[i]*dfac[j]%mod*dfac[U-i]%mod*dfac[T-j]%mod;
            int s=i+j;

            int val=(A[P+s]-B[P+s]+mod)%mod;

            val=val*(2*U+T-M)%mod;
            res=(res+all*val)%mod;
        }

        j=M-2*i-1;  
        if(i<U && j>=0 && j<=T){
            int all=dfac[i]%mod*dfac[j]%mod*dfac[U-i-1]%mod*dfac[T-j]%mod;
            int s=i+j;
            

            int val=F[s+P];
            
            val=val*(2*U+T-M+1)%mod;
            res=(res+all*val)%mod;
        }
    }
    res=res*dfac[U+T+P+C]%mod*fac[U]%mod*fac[T]%mod*fac[P]%mod;
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}