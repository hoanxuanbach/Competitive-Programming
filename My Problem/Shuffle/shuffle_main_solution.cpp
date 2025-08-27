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

const int maxn = 5e5+5;

int n,a[maxn];
int tree[4*maxn],lazy[4*maxn];

void build(int l,int r,int id){
    lazy[id]=-1;
    if(l==r){
        tree[id]=a[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=(tree[id<<1]+tree[id<<1|1])%mod;
}

void getnew(int l,int r,int id,int val){
    tree[id]=(r-l+1)*val%mod;
    lazy[id]=val;
}

void pushdown(int l,int r,int id){
    if(lazy[id]==-1) return;
    int mid=(l+r)>>1;
    getnew(l,mid,id<<1,lazy[id]);
    getnew(mid+1,r,id<<1|1,lazy[id]);
    lazy[id]=-1;
}

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(l,r,id,val);
        return;
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=(tree[id<<1]+tree[id<<1|1])%mod;
}
int query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return 0;
    if(tl<=l && r<=tr) return tree[id];
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    return (query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr))%mod;
}

void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) cin >> a[i];
    build(1,n,1);

    int q;cin >> q;
    while(q--){
        int id,l,r;cin >> id >> l >> r;
        if(id==1){
            int val=query(1,n,1,l,r)*power(r-l+1,mod-2)%mod;
            update(1,n,1,l,r,val);
        }
        else{
            cout << query(1,n,1,l,r) << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}