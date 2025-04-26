#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
int dx[]={0,0,1},
    dy[]={1,-1,0};
int n,k,x[2][maxn];
long long total[15];
pii p[2*maxn];
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
    void print(){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++) cout << Max[i][j] << ' ';
            cout << '\n';
        }
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
        //tree[id].print();
    }
}
int cal(int a,int b){
    int x1=p[a].fi,y1=p[a].se+1,x2=p[b].fi,y2=p[b].se+1;
    if(y2<y1){swap(x1,x2);swap(y1,y2);}
    node res=Segtree::query(1,n,1,y1,y2);
    int ans=res.Max[x1][x2];
    res=Segtree::query(1,n,1,y2,n)+Segtree::query(1,n,1,1,y1);
    ans=max(ans,res.Max[x2][x1]);
    return ans;
}
struct node2{
    int num[11],cnt[11];
    node2(){memset(num,-1,sizeof(num));memset(cnt,0,sizeof(cnt));}
    friend node2 operator+(node2 a,node2 b){
        node2 res;
        int la=0,lb=0;
        for(int i=0;i<k;i++){
            if(a.num[la]==-1 && b.num[lb]==-1) break;
            if(a.num[la]!=-1 && (b.num[lb]==-1 || a.num[la]<b.num[lb])){
                res.num[i]=a.num[la];
                res.cnt[i]=a.cnt[la];
                la++;
            }
            else if(b.num[lb]!=-1 && (a.num[la]==-1 || b.num[lb]<a.num[la])){
                res.num[i]=b.num[lb];
                res.cnt[i]=b.cnt[lb];
                lb++;
            }
            else if(a.num[la]==b.num[lb]){
                res.num[i]=a.num[la];
                res.cnt[i]=a.cnt[la]+b.cnt[lb];
                la++;lb++;
            }
        }
        return res;
    }
    void print(){
        for(int i=0;i<k;i++){
            cout << '{' << num[i] << ' ' << cnt[i] << '}';
        }
        cout << '\n';
    }
};
namespace Segtree2{
    node2 tree[8*maxn];
    int lazy[8*maxn];
    void getnew(int id,int val){
        lazy[id]+=val;
        for(int i=0;i<k;i++){
            if(tree[id].num[i]==-1) return;
            tree[id].num[i]+=val;
        }
    }
    void pushdown(int id){
        if(lazy[id]==0) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=0;
    }
    void change(int l,int r,int id,int pos){
        if(l==r){
            tree[id].num[0]=0;
            tree[id].cnt[0]=1;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(pos<=mid) change(l,mid,id<<1,pos);
        else change(mid+1,r,id<<1|1,pos);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void update(int l,int r,int id,int tl,int tr,int val){
        //if(id==1) cout << '*' << tl << ' ' << tr << ' ' << val << '\n';
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void query(){
        for(int i=0;i<k;i++){
            if(tree[1].num[i]==-1 || tree[1].num[i]>k) return;
            total[tree[1].num[i]]+=tree[1].cnt[i];
        }
    }
}
bool adj(int a,int b){
    int x1=p[a].fi,y1=p[a].se,x2=p[b].fi,y2=p[b].se;
    return ((y1==y2) || (x1==x2 && ((y1+1)%n==y2 || (y2+1)%n==y1)));
}
struct DSU{
    int par[5],cc;
    void init(int N){
        cc=0;
        for(int i=1;i<=N;i++) par[i]=i;
    }
    int findpar(int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    }
    void unions(int u,int v){
        u=findpar(u);v=findpar(v);
        if(u==v) return;
        cc--;par[v]=u;
    }
}f1,f2;
void add(vector<int> cur,int d){
    int sz=(int)cur.size();
    f1.init(sz);f2.init(sz+1);f2.cc++;
    vector<piii> tm;
    Segtree2::change(1,2*n,1,d);
    Segtree2::update(1,2*n,1,(!sz?1:cur[0]+1),d,1);
    for(int i=0;i<sz;i++){
        tm.push_back({cur[i],{i+1,-1}});
        for(int j=i+1;j<sz;j++) tm.push_back({cal(cur[i],cur[j]),{i+1,j+1}});
    }
    sort(tm.begin(),tm.end(),greater<piii>());
    for(int i=0;i<(int)tm.size();i++){
        //if(d==5) cout << tm[i].fi << ' ' << tm[i].se.fi << ' ' << tm[i].se.se << '\n';
        if(tm[i].se.se==-1){
            f1.cc++;f2.cc++;
            f2.unions(tm[i].se.fi,sz+1);
        }
        else{
            f1.unions(tm[i].se.fi,tm[i].se.se);
            f2.unions(tm[i].se.fi,tm[i].se.se);
        }
        int nxt=(i==(int)tm.size()-1?1:tm[i+1].fi);
        if(nxt<tm[i].fi && f2.cc!=f1.cc) Segtree2::update(1,2*n,1,nxt+1,tm[i].fi,f2.cc-f1.cc);
    }
}
signed main(){
    //freopen("PLO.INP","r",stdin);
    //freopen("PLO.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    for(int i=0;i<=1;i++){
        for(int j=0;j<n;j++){cin >> x[i][j];p[x[i][j]]={i,j};}
    }
    for(int i=1;i<=2*n;i++){
        pii a=p[i];
        vector<int> cur;
        for(int t=0;t<3;t++){
            int xt=(a.fi+dx[t]+2)%2,yt=(a.se+dy[t]+n)%n;
            if(x[xt][yt]<=i) cur.push_back(x[xt][yt]);
        }
        sort(cur.begin(),cur.end(),greater<int>());
        add(cur,i);
        Segtree2::query();
        Segtree::update(1,n,1,i,a.fi,a.se+1);
        //cout << total[1] << ' ' << total[2] << '\n';
    }
    for(int i=1;i<=k;i++) cout << total[i] << ' ';
    cout << '\n';
}

