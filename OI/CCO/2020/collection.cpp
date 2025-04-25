#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
const int maxa = 1e6;
const int inf = 1e9;
#define pii pair<int,int>
#define fi first 
#define se second

struct node{
    int lt=-inf,rt=inf,val=inf;
    node(int lt=-inf,int rt=inf,int val=inf):lt(lt),rt(rt),val(val){}
    friend node operator+(node a,node b){
        node res;
        res.val=min({a.val,b.val,b.rt-a.lt});
        res.lt=max(a.lt,b.lt);
        res.rt=min(a.rt,b.rt);
        return res;
    }
}tree[4*maxn];
set<pii> lt[maxn],rt[maxn],L,R;
void update(int l,int r,int id,int x){
    if(l==r){
        int cl=(rt[x].empty()?-inf:rt[x].rbegin()->fi);
        int cr=(lt[x].empty()?inf:lt[x].begin()->fi);
        int val=min(inf,cr-cl);
        tree[id]=node(cl,cr,val);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x);
    else update(mid+1,r,id<<1|1,x);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        char c;int l,r;cin >> c >> l >> r;
        if(c=='A'){
            lt[l].insert({r,i});L.insert({l,i});
            rt[r].insert({l,i});R.insert({r,i});
        }
        else{
            lt[l].erase(lt[l].lower_bound({r,0}));
            rt[r].erase(rt[r].lower_bound({l,0}));
            L.erase(L.lower_bound({l,0}));
            R.erase(R.lower_bound({r,0}));
        }
        update(1,maxa,1,l);
        update(1,maxa,1,r);
        if(*L.rbegin()<*R.begin()){
            l=L.rbegin()->fi,r=R.begin()->fi;
            cout << lt[l].begin()->fi-rt[r].rbegin()->fi << '\n';
        }
        else cout << tree[1].val << '\n';
    }
}
/*
5
A 1 5
A 2 7
A 4 6
A 6 8
R 4 6
*/