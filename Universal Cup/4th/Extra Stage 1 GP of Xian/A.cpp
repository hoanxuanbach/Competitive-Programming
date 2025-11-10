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
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

template<class T> 
struct Compress{
    int sz;
    vector<T> com;
    Compress(vector<T> _com):com(_com){
        sort(com.begin(),com.end());
        com.erase(unique(com.begin(),com.end()),com.end());
        sz=(int)com.size();
    }
    int get(T x){
        return lower_bound(com.begin(),com.end(),x)-com.begin()+1;
    }
};

struct SegtreeB{
    int n;
    vector<int> tree,cnt;
    SegtreeB(int _n=0):n(_n){
        tree.assign(4*n,-inf);
        cnt.assign(4*n,0);
    }
    void update(int l,int r,int id,int x,int val){
        if(l==r){
            cnt[id]^=1;
            if(cnt[id]) tree[id]=val;
            else tree[id]=-inf;
            return;
        }
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x,val);
        else update(mid+1,r,id<<1|1,x,val);
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    }
    pii query(int l,int r,int id,int x){
        if(l==r){
            if(x>l) return pii{cnt[id],-inf};
            else return pii{0,tree[id]};
        }
        int mid=(l+r)>>1;
        if(x<=mid){
            pii val=query(l,mid,id<<1,x);
            val.second=max(val.second,tree[id<<1|1]);
            return val;
        }
        else{
            pii val=query(mid+1,r,id<<1|1,x);
            val.first+=cnt[id<<1];
            return val;
        }
    }
};

struct SegtreeC{
    int n;
    vector<pii> tree;
    vector<int> lazy;
    SegtreeC(int _n=0):n(_n){
        tree.assign(4*n,pii{0,0});
        lazy.assign(4*n,0);
        build(1,n,1);
    }
    void build(int l,int r,int id){
        if(l==r){
            tree[id]={0,-l};
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
    void getnew(int id,int val){
        tree[id].first+=val;
        lazy[id]+=val;
    }
    void pushdown(int id){
        if(lazy[id]){
            getnew(id<<1,lazy[id]);
            getnew(id<<1|1,lazy[id]);
            lazy[id]=0;
        }
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);
    }
    int query(int l,int r,int id,int x){
        if(l==r) return x;
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) return query(l,mid,id<<1,x);
        else{
            int val=query(mid+1,r,id<<1|1,x);
            if(val<0) return val;
            if(tree[id<<1].first>0) return l;
            else return tree[id<<1].second-1; 
        }
    }
};

void solve(){
    int n,q;cin >> n >> q;
    vector<array<int,3>> A(n+q);
    for(int i=0;i<n;i++) cin >> A[i][0] >> A[i][1],A[i][2]=i;
    for(int i=0;i<q;i++) cin >> A[n+i][2] >> A[n+i][0] >> A[n+i][1],A[n+i][2]--;

    vector<pii> comB(n+q);
    for(int i=0;i<n+q;i++) comB[i]={A[i][1],i};
    Compress<pii> cB(comB);
    SegtreeB TB(cB.sz);

    vector<int> comC;
    for(int i=0;i<n+q;i++){
        if(A[i][0]>A[i][1]){
            comC.push_back(A[i][0]);
            comC.push_back(A[i][1]);
        }
        else comC.push_back(A[i][1]);
    }
    Compress<int> cC(comC);
    SegtreeC TC(cC.sz);

    set<pii> S;
    auto add = [&](int i){
        S.insert({A[i][0],i});
        TB.update(1,n+q,1,cB.get({A[i][1],i}),A[i][0]);
        if(A[i][0]>A[i][1]){
            int l=A[i][1],r=A[i][0];
            l=cC.get(l);r=cC.get(r);
            TC.update(1,cC.sz,1,l,r-1,1);
        }
    };
    auto del = [&](int i){
        S.erase({A[i][0],i});
        TB.update(1,n+q,1,cB.get({A[i][1],i}),A[i][0]);
        if(A[i][0]>A[i][1]){
            int l=A[i][1],r=A[i][0];
            l=cC.get(l);r=cC.get(r);
            TC.update(1,cC.sz,1,l,r-1,-1);
        }
    };

    auto cal = [&]{
        pii X=*S.rbegin();
        X.second=A[X.second][1];
        pii val=TB.query(1,n+q,1,cB.get({X.first+1,-1}));
        //cout << cB.get({X.first+1,-1}) << ' ' << val.first << ' ' << val.second << '\n';
        if(X.first<X.second) cout << n-val.first << '\n';
        else{
            int pos=abs(TC.query(1,cC.sz,1,cC.get(X.second)));
            pos=cC.com[pos-1];
            if(pos<=val.second) cout << n-val.first << '\n';
            else cout << n-val.first+1 << '\n';
        }
    };

    vector<int> f(n);
    iota(f.begin(),f.end(),0);
    for(int i=0;i<n;i++) add(i);

    cal();
    for(int i=0;i<q;i++){
        int v=A[n+i][2];
        del(f[v]);
        add(n+i);
        f[v]=n+i;
        cal();
    }

}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
