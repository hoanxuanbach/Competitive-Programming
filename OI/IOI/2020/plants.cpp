#include "plants.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
const int maxl = 20;
const int inf = 1e9;
int n,k;
vector<int> R,H;
set<int> ss,cc;
int lt[maxn][maxl],rt[maxn][maxl];

void cal(int x,int y){
    cc.erase(y);
    if((y-x+n)%n>=k){
        cc.insert(y);
    }
}
void add(int x){
    if(ss.empty()){
        ss.insert(x);
        cc.insert(x);
        return;
    }
    auto it=ss.lower_bound(x);
    if(it!=ss.end()) cal(x,*it);
    else cal(x,*ss.begin());
    if(it==ss.begin()) cal(*ss.rbegin(),x);
    else{
        it--;
        cal(*it,x);
    }
    ss.insert(x);
}
void del(int x){
    cc.erase(x);ss.erase(x);
    if(ss.empty()) return;
    auto it=ss.lower_bound(x);
    int y=(it!=ss.end()?*it:*ss.begin());
    cc.insert(y);
}

int tree[4*maxn],lazy[4*maxn];
void build(int l,int r,int id){
    lazy[id]=0;
    if(l==r){
        tree[id]=R[l];
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    tree[id]=min(tree[id<<1],tree[id<<1|1]);
}
void getnew(int id,int val){
    tree[id]-=val;
    lazy[id]+=val;
}
void pushdown(int id){
    if(!lazy[id]) return;
    getnew(id<<1,lazy[id]);
    getnew(id<<1|1,lazy[id]);
    lazy[id]=0;
}
void get(int l,int r,int id){
    if(tree[id]>0) return;
    if(l==r){
        tree[id]=inf;
        add(l);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    get(l,mid,id<<1);get(mid+1,r,id<<1|1);
    tree[id]=min(tree[id<<1],tree[id<<1|1]);
}
void update(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        getnew(id,1);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr);update(mid+1,r,id<<1|1,tl,tr);
    tree[id]=min(tree[id<<1],tree[id<<1|1]);
}
vector<int> solve(vector<int> r){
    R=r;
    vector<int> p(n);
    ss.clear();cc.clear();
    build(0,n-1,1);
    for(int i=n-1;i>=0;i--){
        get(0,n-1,1);
        int x=*cc.begin();
        if((int)cc.size()>1 && x==0) x=*cc.rbegin();
        p[x]=i;del(x);
        if(x>=k-1) update(0,n-1,1,x-k+1,x);
        else{
            update(0,n-1,1,0,x);
            update(0,n-1,1,n-(k-x)+1,n-1);
        }
    }
    return p;
}

void init(int _k, std::vector<int> r) {
    k=_k;
    n=(int)r.size();
    H=solve(r);

    set<pair<int,int>> S;
    for(int i=0;i<k;i++) S.insert({H[i],i});
    for(int i=0;i<n;i++){
        auto it=S.erase(S.lower_bound({H[i],i}));
        if(it!=S.begin()) it=prev(it),rt[i][0]=(it->second-i+n)%n;
        S.insert({H[(i+k)%n],(i+k)%n});
    }
    S.clear();
    for(int i=1;i<=k;i++) S.insert({H[(n-i)%n],(n-i)%n});
    for(int i=0;i<n;i++){
        S.erase({H[(i-k+n)%n],(i-k+n)%n});
        auto it=S.insert({H[i],i}).first;
        if(it!=S.begin()) it=prev(it),lt[i][0]=(i-it->second+n)%n;
    }

    for(int j=1;j<18;j++){
        for(int i=0;i<n;i++){
            rt[i][j]=min(inf,rt[i][j-1]+rt[(i+rt[i][j-1])%n][j-1]);
            lt[i][j]=min(inf,lt[i][j-1]+lt[(i-lt[i][j-1]%n+n)%n][j-1]);
        }
    }
}

bool get_lt(int x,int y){
    int d=(x-y+n)%n;
    for(int i=17;i>=0;i--){
        if(lt[x][i]<=d) d-=lt[x][i],x=(x-lt[x][i]%n+n)%n;
    }
    return (x-y+n)%n<k && H[x]>=H[y];
}

bool get_rt(int x,int y){
    int d=(y-x+n)%n;
    for(int i=17;i>=0;i--){
        if(rt[x][i]<=d) d-=rt[x][i],x=(x+rt[x][i])%n;
    }
    return (y-x+n)%n<k && H[x]>=H[y];
}

int compare_plants(int x, int y) {
    if(get_lt(x,y) || get_rt(x,y)) return 1;
    if(get_lt(y,x) || get_rt(y,x)) return -1;
	return 0;
}
