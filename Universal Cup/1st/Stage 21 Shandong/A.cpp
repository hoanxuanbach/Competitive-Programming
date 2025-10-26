#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int maxn = 1e5+5;
const int mod = 998244353;

struct SegmentTree{
    int tree[4*maxn],mul[4*maxn];
    void build(int n){
        for(int i=1;i<4*n;i++) tree[i]=0,mul[i]=1;
    }
    void getnew(int id,int val){
        tree[id]=tree[id]*val%mod;
        mul[id]=mul[id]*val%mod;
    }
    void pushdown(int id){
        if(mul[id]==1) return;
        getnew(id<<1,mul[id]);
        getnew(id<<1|1,mul[id]);
        mul[id]=1;
    }
    void update(int l,int r,int id,int x){
        if(l>x) return;
        if(r<=x){
            getnew(id,2);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,x);update(mid+1,r,id<<1|1,x);
        tree[id]=(tree[id<<1]+tree[id<<1|1])%mod;
    }
    void fix(int l,int r,int id,int x,int val){
        if(l==r){
            tree[id]=val;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) fix(l,mid,id<<1,x,val);
        else fix(mid+1,r,id<<1|1,x,val);
        tree[id]=(tree[id<<1]+tree[id<<1|1])%mod;
    }
    int query(int l,int r,int id,int x){
        if(l==r) return tree[id];
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) return query(l,mid,id<<1,x);
        else return (tree[id<<1]+query(mid+1,r,id<<1|1,x))%mod;
    }
}ST[2];

void solve(){
    int n;cin >> n;
    vector<int> l(n),r(n),c(n);
    for(int i=0;i<n;i++) cin >> l[i] >> r[i] >> c[i];

    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return r[x]<r[y];
    });

    ST[0].build(n+1);
    ST[1].build(n+1);
    ST[0].fix(0,n,1,0,1);
    ST[1].fix(0,n,1,0,1);

    int res=1;
    for(int i=1;i<=n;i++){
        int x=ord[i-1];
        int k=0,lt=1,rt=i;
        while(lt<=rt){
            int mid=(lt+rt)>>1;
            if(r[ord[mid-1]]<l[x]) k=mid,lt=mid+1;
            else rt=mid-1;
        }

        //cout << k << endl;

        int dp=ST[c[x]^1].query(0,n,1,k);
        ST[c[x]^1].update(0,n,1,k);
        ST[c[x]].fix(0,n,1,i,dp);

        //cout << x << ' ' << k << ' ' << dp << endl;

        res=(res+dp)%mod;
    }
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}