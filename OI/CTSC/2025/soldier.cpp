#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int n,k;cin >> n >> k;
    vector<int> a(n),b(n),com;com.push_back(0);
    for(int i=0;i<n;i++) cin >> a[i] >> b[i],com.push_back(a[i]),com.push_back(a[i]-1);
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size()-1;
    auto get = [&](int x){
        return lower_bound(com.begin(),com.end(),x)-com.begin();
    };

    vector<int> lazy(4*(sz+1),0);
    vector<pii> tree(4*(sz+1),{-inf,-inf});
    auto getnew = [&](int id,int val){
        lazy[id]+=val;
        tree[id].first+=val;
        tree[id].second+=val;
    };
    auto pushdown = [&](int id){
        if(!lazy[id]) return;
        getnew(id<<1,lazy[id]);
        getnew(id<<1|1,lazy[id]);
        lazy[id]=0;
    };
    function<void(int,int,int,int,pii)> update = [&](int l,int r,int id,int x,pii val){
        if(l==r){
            tree[id]=max(tree[id],val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) update(l,mid,id<<1,x,val);
        else update(mid+1,r,id<<1|1,x,val);
        tree[id].first=max(tree[id<<1].first,tree[id<<1|1].first);
        tree[id].second=max(tree[id<<1].second,tree[id<<1|1].second);
    };
    function<void(int,int,int,int,int,int)> add = [&](int l,int r,int id,int tl,int tr,int val){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            getnew(id,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        add(l,mid,id<<1,tl,tr,val);add(mid+1,r,id<<1|1,tl,tr,val);
        tree[id].first=max(tree[id<<1].first,tree[id<<1|1].first);
        tree[id].second=max(tree[id<<1].second,tree[id<<1|1].second);
    };
    function<pii(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return pii{-inf,-inf};
        if(tl<=l && r<=tr) return tree[id];
        pushdown(id);
        int mid=(l+r)>>1;
        pii X=query(l,mid,id<<1,tl,tr),Y=query(mid+1,r,id<<1|1,tl,tr);
        return pii{max(X.first,Y.first),max(X.second,Y.second)};
    };

    update(0,sz,1,get(0),{0,0});
    for(int i=0;i<n;i++){
        int pos=get(a[i]-1);
        pii X=query(0,sz,1,0,pos),Y=query(0,sz,1,pos+1,sz);
        update(0,sz,1,pos,pii{Y.first,Y.first+(a[i]-1)*k});
        update(0,sz,1,pos+1,pii{X.second-a[i]*k,X.second});
        add(0,sz,1,pos+1,sz,b[i]);
    }
    cout << tree[1].first << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
