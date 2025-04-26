#include<bits/stdc++.h>
using namespace std;

using i32=int;
#define int long long
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int inf=1e18;
const int maxn = 250005;
const int Max = 250001;

int dx[]={1,1,0,-1,-1,-1,0,1},
    dy[]={0,1,1,1,0,-1,-1,-1};

int n,m,q;
int res[maxn];
int X[maxn],Y[maxn];

bool mv[maxn];
struct Rec{
    int x1=-1,y1=-1,x2=-1,y2=-1;
    Rec(int x1=-1,int y1=-1,int x2=-1,int y2=-1):x1(x1),y1(y1),x2(x2),y2(y2){}
}rec[maxn];

struct Query{
    int x1,y1,x2,y2,val;
};

namespace Left_to_Right{
    int tree[4*maxn],lazy[4*maxn];
    void getnew(int l,int r,int id,int val){
        lazy[id]+=val;
        tree[id]+=(r-l+1)*val;
    }
    void pushdown(int l,int r,int id){
        if(!lazy[id]) return;
        int mid=(l+r)>>1;
        getnew(l,mid,id<<1,lazy[id]);
        getnew(mid+1,r,id<<1|1,lazy[id]);
        lazy[id]=0;
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
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    int query(int l,int r,int id,int p){
        if(l==r) return tree[id];
        pushdown(l,r,id);
        int mid=(l+r)>>1;
        if(p<=mid) return query(l,mid,id<<1,p);
        else return tree[id<<1]+query(mid+1,r,id<<1|1,p);
    }

    vector<piii> pos[maxn];
    void solve(vector<Query> Q,vector<piii> qq){
        for(int i=0;i<=Max;i++) pos[i].clear();
        for(int i=0;i<=4*Max;i++) tree[i]=lazy[i]=0;

        for(auto c:Q) pos[c.x1].push_back({c.val,{c.y1,c.y2}});
        for(auto p:qq) pos[p.se.fi].push_back({0,{p.fi,p.se.se}});
        for(int i=0;i<=Max;i++){
            for(auto p:pos[i]){
                if(p.fi) update(0,Max,1,p.se.fi,p.se.se,p.fi);
                else res[p.se.fi]+=query(0,Max,1,p.se.se);
            }
        }
    }
}

namespace Down_to_Up{
    vector<pii> pos[maxn];

    struct bit{
        int bit[2*maxn];
        void update(int x,int val){
            assert(x>0);
            for(int i=x;i<=2*Max;i+=(i&(-i))) bit[i]+=val;
        }
        int query(int x){
            assert(x>=0);
            int total=0;
            for(int i=x;i>=1;i-=(i&(-i))) total+=bit[i];
            return total;
        }
    }f0,f1,f2;

