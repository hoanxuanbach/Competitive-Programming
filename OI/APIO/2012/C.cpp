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
const int maxn=200005;
const int B=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=25;
const int maxa=1000000;
const int root=3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot=power(3,mod-2);
const int base=101;

int N,H,W,lst[maxn];
int X[maxn],Y[maxn],D[maxn];
map<int,set<pii>> mp[6];

priority_queue<piii,vector<piii>,greater<piii>> pq;

//3->0,2->1,2->3,1->0,2->0,

void add(int d,int x,int y){
    if(D[x]==D[y] || D[x]==2 || D[y]==0) return;
    if(D[x]==3 && D[y]==1) return;
    pq.push({d,{x,y}});
}

void del2(int t,int x,int y,int i){
    auto it = mp[t][x].lower_bound({y,i});
    it=mp[t][x].erase(it);
    if(it!=mp[t][x].end() && it!=mp[t][x].begin()){
        pii b=*it;it--;
        pii a=*it;
        add(b.fi-a.fi,a.se,b.se);
    }
}

void del(int i){
    if(!(D[i]&1)){
        del2(0,Y[i],X[i],i);
        del2(2+D[i]/2,X[i]-Y[i],X[i]+Y[i],i);
        del2(4+D[i]/2,X[i]+Y[i],X[i]-Y[i],i);
    }
    else{
        del2(1,X[i],Y[i],i);
        del2(3-D[i]/2,X[i]-Y[i],X[i]+Y[i],i);
        del2(4+D[i]/2,X[i]+Y[i],X[i]-Y[i],i);
    }
}

int sz;
vector<int> com;
map<int,vector<pii>> cc;
pii tree[4*maxn];
int lazy[4*maxn];

void build(int l,int r,int id){
    tree[id].se=com[r]-com[l-1];
    if(l==r) return;
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
}

void update(int l,int r,int id,int tl,int tr,int val){
    if(tr<l || r<tl) return;
    if(tl<=l && r<=tr){
        lazy[id]+=val;
        tree[id].fi+=val;
        return;
    }
    int mid=(l+r)>>1;
    update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
    tree[id].fi=min(tree[id<<1].fi,tree[id<<1|1].fi);
    tree[id].se=tree[id<<1].se*(tree[id<<1].fi==tree[id].fi)+tree[id<<1|1].se*(tree[id<<1|1].fi==tree[id].fi);
    tree[id].fi+=lazy[id];
}

void get(int x,int y,int u,int v){
    x=max(min(x,W),1LL);
    y=max(min(y,H),1LL);
    u=max(min(u,W),1LL);
    v=max(min(v,H),1LL);
    if(x>u) swap(x,u);
    if(y>v) swap(y,v);
    //cout << x << ' ' << y << ' ' << u << ' ' << v << '\n';
    cc[x].push_back({y,v});
    cc[u+1].push_back({-y,-v});
    com.push_back(y);
    com.push_back(v+1);
}



void solve(){
    cin >> W >> H >> N;
    for(int i=1;i<=N;i++){
        cin >> X[i] >> Y[i] >> D[i];
        if(D[i]&1) D[i]^=2;
        lst[i]=inf;
        if(!(D[i]&1)){
            mp[0][Y[i]].insert({X[i],i});
            mp[2+D[i]/2][X[i]-Y[i]].insert({X[i]+Y[i],i});
            mp[4+D[i]/2][X[i]+Y[i]].insert({X[i]-Y[i],i});
        }
        else{
            mp[1][X[i]].insert({Y[i],i});
            mp[3-D[i]/2][X[i]-Y[i]].insert({X[i]+Y[i],i});
            mp[4+D[i]/2][X[i]+Y[i]].insert({X[i]-Y[i],i});
        }
    }
    for(int i=0;i<6;i++) for(auto cc:mp[i]){
        pii p={-1,-1};
        for(auto [d,id]:cc.se){
            if(p.se!=-1) add(d-p.fi,p.se,id);
            p={d,id};
        }
    }
    while(!pq.empty()){
        auto [d,p]=pq.top();pq.pop();
        auto [x,y]=p;
        if(lst[x]<d || lst[y]<d) continue;
        if(lst[x]>d){
            lst[x]=d;
            del(x);
        }
        if(lst[y]>d){
            lst[y]=d;
            del(y);
        }
    }
    for(int i=1;i<=N;i++){
        if(D[i]==0) get(X[i],Y[i],X[i]+lst[i]/2,Y[i]);
        if(D[i]==1) get(X[i],Y[i],X[i],Y[i]+lst[i]/2);
        if(D[i]==2) get(X[i],Y[i],X[i]-lst[i]/2,Y[i]);
        if(D[i]==3) get(X[i],Y[i],X[i],Y[i]-lst[i]/2);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    sz=(int)com.size()-1;
    build(1,sz,1);

    int pre=-1,total=0;
    for(auto v:cc){
        if(pre!=-1){
            int cnt=v.fi-pre;
            pii val=tree[1];
            //cout << val.fi << ' ' << val.se << ' ' << pre << ' ' << v.fi << '\n';
            if(!val.fi) total+=cnt*(H-val.se);
            else total+=cnt*H;
        }
        for(auto [l,r]:v.se){
            int val=(l<0?-1:1);
            l=abs(l);r=abs(r);
            l=lower_bound(com.begin(),com.end(),l)-com.begin()+1;
            r=upper_bound(com.begin(),com.end(),r)-com.begin();
            update(1,sz,1,l,r,val);
        }
        pre=v.fi;
    }
    cout << total << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}

