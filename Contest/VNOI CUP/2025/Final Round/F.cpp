#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
#define fi first
#define se second
const int inf = 1e18;
const int mod = 998244353;
const int inv2=(mod+1)/2;
const int maxn = 2e5+5;
const int maxa = 1e6+5;

int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}

mt19937_64 rng(1);
int rand_int(int l,int r){
    return l+rng()%(r-l+1);
}

int fac[maxn],dfac[maxn],inv[maxn];
int C(int n,int k){
    if(n<k || k<0 || n<0) return 0;
    return fac[n]*dfac[n-k]%mod*dfac[k]%mod;
}

void combi(int n){
    fac[0]=inv[0]=1;
    for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
    dfac[n]=power(fac[n],mod-2);
    for(int i=n;i>=1;i--){
        dfac[i-1]=dfac[i]*i%mod;
        inv[i]=dfac[i]*fac[i-1]%mod;
    }
}

struct node{
    int t=0,fst=-1;
    pii nxt[3];
    node(){
        memset(nxt,-1,sizeof(nxt));
    }
    friend node operator+(node a,node b){
        if(a.fst==-1) return b;
        else if(b.fst==-1) return a;
        else{
            node res;
            res.fst=a.fst;
            res.t=a.t^b.t;
            for(int i=0;i<=2;i++){
                pii x=a.nxt[i];
                if(!x.fi) res.nxt[i]=b.nxt[0];
                else{
                    int lst=x.se;
                    if(lst<b.fst) res.nxt[i]=b.nxt[1];
                    else res.nxt[i]=b.nxt[2];
                }
            }
            return res;
        }
    };
};

int p[maxn];
node tree[4*maxn];

void init(int id,int x){
    if(p[x]<x) tree[id]=node();
    else if(p[x]==x){
        tree[id].t=1;
        tree[id].fst=x;
        for(int i=0;i<=2;i++) tree[id].nxt[i]={0,0};
    }
    else{
        tree[id].t=0;
        tree[id].fst=x;
        int y=p[x];
        tree[id].nxt[0]={1,y};
        tree[id].nxt[1]={1,y};
        tree[id].nxt[2]={0,0};
    }
    //cout << "init " << id << ' ' << x << ' ' << tree[id].t << '\n';
}

void build(int l,int r,int id){
    if(l==r){
        init(id,l);
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

node query(int l,int r,int id,int x){
    if(l==r) return tree[id];
    int mid=(l+r)>>1;
    if(x<=mid) return query(l,mid,id<<1,x);
    else return tree[id<<1]+query(mid+1,r,id<<1|1,x);
}

void update(int l,int r,int id,int x){
    if(l==r){
        init(id,l);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x);
    else update(mid+1,r,id<<1|1,x);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

void solve(){   
    int n,m;cin >> n >> m;n*=2;
    iota(p,p+n+1,0);
    for(int i=1;i<=m;i++){
        int x,y;cin >> x >> y;
        if(x>y) swap(x,y);
        p[x]=y;p[y]=x;
    }

    build(1,n,1);
    int q;cin >> q;
    set<int> ss;
    for(int i=1;i<=n;i++) if(p[i]>=i) ss.insert(i);
    for(int i=1;i<=q;i++){
        char c;cin >> c;
        if(c=='+'){
            int x,y;cin >> x >> y;
            if(x>y) swap(x,y);
            p[x]=y;p[y]=x;
            update(1,n,1,x);
            update(1,n,1,y);
            ss.erase(y);
        }
        else if(c=='-'){
            int x,y;cin >> x >> y;
            if(x>y) swap(x,y);
            p[x]=x;p[y]=y;
            update(1,n,1,x);
            update(1,n,1,y);
            ss.insert(y);
        }
        else{
            int x;cin >> x;
            int pos=min(x,p[x]);
            
            auto print = [&](int t){
                cout << t << '\n';
            };

            int t=0;
            pii cur={0,0};
            if(pos>1){
                node res=query(1,n,1,pos-1);
                t=res.t;cur=res.nxt[0];
            }
            
            auto it=ss.upper_bound(pos);

            int y=n+1;
            if(it!=ss.end()) y=*it;

            //cout << pos << ' ' << x << ' ' << y << ' ' << t << ' ' << cur.fi << ' ' << cur.se << '\n';

            if(cur.fi==0){
                if(pos<x){
                    if(x<y) print(t^1);
                    else print(t);
                }
                else if(pos>=x) print(t);
            }
            else{
                if(pos<x){
                    if(cur.se<pos){
                        if(x<y) print(t^1);
                        else print(t);
                    }
                    else print(t^1);
                }
                else if(pos>=x){
                    if(cur.se<x) print(t);
                    else print(t^1);
                }   
            }
            
        }
    }

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}