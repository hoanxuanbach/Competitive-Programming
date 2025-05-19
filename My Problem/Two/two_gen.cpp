#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
const int oo=1e9;
#define pii pair<int,int>
#define fi first
#define se second
struct query{
    int l,x1,y1,x2,y2;
};
int n,q,x[2][maxn];
pii pos[2*maxn];
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
struct node2{
    int Min[2][2];
    node2(int st=0){
        memset(Min,0,sizeof(Min));
        Min[0][0]=st;
    }
    friend node2 operator+(node2 a,node2 b){
        node2 res;
        for(int i=0;i<=1;i++){
            for(int j=0;j<=1;j++){
                res.Min[i][j]=oo;
                for(int k=0;k<=1;k++) res.Min[i][j]=min(res.Min[i][j],max(a.Min[i][k],b.Min[k][j]));
            }
        }
        return res;
    }
};
namespace Segtree2{
    node2 tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){
            tree[id].Min[0][0]=x[0][l];
            tree[id].Min[1][1]=x[1][l];
            tree[id].Min[0][1]=tree[id].Min[1][0]=max(x[0][l],x[1][l]);
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node2 query(int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return node2(-1);
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        node2 cr=query(mid+1,r,id<<1|1,tl,tr),cl=query(l,mid,id<<1,tl,tr);
        if(cl.Min[0][0]==-1) return cr;
        else if(cr.Min[0][0]==-1) return cl;
        else return cl+cr;
    }
 
}
int main(int argc,char* argv[]){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    registerGen(argc,argv,1);
    int sub=atoi(argv[1]);
    if(sub==1) n=q=5000;
    else n=q=2e5;
    cout << n << '\n';
    vector<int> p;
    for(int i=1;i<=2*n;i++) p.push_back(i);
    shuffle(p.begin(),p.end());
    for(int i=0;i<=1;i++){
        for(int j=1;j<=n;j++){
            x[i][j]=p[i*n+j-1];
            pos[x[i][j]]={i,j};
            cout << x[i][j];
            if(j!=n) cout << ' ';
        }
        cout << '\n';
    }
    cout << q << '\n';
    Segtree2::build(1,n,1);
    for(int i=1;i<=q;i++){
        int x1=rnd.next(0,1),y1=rnd.next(1,n),x2=rnd.next(0,1),y2=y1+rnd.next(0,n-y1),l=-1,r=1;
        node2 res=Segtree2::query(1,n,1,y1,y2);
        if(rnd.next(0,5)) r=res.Min[x1][x2];
        r=rnd.next(r,2*n);
        que[r].push_back({l,x1,y1,x2,y2});
    }
    for(int i=1;i<=2*n;i++){
        Segtree::update(1,n,1,x[pos[i].fi][pos[i].se],pos[i].fi,pos[i].se);
        for(auto d:que[i]){
            node res=Segtree::query(1,n,1,d.y1,d.y2);
            int k=rnd.next(0,2),c=res.Max[d.x1][d.x2];
            if((c==i) || (k && c)) d.l=rnd.next(1,c);
            else d.l=rnd.next(c+1,i);
            cout << d.x1 << ' ' << d.y1 << ' ' << d.x2 << ' ' << d.y2 << ' ' << d.l << ' ' << i << '\n';
        }
    }
}
