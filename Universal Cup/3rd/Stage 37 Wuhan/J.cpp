#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e9;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


struct SuffixArray {
	vi sa, lcp;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1LL,j*2), lim = p) {
			p = j, iota(all(y), n - j);
			rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
			fill(all(ws), 0);
			rep(i,0,n) ws[x[i]]++;
			rep(i,1,lim) ws[i] += ws[i - 1];
			for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
			swap(x, y), p = 1, x[sa[0]] = 0;
			rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
				(y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
		}
		for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
			for (k && k--, j = sa[x[i] - 1];
					s[i + k] == s[j + k]; k++);
	}
};

const int LG = 18;
void solve(){
    string S;cin >> S;
    SuffixArray SA(S);
    int n=(int)S.length();
    vector<int> s(SA.sa.begin()+1,SA.sa.end()),lcp(SA.lcp.begin()+1,SA.lcp.end());

    int total=0;
    for(int i=0;i<n;i++) total+=n-s[i]-lcp[i];

    vector<int> p(n),d(n);
    for(int i=0;i<n;i++) p[s[i]]=i,d[i]=n-s[i];

    vector<vector<int>> val(n,vector<int>(LG,0));
    for(int i=0;i<n;i++) val[i][0]=lcp[i];
    for(int i=1;i<LG;i++) for(int j=0;j<=n-(1<<i);j++) val[j][i]=min(val[j][i-1],val[j+(1<<(i-1))][i-1]);

    vector<int> tree(4*n),mn(4*n),mx(4*n),lst(4*n),fst(4*n);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            mn[id]=mx[id]=lst[id]=fst[id]=d[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=(tree[id<<1]+tree[id<<1|1]+fst[id<<1|1]-min({lst[id<<1],fst[id<<1|1],lcp[mid+1]}));
        lst[id]=lst[id<<1|1];
        fst[id]=fst[id<<1];
        mn[id]=min(mn[id<<1],mn[id<<1|1]);
        mx[id]=max(mx[id<<1],mx[id<<1|1]);
    };
    build(0,n-1,1);
    function<void(int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int k){
        if(tr<l || r<tl || mx[id]<=k) return;
        if(tl<=l && r<=tr){
            if(mn[id]>=k){
                fst[id]=lst[id]=mn[id]=mx[id]=k;
                tree[id]=0;
                return;
            }
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,k);update(mid+1,r,id<<1|1,tl,tr,k);
        tree[id]=(tree[id<<1]+tree[id<<1|1]+fst[id<<1|1]-min({lst[id<<1],fst[id<<1|1],lcp[mid+1]}));
        lst[id]=lst[id<<1|1];
        fst[id]=fst[id<<1];
        mn[id]=min(mn[id<<1],mn[id<<1|1]);
        mx[id]=max(mx[id<<1],mx[id<<1|1]);
    };

    int q;cin >> q;
    for(int i=0;i<q;i++){
        int l,r;cin >> l >> r;l--;r--;
        int x=p[l],k=r-l;

        int lt=x,rt=x;
        for(int j=LG-1;j>=0;j--){
            if(lt-(1<<j)<0) continue;
            if(val[lt-(1<<j)+1][j]>k) lt-=(1<<j);
        }
        for(int j=LG-1;j>=0;j--){
            if(rt+(1<<j)>=n) continue;
            if(val[rt+1][j]>k) rt+=(1<<j);
        }
        update(0,n-1,1,lt,rt,k);
        cout << total-tree[1]-fst[1] << ' ';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}