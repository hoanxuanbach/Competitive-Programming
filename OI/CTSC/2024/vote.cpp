#include<bits/stdc++.h>
using namespace std; 
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int> 
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2 = (mod+1)/2;
const int maxn = 2e5+5;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

int fac[maxn],dfac[maxn],inv[maxn];
void combi(int n){
    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}
int C(int n,int k){
    return fac[n]*dfac[k]%mod*dfac[n-k]%mod;
}

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

vector<int> g[maxn];
int n,q,f[maxn],s[maxn],a[maxn],b[maxn];
int L[maxn],head[maxn],sz[maxn],son[maxn],leaf[maxn],T;

int dp[maxn];


struct item {
    int key,prior,b=0,sum=0,mn=0;
    item *l, *r;
    item () { }
    item (int key) : key(key), prior(rand_int(0,inf)), l(NULL), r(NULL) { }
    item (int key, int prior) : key(key), prior(prior), l(NULL), r(NULL) { }
};
typedef item* pitem;

item I[maxn],empty;

struct Treap{

    pitem root;

    int get_mn(pitem t){
        if(!t) return inf;
        else return t->mn;
    }
    int get_sum(pitem t){
        if(!t) return 0;
        else return t->sum;
    }

    void cal(pitem &t){
        t->sum=get_sum(t->l)+get_sum(t->r)+t->b;
        t->mn=min({get_mn(t->l)+t->b+get_sum(t->r),t->key/(n+1)+get_sum(t->r),get_mn(t->r)});
    }

    void split (pitem t, int key, pitem & l, pitem & r) {
        if (!t)
            l = r = NULL;
        else if (t->key <= key)
            split (t->r, key, t->r, r),  l = t;
        else
            split (t->l, key, l, t->l),  r = t;
        
        if(t) cal(t);
    }
    void insert (pitem & t, pitem it) {
        if (!t)
            t = it;
        else if (it->prior > t->prior)
            split (t, it->key, it->l, it->r),  t = it;
        else
            insert (t->key <= it->key ? t->r : t->l, it);

        if(t) cal(t);
    }

    void merge (pitem & t, pitem l, pitem r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            merge (l->r, l->r, r),  t = l;
        else
            merge (r->l, l, r->l),  t = r;
        
        if(t) cal(t);
    }
    void erase (pitem & t,int key) {
        if (t->key == key) {
            pitem th = t;
            merge (t, t->l, t->r);
        }
        else
            erase (key < t->key ? t->l : t->r, key);
        
        if(t) cal(t);
    }

    int query(pitem t,int x){
        if(!t) return x;
        if(t->mn>=x) return x-t->sum;
        if(x>get_mn(t->r)) return query(t->r,x);
        x-=get_sum(t->r);
        if(x>(t->key/(n+1))) return x;
        x-=t->b;
        return query(t->l,x);
    }

    void print(pitem t){
        if(!t) return;
        print(t->l);
        cout << "print " << t->key/(n+1) << ' ' << t->b << ' ' << t->sum << ' ' << t->mn << endl;
        print(t->r);
    }
    void del(int id){
        erase(root,I[id].key);
    }
    void add(int a,int b,int id){
        I[id]=item(a*(n+1)+id);
        I[id].sum=I[id].b=b;
        I[id].mn=a;
        insert(root,&I[id]);
    }
    int query(int x){
        return query(root,x);
    }

}S[maxn];

array<int,2> tree[4*maxn];
void update(int l,int r,int id,int x,array<int,2> val){
    if(l==r){
        tree[id]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x,val);
    else update(mid+1,r,id<<1|1,x,val);
    tree[id][0]=tree[id<<1|1][tree[id<<1][0]];
    tree[id][1]=tree[id<<1|1][tree[id<<1][1]];
}
array<int,2> query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return {0,1};
    if(tl<=l && r<=tr) return tree[id];
    int mid=(l+r)>>1;
    array<int,2> A=query(l,mid,id<<1,tl,tr),B=query(mid+1,r,id<<1|1,tl,tr);
    A[0]=B[A[0]];A[1]=B[A[1]];
    return A;
}

int A[maxn],B[maxn];
int get(int u){
    int v=leaf[u];
    if(u==v) return a[u];
    array<int,2> nxt=query(1,n,1,n+1-L[f[v]],n+1-L[u]);
    return (nxt[0]?B[u]:A[u]);
}

void fix(int u){
    if(!u) return;
    int v=son[u];
    if(v){
        
        A[u]=S[u].query(a[u]);
        B[u]=S[u].query(a[u]-b[v]);
    }
    else A[u]=B[u]=a[u];
    if(v){
        array<int,2> nxt;
        nxt[0]=(A[u]<=A[v]);
        nxt[1]=(A[u]<=B[v]);
        update(1,n,1,n-L[u]+1,nxt);
    }
}


void solve(){   
    cin >> n >> q;
    for(int i=2;i<=n;i++){
        cin >> f[i];
        g[f[i]].push_back(i);
    }
    for(int i=1;i<=n;i++) cin >> s[i],a[i]=s[i];
    for(int i=1;i<=n;i++) cin >> b[i],a[f[i]]+=b[i];
    
    function<void(int)> pre_dfs = [&](int u){
        vector<pii> val;
        sz[u]=1;dp[u]=a[u];
        for(int v:g[u]){
            pre_dfs(v);sz[u]+=sz[v];
            if(sz[v]>sz[son[u]]) son[u]=v;
            val.push_back({dp[v],b[v]});
        }
        sort(val.begin(),val.end());
        while(!val.empty() && val.back().fi>=dp[u]) dp[u]-=val.back().se,val.pop_back();
    };
    pre_dfs(1);
    for(int i=1;i<4*n;i++) tree[i]={0,0};

    function<void(int,int)> hld_dfs = [&](int u,int t){
        L[u]=++T;
        if(t) head[u]=head[f[u]];
        else head[u]=u;
        if(son[u]) hld_dfs(son[u],1),leaf[u]=leaf[son[u]];
        else leaf[u]=u;
        for(int v:g[u]) if(v!=son[u]){
            hld_dfs(v,0);
            S[u].add(dp[v],b[v],v);
        }
        fix(u);
    };
    hld_dfs(1,0);

    for(int i=1;i<=q;i++){
        int op;cin >> op;
        if(op==1){
            int u,x,y;cin >> u >> x >> y;
            int v=f[u];
            a[u]+=x-s[u];s[u]=x;
            a[v]+=y-b[u];b[u]=y;

            int j=-1;
            while(u){
                if(j>1) u=head[u];
                fix(u);j++;
                v=f[u];
                if(v){
                    if(u!=son[v]){
                        S[v].del(u);
                        S[v].add(get(u),b[u],u);
                        j=0;
                    }
                }
                u=v;
            }
        }
        else{
            int u,v;cin >> u >> v;
            int du=get(u),dv=get(v);
            if(du>dv || (du==dv && u>v)) cout << 0 << '\n';
            else cout << 1 << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}