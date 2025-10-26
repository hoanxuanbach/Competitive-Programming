// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/
#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=100005;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int base=131;

struct node{
    int sum=0;
    node *cl=nullptr,*cr=nullptr;
    node(){}
};

set<pii> s[maxn];
int n,q;
node *root;

void update(int l,int r,node *x,int p,int val){
    if(l==r){
        x->sum+=val;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid){
        if(!x->cl) x->cl=new node();
        update(l,mid,x->cl,p,val);
    }
    else{
        if(!x->cr) x->cr=new node();
        update(mid+1,r,x->cr,p,val);
    }
    x->sum=(x->cl?x->cl->sum:0)+(x->cr?x->cr->sum:0);
}
int query(int l,int r,node *x,int p){
    if(!x) return 0;
    if(l==r) return x->sum;
    int mid=(l+r)>>1;
    if(p<=mid) return query(l,mid,x->cl,p);
    else return (x->cl?x->cl->sum:0)+query(mid+1,r,x->cr,p);
}

void del(int L,int R,int x){
    auto it=s[x].lower_bound({L,0});
    if(it!=s[x].begin()) it--;
    while(it!=s[x].end() && it->fi<=R){
        //cout << "pos " << it->fi << ' ' << it->se << endl;
        int l=max(L,it->fi),r=min(R,it->se);
        if(l>r){
            it++;
            continue;
        }
        update(1,n,root,l,-1);
        if(r<n) update(1,n,root,r+1,1);
        //cout << "update " << x << ' ' << l << ' ' << r << ' ' << -1 << endl;
        pii cur=*it;
        it=s[x].erase(it);
        if(cur.fi<l) s[x].insert({cur.fi,l-1});
        if(r<cur.se) s[x].insert({r+1,cur.se});
    }
}
void solve(){
    root = new node();
    cin >> n >> q;
    for(int i=1;i<=q;i++){
        char c;cin >> c;
        int l,r,x;
        if(c=='?'){
            int x;cin >> x;
            cout << query(1,n,root,x) << endl;
        }
        else{
            cin >> l >> r >> x;
            del(l,r,x);
            if(c=='+'){
                s[x].insert({l,r});
                update(1,n,root,l,1);
                if(r<n) update(1,n,root,r+1,-1);
                //cout << "update " << x << ' ' << l << ' ' << r << ' ' << 1 << endl;
            }
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
