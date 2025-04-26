#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
struct query{
    int l,r,w;
    bool operator<(query o){
        if(l!=o.l) return l<o.l;
        else return r>o.r;
    }
};

vector<query> p;
vector<int> ans;
int n,m,c[maxn],total;
struct node{
    int x=-1,num=0;
    node(){}
    friend node operator+(node a,node b){
        node res;res.num=a.num+b.num;
        if(a.x==-1) res.x=b.x;
        else if(b.x==-1) res.x=a.x;
        else res.x=(c[a.x]<c[b.x]?a.x:b.x);
        return res;
    }
};
namespace st{
    node tree[4*maxn];
    void build(int l,int r,int id){
        if(l==r){tree[id].x=l;return;}
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    void update(int l,int r,int id,int p){
        if(l==r){
            tree[id].x=-1;tree[id].num=1;
            return;
        }
        int mid=(l+r)>>1;
        if(p<=mid) update(l,mid,id<<1,p);
        else update(mid+1,r,id<<1|1,p);
        tree[id]=tree[id<<1]+tree[id<<1|1];
    }
    node query(int l,int r,int id,int tl,int tr){
        if(l>tr || tl>r) return node();
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return query(l,mid,id<<1,tl,tr)+query(mid+1,r,id<<1|1,tl,tr);
    }
}
void cal(int l,int r,int w){
    while(true){
        node x=st::query(1,n,1,l,r);
        if(x.num>=w) return;
        ans.push_back(x.x);total+=c[x.x];
        st::update(1,n,1,x.x);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> c[i];
    st::build(1,n,1);
    cin >> m;
    for(int i=1;i<=m;i++){
        int l,r,w;cin >> l >> r >> w;
        p.push_back({l,r,w});
    }
    sort(p.begin(),p.end());
    vector<query> v;
    for(auto x:p){
        while(!v.empty() && v.back().r<x.l){
            cal(v.back().l,v.back().r,v.back().w);
            v.pop_back();
        }
        v.push_back(x);
    }
    while(!v.empty()){cal(v.back().l,v.back().r,v.back().w);v.pop_back();}
    cout << total << '\n';
    cout << (int)ans.size() << '\n';
    for(int x:ans) cout << x << ' ';
}
