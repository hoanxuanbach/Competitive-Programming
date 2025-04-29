#include<bits/stdc++.h>
#define pb push_back
#define fi first
#define se second 
using namespace std;
typedef long long ll;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef pair<ll, ll> pii;
typedef vector<ll> vi;
const int maxn=1<<17;
const int mod=998244353;
int n;
int cnt[maxn];
ll fact[maxn];
ll invfact[maxn];
ll inv[maxn];
ll po2[maxn];
ll C(ll a,ll b){
	if(a<b || b<0 || a<0)return 0;
	return fact[a]*invfact[b]%mod*invfact[a-b]%mod;
}
void FST(vi& a, bool inv1) {
	for (int n = sz(a), step = 1; step < n; step *= 2) {
		for (int i = 0; i < n; i += 2 * step) rep(j,i,i+step) {
			ll &u = a[j], &v = a[j + step]; tie(u, v) = pii((u + v)%mod, ((u-v)%mod+mod)%mod );                   // XOR /// include-line
		}
	}
	if (inv1) for (ll& x : a) x =(x* inv[sz(a)]%mod); // XOR only /// include-line
}
vi conv(vi a, vi b) {
	FST(a, 0); FST(b, 0);
	rep(i,0,sz(a)) a[i] =(a[i]* b[i])%mod;
	FST(a, 1); return a;
}
void add(ll &x,ll val){
	x+=val;
	if(x>=mod)x-=mod;
	if(x<0)x+=mod;
}
array<vector<ll>,2> build(int bit,int l,int r){
	if(bit==0){
		array<vector<ll>,2>k;
		ll sz0=0;
		ll sz1=0;
		for(int i=0;i<=cnt[l];i++){
			if(i&1){
				add(sz1,C(cnt[l],i)*po2[i]%mod);
			}
			else{
				add(sz0,C(cnt[l],i)*po2[i]%mod);
			}
		}
		if((l&1)==0){
			k[0].pb(sz0);
			k[1].pb(sz1);
		}
		else{
			k[0].pb(sz0);
			k[1].pb(sz1);
		}
		return k;
	}
	else{
		array<vector<ll>,2>a=build(bit-1,l,(l+r)/2);
		array<vector<ll>,2>b=build(bit-1,(l+r)/2+1,r);
		array<vector<ll>,2>k;
		int sz=(r-l+1);
		k[0].assign(sz,0);
		k[1].assign(sz,0);
		vi p=conv(a[0],b[0]);
		for(int i=0;i<sz/2;i++){
			add(k[0][i],p[i]);
		}
		vi p1=conv(a[0],b[1]);
		for(int i=sz/2;i<sz;i++){
			add(k[1][i],p1[i-sz/2]);
		}
		vi p2=conv(a[1],b[0]);
		for(int i=0;i<sz/2;i++){
			add(k[1][i],p2[i]);
		}
		vi p3=conv(a[1],b[1]);
		for(int i=sz/2;i<sz;i++){
			add(k[0][i],p3[i-sz/2]);
		}
		return k;
	}
}
signed main(){
	//freopen("input.inp","r",stdin);
	//freopen("output.out","w",stdout);
	cin.tie(0),cout.tie(0)->sync_with_stdio(0);
	cin >> n;
	invfact[0]=invfact[1]=inv[0]=inv[1]=fact[0]=fact[1]=1;
	po2[0]=1;
	po2[1]=2;
	for(int i=2;i<maxn;i++){
		po2[i]=po2[i-1]*2%mod;
		inv[i]=mod-mod/i*inv[mod%i]%mod;
		invfact[i]=invfact[i-1]*inv[i]%mod;
		fact[i]=fact[i-1]*i%mod;
	}
	for(int i=1;i<=n;i++){
		int x;
		cin >> x;
		cnt[x]++;
	}	
	array<vector<ll>,2>k=build(17,0,(1<<17)-1);
	cout << (k[0][0]+k[1][0])%mod << '\n';
}