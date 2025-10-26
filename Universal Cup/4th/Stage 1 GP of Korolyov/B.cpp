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
const int inv2 = (mod+1)/2;

void solve(){
    int n;cin >> n;
    vector<vector<int>> g(n+1);
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> cnt(n+1);

    vector<int> d(n+1);
    vector<bool> used(n+1);

    int S=0;
    vector<int> ss(n+1);

    int D=0;
    vector<int> cc(n+1);

    function<void(int,int)> pre_dfs = [&](int u,int p){
        ss[u]=1;
        for(int v:g[u]){
            if(v==p || used[v]) continue;
            pre_dfs(v,u);ss[u]+=ss[v];
        }
    };
    function<int(int,int)> get_centroid = [&](int u,int p){
        for(int v:g[u]){
            if(v==p || used[v]) continue;
            if(ss[v]>S/2) return get_centroid(v,u);
        }
        return u;
    };
    function<void(int,int)> dfs = [&](int u,int p){
        d[u]=d[p]+1;
        cc[d[u]]++;
        cnt[d[u]]++;
        D=max(D,d[u]);
        for(int v:g[u]){
            if(v==p || used[v]) continue;
            dfs(v,u);
        }
    };

    auto cal = [&](vector<int> &v,int delta){
        vector<int> a=conv(v,v);
        int d=(int)v.size();
        for(int i=0;i<d;i++) a[2*i]-=v[i];
        for(int i=0;i+1<min(n,2*d);i++){
            a[i]=a[i]*inv2%mod;
            cnt[i+2]+=a[i]*delta;
        }
    };

    function<void(int)> decompose = [&](int u){
        pre_dfs(u,0);S=ss[u];
        int x=get_centroid(u,0);
        used[x]=true;d[x]=0;

        vector<vector<int>> A;

        int K=0;
        for(int v:g[x]){
            if(used[v]) continue;
            D=0;dfs(v,x);
            K=max(K,D);
            vector<int> cur(D);
            for(int i=0;i<D;i++) cur[i]=cc[i+1],cc[i+1]=0;
            A.push_back(cur);
        }

        vector<int> total(K);
        for(auto v:A){
            int D=(int)v.size();
            for(int i=0;i<D;i++) total[i]+=v[i];
            cal(v,-1);
        }
        cal(total,1);

        for(int v:g[x]) if(!used[v]) decompose(v);
    };
    decompose(1);

    vector<int> fac(n+1);
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;

    vector<int> dfac(n+1);
    dfac[n]=modpow(fac[n],mod-2);
    for(int i=n;i>=1;i--) dfac[i-1]=dfac[i]*i%mod;

    for(int i=1;i<n;i++) cnt[i]=cnt[i]*fac[n-i-1]%mod;


    vector<int> mul(n+1);
    for(int i=0;i<=n;i++) mul[i]=dfac[i];

    cnt=conv(cnt,mul);
    for(int i=1;i<=n-2;i++){
        int res=cnt[i+1];
        res=res*dfac[n-i-2]%mod;
        res=res*fac[i]%mod;
        cout << res << ' ';
    }
    cout << "0 0\n";
}   

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}