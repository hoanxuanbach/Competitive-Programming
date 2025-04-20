#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
#define pii pair<int,int>
#define fi first
#define se second

int N,M,B,P,C[maxn];
struct Rec{
    int x,y,u,v;
}R[maxn];

namespace B1{
    int tree[4*maxn],lazy[4*maxn];
    vector<int> pos[maxn];

    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id]+=val;
            lazy[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=min(tree[id<<1],tree[id<<1|1])+lazy[id];
    }
    void solve(){
        auto check = [&](int d){
            for(int i=1;i<=N-d+1;i++) pos[i].clear();
            for(int i=1;i<=4*(M-d+1);i++) tree[i]=lazy[i]=0;
            for(int i=1;i<=P;i++){
                int x=max(1,R[i].x-d+1),u=R[i].u;
                pos[x].push_back(i);pos[u+1].push_back(i);
            }
            for(int i=1;i<=N-d+1;i++){
                for(int id:pos[i]){
                    int l=max(1,R[id].y-d+1),r=R[id].v,c=C[id];
                    if(i==R[id].u+1) c=-c;
                    update(1,M-d+1,1,l,r,c);
                }
                //cout << i << ' ' << tree[1] << '\n';
                if(tree[1]<=B) return true;
            }
            return false;
        };
        int l=1,r=min(N,M),res=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)) res=mid,l=mid+1;
            else r=mid-1;
        }
        cout << res << '\n';
    }
}

namespace B0{
    vector<int> add[maxn],del[maxn];
    struct node{
        int val=0,sz=0,lt=0,rt=0,len=0;
        node(int s=0){
            sz=lt=rt=len=s;
        }
        friend node operator+(node a,node b){
            node res;
            res.len=a.len+b.len;
            res.val=min(a.val,b.val);
            if(a.val<b.val){
                res.sz=a.sz;
                res.lt=a.lt;
                res.rt=0;
            }
            else if(a.val>b.val){
                res.sz=b.sz;
                res.rt=b.rt;
                res.lt=0;
            }
            else{
                res.sz=max({a.sz,b.sz,a.rt+b.lt});
                res.lt=a.lt+(a.lt==a.len)*b.lt;
                res.rt=b.rt+(b.rt==b.len)*a.rt;
            }
            return res;
        }
    }tree[4*maxn];
    void build(int l,int r,int id){
        tree[id]=node(r-l+1);
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    }
    int lazy[4*maxn];
    void update(int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            tree[id].val+=val;
            lazy[id]+=val;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
        tree[id].val+=lazy[id];
    }
    void solve(){
        for(int i=1;i<=P;i++){
            add[R[i].x].push_back(i);
            del[R[i].u].push_back(i);
        }
        int res=0;
        build(1,M,1);
        for(int i=1,j=0;i<=N;i++){
            while(j<=N){
                if((!tree[1].val)*tree[1].sz<j-i+1) break;
                j++;
                for(int id:add[j]) update(1,M,1,R[id].y,R[id].v,1);
            }
            res=max(res,j-i);
            for(int id:del[i]) update(1,M,1,R[id].y,R[id].v,-1);
        }
        cout << res << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> M >> B >> P;
    for(int i=1;i<=P;i++) cin >> R[i].x >> R[i].y >> R[i].u >> R[i].v >> C[i];
    if(B) B1::solve();
    else B0::solve();
}
