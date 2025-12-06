#include<bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int L = 20;
const int maxn = 2e5+5;
int lg2[2*maxn];

struct SuffixArray {
	vi sa, lcp;

    vector<int> pos;
    vector<vector<int>> d;
	SuffixArray(string s, int lim=256) { // or vector<int>
		s.push_back(0); int n = sz(s), k = 0, a, b;
		vi x(all(s)), y(n), ws(max(n, lim));
		sa = lcp = y, iota(all(sa), 0);
		for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
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
        
        d.assign(n,vector<int>(L,0));
        pos.assign(n,-1);
        for(int i=0;i+1<n;i++) d[i][0]=lcp[i+1];
        for(int j=1;j<L;j++) for(int i=0;i+(1<<j)<=n;i++) d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
        for(int i=0;i<n;i++) pos[sa[i]]=i;
	}
    int cal(int x,int y){
        x=pos[x];y=pos[y];
        if(x>y) swap(x,y);
        int k=lg2[y-x];
        return min(d[x][k],d[y-(1<<k)][k]);
    }
};

void solve(){
    int n;
    string A,B;
    cin >> n >> A >> B;
    for(int i=2;i<=2*(n+1);i++) lg2[i]=lg2[i/2]+1;

    string s=A+"$"+B;
    reverse(A.begin(),A.end());
    reverse(B.begin(),B.end());
    string t=A+"$"+B;
    reverse(A.begin(),A.end());
    reverse(B.begin(),B.end());

    SuffixArray S(s),T(t);
    auto get_lcp = [&](int x,int i,int y,int j){
        if(x>=n || y>=n) return 0;
        int mx=n-max(x,y);
        x=(n+1)*i+x;
        y=(n+1)*j+y;
        return min(mx,S.cal(x,y));
    };
    auto get_lcs = [&](int x,int i,int y,int j){
        if(x<0 || y<0) return 0;
        int mx=min(x+1,y+1);
        x=(n+1)*i+n-1-x;
        y=(n+1)*j+n-1-y;
        return min(mx,T.cal(x,y));
    };
    for(int k=n;k>=2;k--){
        auto F = [&](int l){
            int r=l+k-1;

            int b=min(k,get_lcs(l-1,0,r,0));
            int a=min(k,get_lcp(l,0,r+1,0));
            if(a+b>=k) return true;
            int d=k-a-b;
            if(get_lcp(l+a,0,r+a,1)>=d) return true;

            b=min(k,get_lcs(l-1,1,r,1));
            a=min(k,get_lcp(l,1,r+1,1));
            if(a+b>=k) return true;
            d=k-a-b;
            if(get_lcs(l-b,0,r-b,1)>=d) return true;

            return false;
        };
        for(int i=0;i+k<=n;i+=k) if(F(i)){
            cout << 2*k << '\n';
            return;
        }
        if(F(n-k)){
            cout << 2*k << '\n';
            return;
        }
        auto G = [&](int l){
            int r=l+k-2;
            
            int b=get_lcs(l-1,0,r,1);
            int a=get_lcp(l,0,r+1,1);
            if(a+b>=k) return true;

            int d=k-a-b;
            if(a && get_lcp(l+a-1,1,r+a+1,1)>=d) return true;
            if(b && get_lcs(r-b+1,0,l-b-1,0)>=d) return true;

            return false;
        };
        for(int i=0;i+k-1<=n;i+=k-1) if(G(i)){
            cout << 2*k << '\n';
            return;
        }
        if(G(n-k+1)){
            cout << 2*k << '\n';
            return;
        }
    }

    for(int i=0;i<n;i++) if(A[i]==B[i]){
        cout << 2 << '\n';
        return;
    }
    for(int i=0;i+1<n;i++) if(A[i]==A[i+1] || B[i]==B[i+1]){
        cout << 2 << '\n';
        return;
    }
    cout << 0 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
