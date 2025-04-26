#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn = 1e5+5;
const int maxq = 3e5+5;
const int A = 1e6;

int n,q,mod;
int a[maxn],res[maxq];
vector<pair<int,int>> qq[maxn];
int p[A+5],pos[A+5],c[maxn];

int lazy[4*maxn];
struct node{
    int total=0,sum=0,num=0;
    node(int _num=0){sum=num=_num;}
    friend node operator+(node a,node b){
        node res;
        res.total=(a.total+b.total)%mod;
        res.sum=(a.sum*b.num+b.sum)%mod;
        res.num=a.num*b.num%mod;
        return res;
    }
}tree[4*maxn];

void build(int l,int r,int id){
    if(l==r){
        tree[id]=node(c[l]);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
void getnew(int id,int val){
    tree[id].total=(tree[id].total+tree[id].sum*val)%mod;
    lazy[id]=(lazy[id]+val)%mod;
}
void pushdown(int id){
    if(!lazy[id]) return;
    getnew(id<<1,lazy[id]*tree[id<<1|1].num%mod);
    getnew(id<<1|1,lazy[id]);
    lazy[id]=0;
}
void update(int l,int r,int id,int x){
    if(l==r){
        tree[id].sum=tree[id].num=c[l];
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x);
    else update(mid+1,r,id<<1|1,x);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
void update_lazy(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(id,val);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update_lazy(l,mid,id<<1,tl,tr,val*tree[id<<1|1].num%mod);
    update_lazy(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
int query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return 0;
    if(tl<=l && r<=tr) return tree[id].total;
    pushdown(id);
    int mid=(l+r)>>1;
    return (query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr))%mod;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q >> mod;
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        qq[r].push_back({l,i});
    }
    for(int i=2;i<=A;i++){
        if(!p[i]){
            for(int j=i;j<=A;j+=i) p[j]=i;
        }
    }
    for(int i=1;i<=n;i++) c[i]=1;
    build(1,n,1);
    for(int i=1;i<=n;i++){
        int x=a[i];c[i]=x;
        while(x>1){
            int k=p[x],d=1;
            while(x%k==0){
                d*=k;x/=k;
                if(pos[d]){
                    c[pos[d]]/=k;
                    update(1,n,1,pos[d]);
                }
                pos[d]=i;
            }
        }
        update(1,n,1,i);
        update_lazy(1,n,1,1,i,1);
        for(auto [l,id]:qq[i]) res[id]=query(1,n,1,l,i);
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}
