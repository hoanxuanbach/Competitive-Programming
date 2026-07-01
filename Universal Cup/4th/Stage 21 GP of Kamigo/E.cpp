#include<bits/stdc++.h>
using namespace std;

const int LG = 20;
const int maxn = 5e5+5;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits) { // (optional)
	//this is just 3 times faster than stl sort for N=10^6
	int mask = (1 << bits) - 1;
	rep(it,0,2) {
		int move = it * bits;
		vi q(1 << bits), w(sz(q) + 1);
		rep(i,0,sz(b))
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pli> res(b.size());
		rep(i,0,sz(b))
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}

int lg2[maxn];
struct SuffixArray {
	vi a,s,inv;
    vector<vi> T;
	SuffixArray(vector<int> & _s) : s(_s) {
        s.push_back(0);
		int N = sz(s);
		vector<pli> b(N);
		a.resize(N);
		rep(i,0,N) {
			b[i].first = s[i];
			b[i].second = i;
		}

		int q = 8;
		while ((1 << q) < N) q++;
		for (int moc = 0;; moc++) {
			count_sort(b, q); // sort(all(b)) can be used as well
			a[b[0].second] = 0;
			rep(i,1,N)
				a[b[i].second] = a[b[i - 1].second] +
					(b[i - 1].first != b[i].first);

			if ((1 << moc) >= N) break;
			rep(i,0,N) {
				b[i].first = (ll)a[i] << q;
				if (i + (1 << moc) < N)
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		rep(i,0,sz(a)) a[i] = b[i].second;
        //cout << "Suffix Array" << endl;
        lcp();
	}
	void lcp() {
		// longest common prefixes: res[i] = lcp(a[i], a[i-1])
		int n = sz(a), h = 0;
        inv.assign(n,0);
        T.assign(LG,vector<int>(n,0));
		rep(i,0,n) inv[a[i]] = i;
		rep(i,0,n) if (inv[i] > 0) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			T[0][inv[i]] = h;
			if(h > 0) h--;
		}

        for(int j=1;j<LG;j++) for(int i=0;i<=n-(1<<j);i++) T[j][i]=min(T[j-1][i],T[j-1][i+(1<<(j-1))]);
        //cout << "lcp" << endl;
        //for(int i=0;i<n;i++) cout << a[i] << ' ';
        //cout << '\n';
        //for(int i=0;i<n;i++) cout << T[0][i] << ' ';
        //cout << '\n';
	}
    int query(int l,int r){
        l=inv[l];r=inv[r];
        if(l>r) swap(l,r);
        l++;
        int k=lg2[r-l+1];
        return min(T[k][l],T[k][r-(1<<k)+1]);
    }
};

//#define int long long 
//#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
//const int maxn = 2e5+5;
//const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

struct Fast{
    int val[maxn];

    int p[maxn],sz[maxn],mx[maxn];

    void init(int N){
        for(int i=0;i<=N+1;i++){
            val[i]=N;
            p[i]=mx[i]=i;
            sz[i]=1;
        } 
    }
    int ff(int u){
        if(u!=p[u]) return p[u]=ff(p[u]);
        return u;
    }
    int unite(int u,int v){
        u=ff(u);v=ff(v);
        if(u!=v){
            if(sz[u]<sz[v]) swap(u,v);
            sz[u]+=sz[v];p[v]=u;
            mx[u]=max(mx[u],mx[v]);
        }
        return u;
    }
    void update(int l,int r,int d){
        if(l>r) return;

        int x=mx[ff(l)];
        while(x<=r){
            val[x]=d;
            x=mx[unite(x,x+1)];
        }
    }
}L,R;

void solve(){
    int N;cin >> N;
    vector<int> S(N);
    for(int i=0;i<N;i++){
       cin >> S[i];
    }
    for(int i=2;i<=N+1;i++) lg2[i]=lg2[i/2]+1;

    SuffixArray A(S);
    reverse(S.begin(),S.end());
    SuffixArray B(S);
    auto query_lcp = [&](int i,int j){
        return A.query(i,j);
    };
    auto query_lcs = [&](int i,int j){
        i=N-i;j=N-j;
        return B.query(i,j);
    };

    vector<pii> fl(N+1),fr(N+1);
    L.init(N);R.init(N);
    for(int d=1;d<N;d++){
        for(int i=d;i+d<=N;i+=d){
            int rt=min(d-1,query_lcp(i,i+d));
            int lt=min(d,query_lcs(i,i+d));
            //cout << '*' << i << ' ' << d << ' ' << lt << ' ' << rt << '\n';
            fl[i-d]={i-lt,i+rt-d};
            fr[i+d]={i-lt+2*d,i+d+rt};
        }
        for(int i=0;i+2*d<=N;i+=d){
            int l=fl[i].first,r=fl[i].second;
            L.update(l,r,d);
        }
        for(int i=3*d;i<=N;i+=d){
            int l=max(fr[i].first,fr[i-d].first+d),r=min(fr[i].second,fr[i-d].second+d);
            R.update(l,r,d);
        }
    }


    //for(int i=0;i<=N;i++) cout << L[i] << ' ' << R[i] << '\n';

    vector<vector<int>> mn(LG,vector<int>(N,N));
    for(int i=1;i<N;i++){
        int l=i-3*R.val[i],r=i+2*L.val[i]-1;
        if(l<0 || r>=N) continue;
        //cout << '*' << i << ' ' << l << ' ' << r << '\n';
        mn[0][l]=min(mn[0][l],r);
    }

    for(int j=1;j<LG;j++) for(int i=0;i<=N-(1<<j);i++) mn[j][i]=min(mn[j-1][i],mn[j-1][i+(1<<(j-1))]);
    auto query = [&](int l,int r){
        int k=lg2[r-l+1];
        return min(mn[k][l],mn[k][r-(1<<k)+1]);
    };

    int Q;cin >> Q;
    for(int i=0;i<Q;i++){
        int l,r;cin >> l >> r;l--;r--;
        if(query(l,r)<=r) cout << "Yes\n";
        else cout << "No\n";
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}