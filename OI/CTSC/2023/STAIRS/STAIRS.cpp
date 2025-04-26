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
#define int long long
#define ld long double
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second
const long long inf=1e18;
const int mod=998244353;
const int maxn=300005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
const int base=101;

int m,S;
struct Query{
    char op;
    int a=0,b=0;
}qq[maxn];
vector<int> edge[maxn],com;

struct node{
    int lt=0,rt=0,total=0;
    int add=0,val=inf;
    node(int a=0,int sz=0){
        lt=rt=a;
        total=(a>=1)*(sz-1);
    }
    friend node operator+(node a,node b){
        node res;
        res.lt=a.lt;
        res.rt=b.rt;
        res.total=a.total+b.total+a.rt-b.lt+(b.lt>=1);
        return res;
    }
}tree[4*maxn];

bool check(int id,int val){
    if(val>0) return (tree[id].rt>0 || tree[id].lt==0);
    else return (tree[id].rt+val>0 || tree[id].lt+val<=0);
}

void getnew(int l,int r,int id,int val){
    //cout << "getnew " << l << ' ' << r << ' ' << id << ' '
    tree[id]=node(val,com[r]-com[l-1]);
    tree[id].val=val;
}

void getadd(int l,int r,int id,int val){
    if(val<0 && tree[id].lt+val<=0){
        getnew(l,r,id,0);
        return;
    }
    if(val>0 && tree[id].lt==0){
        getnew(l,r,id,val);
        return;
    }
    tree[id].lt+=val;
    tree[id].rt+=val;
    if(tree[id].val!=inf) tree[id].val+=val;
    else tree[id].add+=val;
}

void pushdown(int l,int r,int id){
    int mid=(l+r)>>1;
    if(tree[id].add!=0){
        getadd(l,mid,id<<1,tree[id].add);
        getadd(mid+1,r,id<<1|1,tree[id].add);
        tree[id].add=0;
    }
    if(tree[id].val!=inf){
        getnew(l,mid,id<<1,tree[id].val);
        getnew(mid+1,r,id<<1|1,tree[id].val);
        tree[id].val=inf;
    }
}

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr && check(id,val)){
        if(val>0){
            if(tree[id].rt>0) getadd(l,r,id,val);
            else getnew(l,r,id,val);
        }
        else{
            if(tree[id].rt+val>0) getadd(l,r,id,val);
            else getnew(l,r,id,0);
        }
        return;
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}

pii query(int l,int r,int id,int num){
    if(l==r){
        int sz=com[l]-com[l-1];
        //cout << "query " << num << ' ' << sz << ' ' << tree[id].lt << '\n';
        if(num<sz) return {com[l-1]+num-1,tree[id].lt};
        num-=(sz-1);
        return {com[l]-1,tree[id].lt-num+1};
    }
    pushdown(l,r,id);
    int mid=(l+r)>>1;
    int total=tree[id<<1].total+tree[id<<1].rt-tree[id<<1|1].lt+(tree[id<<1|1].lt>=1);
    if(num>total) return query(mid+1,r,id<<1|1,num-total);
    else return query(l,mid,id<<1,num);
}

void solve(){
    cin >> m;
    com.push_back(1);
    for(int i=1;i<=m;i++){
        cin >> qq[i].op >> qq[i].a;
        if(qq[i].op=='+' || qq[i].op=='-'){
            cin >> qq[i].b;
            if(qq[i].op=='+') com.push_back(qq[i].a+1);
            else com.push_back(qq[i].a);
        }
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    S=(int)com.size()-1;
    if(!S){
        for(int i=1;i<=m;i++){
            if(qq[i].op=='?') cout << -1 << ' ' << -1 << '\n';
        }
        return;
    }
    for(int i=1;i<=m;i++){
        char op=qq[i].op;
        int a=qq[i].a,b=qq[i].b;
        if(op=='+'){
            int pos=upper_bound(com.begin(),com.end(),a)-com.begin();
            update(1,S,1,1,pos,b);
        }
        else if(op=='-'){
            int pos=lower_bound(com.begin(),com.end(),a)-com.begin()+1;
            update(1,S,1,pos,S,-b);
        }
        else if(op=='R'){
            for(int j=i-a;j<i;j++) if(qq[j].op=='+'){
                int pos=upper_bound(com.begin(),com.end(),qq[j].a)-com.begin();
                update(1,S,1,1,pos,-qq[j].b);
            }
        }
        else{
            int l=1,r=(tree[1].total+tree[1].rt)/a;
            if((tree[1].total+tree[1].rt)%a!=0){
                cout << "Wrong: " << i << ' ' << tree[1].total+tree[1].rt << ' ' << a << '\n';
            }
            if(r==0){
                cout << -1 << ' ' << -1 << '\n';
            }
            else{
                while(l<r){
                    int mid=(l+r)>>1;
                    pii p=query(1,S,1,mid*a);
                    pii q=query(1,S,1,mid*a+1);
                    if(p.fi==q.fi) r=mid;
                    else l=mid+1;
                }
                int X=query(1,S,1,(l-1)*a+1).fi;
                int Y=query(1,S,1,l*a).se;
                cout << X << ' ' << Y << '\n';
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
