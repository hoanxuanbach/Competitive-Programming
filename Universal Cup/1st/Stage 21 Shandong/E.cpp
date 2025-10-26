#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define ll long long 

struct Line {
	mutable ll k, m;
    mutable double p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(double x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const double inf = 1/0.0;
	double div(ll a, ll b) { // floored division
		return (double)a/b;
    }
	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x,ll y){
		assert(!empty());
		auto l = *lower_bound((double)x/y);
		return l.k*x + l.m*y;
	}
};

const int inf = LLONG_MAX;

void solve(){
    int n,k;cin >> n >> k;    
    vector<int> x(n),y(n);
    for(int i=0;i<n;i++) cin >> x[i] >> y[i],x.push_back(x[i]),y.push_back(y[i]);

    int total=0;
    vector<int> val(n);
    for(int i=0;i<k;i++) total+=x[i]*y[i+1]-x[i+1]*y[i];

    vector<int> qx(n),qy(n),res(n);

    for(int b=0;b<n;b++){
        val[b]=total;
        int c=(b+k)%n;
        int nb=(b+1)%n,nc=(c+1)%n;
        total-=x[b]*y[nb]-x[nb]*y[b];
        total+=x[c]*y[nc]-x[nc]*y[c];
        qx[nc]=x[c]-x[b];
        qy[nc]=y[b]-y[c];
    }

    vector<int> mx(8*n),mn(8*n);
    vector<LineContainer> cht0(8*n),cht1(8*n);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        mx[id]=-inf;mn[id]=inf;
        for(int i=l;i<=r;i++){
            mx[id]=max(mx[id],y[i]);
            mn[id]=min(mn[id],y[i]);
            cht0[id].add(y[i],x[i]);
            cht1[id].add(y[i],-x[i]);
        }
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    };
    build(0,2*n-1,1);

    function<int(int,int,int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr,int X,int Y){
        if(tr<l || r<tl) return -inf;
        if(tl<=l && r<=tr){
            if(Y==0) return max(mx[id]*X,mn[id]*X);
            else if(Y>0) return cht0[id].query(X,Y);
            else return cht1[id].query(X,-Y);
        }
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr,X,Y),query(mid+1,r,id<<1|1,tl,tr,X,Y));
    };

    for(int i=0;i<n;i++) res[i]=query(0,2*n-1,1,i,i+n-k-2,qx[i],qy[i]);

    int ans=0;
    for(int b=0;b<n;b++){
        ans=max(ans,val[b]+res[(b+k+1)%n]);
    }
    cout << ans/2;
    if(ans&1) cout << ".5\n";
    else cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}