    void cal(vector<Query> Q,vector<piii> qq){
        for(int i=0;i<=2*Max;i++) f0.bit[i]=f1.bit[i]=f2.bit[i]=0;
        for(int i=0;i<=Max;i++) pos[i].clear();
        for(int i=0;i<(int)Q.size();i++){
            auto c=Q[i];
            pos[c.x1].emplace_back(inf,i);
            pos[c.x2+1].emplace_back(-inf,i);
        }
        for(auto p:qq) if(p.se.fi>=0) pos[p.se.fi].emplace_back(p.fi,p.se.se);
        for(int i=0;i<=Max;i++){
            for(auto p:pos[i]){
                if(p.fi==-inf){
                    int d=Q[p.se].x1-Q[p.se].y1,val=Q[p.se].val;
                    f0.update(Max-d,-val);
                    f1.update(Max-d,val*(Q[p.se].x1-1));
                    f2.update(Max-d,val*(Q[p.se].x2-Q[p.se].x1+1));
                }
                else if(p.fi==inf){
                    int d=Q[p.se].x1-Q[p.se].y1,val=Q[p.se].val;
                    f0.update(Max-d,val);
                    f1.update(Max-d,-val*(i-1));
                }
                else{
                    res[p.fi]+=f0.query(Max-(i-p.se))*i+f1.query(Max-(i-p.se))+f2.query(Max-(i-p.se));
                }
            }
        }
    }
    void solve(vector<Query> Q,vector<piii> qq){
        cal(Q,qq);
        for(auto &c:Q){
            swap(c.x1,c.y1);
            swap(c.x2,c.y2);
        }
        for(auto &p:qq){
            p.se.fi--;
            swap(p.se.fi,p.se.se);
        }
        cal(Q,qq);
    }
}
vector<int> count_enclosing_rectangle(vector<pair<i32,i32>> R1,vector<pair<i32,i32>> R2,
                                         vector<i32> V,vector<i32> I,vector<i32> D,vector<pair<i32,i32>> P){
    n=(int)R1.size();
    m=(int)V.size();
    q=(int)P.size();
    for(int i=1;i<=n;i++) rec[i]={R1[i-1].fi,R1[i-1].se,R2[i-1].fi,R2[i-1].se};
    vector<Query> q0,q1,q2,q3;

    auto add = [&](int x1,int y1,int x2,int y2,int val){
        if(x1>x2 || (x1==x2 && y1>y2)){
            swap(x1,x2);
            swap(y1,y2);
        }
        if(x1==x2){
            q0.push_back({x1,y1,x2,y2,val});
            //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << val << '\n';
        }
        else if(y1==y2){
            q1.push_back({y1,x1,y2,x2,val});
            //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << ' ' << val << '\n';
        }
        else if(x1-y1==x2-y2) q2.push_back({x1,y1,x2,y2,val});
        else q3.push_back({Max-x2,y2,Max-x1,y1,-val});
    };

    for(int i=1;i<=m;i++){
        int id=V[i-1],p=I[i-1],d=D[i-1];

        Rec S=rec[p];
        S.x1+=dx[id]*mv[p];
        S.y1+=dy[id]*mv[p];
        S.x2+=dx[id]*mv[p];
        S.y2+=dy[id]*mv[p];
        mv[p]=true;
        rec[p].x1+=dx[id]*d;
        rec[p].y1+=dy[id]*d;
        rec[p].x2+=dx[id]*d;
        rec[p].y2+=dy[id]*d;
        Rec T=rec[p];

        add(S.x1,S.y1,T.x1,T.y1,1);
        add(S.x2+1,S.y1,T.x2+1,T.y1,-1);
        add(S.x1,S.y2+1,T.x1,T.y2+1,-1);
        add(S.x2+1,S.y2+1,T.x2+1,T.y2+1,1);
    }
    for(int i=1;i<=n;i++){
        if(mv[i]) continue;
        Rec S=rec[i],T=S;
        add(S.x1,S.y1,T.x1,T.y1,1);
        add(S.x2+1,S.y1,T.x2+1,T.y1,-1);
        add(S.x1,S.y2+1,T.x1,T.y2+1,-1);
        add(S.x2+1,S.y2+1,T.x2+1,T.y2+1,1);
    }

    vector<piii> qq;
    for(int i=0;i<q;i++){
        X[i]=P[i].fi;
        Y[i]=P[i].se;
        qq.push_back({i,{X[i],Y[i]}});
    }
    Left_to_Right::solve(q0,qq);
    Down_to_Up::solve(q2,qq);
    for(int i=0;i<q;i++){
        qq[i].se.fi=Y[i];
        qq[i].se.se=X[i];
    }
    Left_to_Right::solve(q1,qq);
    for(int i=0;i<q;i++){
        qq[i].se.fi=Max-1-X[i];
        qq[i].se.se=Y[i];
    }
    Down_to_Up::solve(q3,qq);
    vector<int> ans(q);
    for(int i=0;i<q;i++) ans[i]=res[i];
    return ans;
}

#undef int