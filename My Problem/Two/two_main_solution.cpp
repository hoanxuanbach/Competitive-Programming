#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
#define pii pair<int,int>
#define fi first
#define se second
struct query{
    int l,x1,y1,x2,y2,id;
};
int n,q,x[2][maxn];
pii pos[2*maxn];
bool ans[maxn];
vector<query> que[2*maxn];
struct node{
    int Max[2][2];
    node(int st=0){memset(Max,0,sizeof(Max));Max[0][0]=st;}
    friend node operator+(node a,node b){
        node res;
        for(int i=0;i<=1;i++){
            for(int j=0;j<=1;j++){
                for(int k=0;k<=1;k++) res.Max[i][j]=max(res.Max[i][j],min(a.Max[i][k],b.Max[k][j]));
            }
        }
        return res;
    }
};
namespace Segtree{
    node tree[4*maxn];
    node query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return node(-1);
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        node cr=query(mid+1,r,id<<1|1,tl,tr),cl=query(l,mid,id<<1,tl,tr);
        if(cl.Max[0][0]==-1) return cr;
        else if(cr.Max[0][0]==-1) return cl;
        else return cl+cr;
    }
    void update(int l,int r,int id,int val,int x1,int y1){
        if(l==r){
            tree[id].Max[x1][x1]=val;
            for(int i=0;i<=1;i++) tree[id].Max[i][i^1]=min(tree[id].Max[i][i],tree[id].Max[i^1][i^1]);
            return;
        }
        int mid=(l+r)>>1;
        if(y1<=mid) update(l,mid,id<<1,val,x1,y1);
        else update(mid+1,r,id<<1|1,val,x1,y1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=0;i<=1;i++){
        for(int j=1;j<=n;j++){
            cin >> x[i][j];
            pos[x[i][j]]={i,j};
        }
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int x1,y1,x2,y2,l,r;cin >> x1 >> y1 >> x2 >> y2 >> l >> r;
        que[r].push_back({l,x1,y1,x2,y2,i});
    }
    for(int i=1;i<=2*n;i++){
        Segtree::update(1,n,1,x[pos[i].fi][pos[i].se],pos[i].fi,pos[i].se);
        for(auto d:que[i]){
            node res=Segtree::query(1,n,1,d.y1,d.y2);
            if(res.Max[d.x1][d.x2]>=d.l) ans[d.id]=1;
        }
    }
    for(int i=1;i<=q;i++) cout << (ans[i]?"YES":"NO") << '\n';
}
