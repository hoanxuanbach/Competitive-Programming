#include<bits/stdc++.h>
using namespace std;


#define ll long long 
struct Line {
	mutable ll k, m, p;
    ll id=-1;
	bool operator<(const Line& o) const {
        if(k!=o.k) return k < o.k;
        else return id<o.id; 
    }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
    
    ll I=-1,L=-1,R=-1;

	bool isect(iterator x, iterator y) {
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);

        if(y->id==I) L=x->p+1;
        if(x->id==I) R=x->p;

		return x->p >= y->p;
	}
	void add(ll k, ll m,int id) {
        I=id;
		auto z = insert({k, m, 0, id}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));

        L=R=-1;
        auto it = lower_bound({k,m,0,id});
        if(it!=end() && it->id==id){
            R=it->p;
            if(it!=begin()){
                --it;
                L=it->p+1;
            }
        }
	}
	ll query(ll x) {
		assert(!empty());
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

#define int long long 
const int inf = 9e18;

void solve(){
    int n,q;cin >> n >> q;  
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    
    vector<int> total(4*n),sum(4*n),val(4*n),cnt(4*n),V(4*n,-1),T(4*n,-1);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            total[id]=sum[id]=a[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        sum[id]=sum[id<<1]+sum[id<<1|1];total[id]=sum[id];
    };
    function<void(int,int,int)> getnew = [&](int id,int v,int t){
        total[id]=sum[id]+v*cnt[id]-t*val[id];
        V[id]=v;T[id]=t;
    };
    function<void(int)> pushdown = [&](int id){
        if(V[id]==-1) return;
        getnew(id<<1,V[id],T[id]);
        getnew(id<<1|1,V[id],T[id]);
        V[id]=T[id]=-1;
    };
    function<void(int,int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int v,int t){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,v,t);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,v,t);update(mid+1,r,id<<1|1,tl,tr,v,t);
        sum[id]=sum[id<<1]+sum[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
        val[id]=val[id<<1]+val[id<<1|1];
        total[id]=total[id<<1]+total[id<<1|1];
        //cout << "update " << l << ' ' << r << ' ' << id << ' ' << V[id] << ' ' << T[id] << ' ' << total[id] << ' ' << cnt[id] << ' ' << val[id] << ' ' << sum[id] << endl;
    };
    function<int(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return 0LL;
        if(tl<=l && r<=tr) return total[id];
        pushdown(id);
        int mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    };
    function<void(int,int,int,int)> fix = [&](int l,int r,int id,int x){
        if(l==r){
            sum[id]=0;
            cnt[id]=1;
            val[id]=x;
            total[id]=V[id]-T[id]*x;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) fix(l,mid,id<<1,x);
        else fix(mid+1,r,id<<1|1,x);
        sum[id]=sum[id<<1]+sum[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
        val[id]=val[id<<1]+val[id<<1|1];
        total[id]=total[id<<1]+total[id<<1|1];
    };
    build(1,n,1);

    int k=0;
    vector<int> op(q),A(q),B(q);
    for(int i=0;i<q;i++){
        cin >> op[i];
        if(op[i]==1) cin >> A[i],B[i]=k;
        else if(op[i]==3) cin >> A[i] >> B[i];
        else k++;
    }

    vector<LineContainer> cht(4*q);
    function<void(int,int,int)> buildcht = [&](int l,int r,int id){
        for(int i=l;i<=r;i++) if(op[i]==1) cht[id].add(B[i],-A[i],i);
        if(l==r) return;
        int mid=(l+r)>>1;
        buildcht(l,mid,id<<1);buildcht(mid+1,r,id<<1|1);
    };
    buildcht(0,q-1,1);
    function<int(int,int,int,int,int)> get = [&](int l,int r,int id,int x,int p){
        if(cht[id].empty() || x+cht[id].query(p)<=0) return r+1;
        if(l==r) return l;
        int mid=(l+r)>>1;
        if(!cht[id<<1].empty() && x+cht[id<<1].query(p)>0) return get(l,mid,id<<1,x,p);
        else return get(mid+1,r,id<<1|1,x,p);
    };

    vector<vector<int>> f(q);
    for(int i=1;i<=n;i++){
        int lst=get(0,q-1,1,a[i],i);
        if(lst<q) f[lst].push_back(i);
    }   

    k=0;
    LineContainer cur;

    vector<bool> del(n+1);
    vector<int> cc(n+1,inf);
    for(int i=0;i<q;i++){
        for(int id:f[i]) fix(1,n,1,id),del[id]=true;
        if(op[i]==1){
            cur.add(k,-A[i],i);
            int lt=max(cur.L,1LL);
            int rt=min(cur.R,n);
            //cout << A[i] << ' '<< k << ' ' << lt << ' ' << rt << '\n';
            //for(int j=lt;j<=rt;j++) cc[j]=A[i]-k*j;

            if(lt<=rt) update(1,n,1,lt,rt,A[i],k);
        }
        else if(op[i]==2) k++;
        else{
            int res=k*(A[i]+B[i])*(B[i]-A[i]+1)/2;
            res+=query(1,n,1,A[i],B[i]);
            cout << res << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}