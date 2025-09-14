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
    int n,q;cin >> n >> q;
    vector<int> a(n+1),lt(n+1),rt(n+1);

    vector<int> v;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        while(!v.empty() && a[v.back()]<a[i]) v.pop_back();
        lt[i]=(v.empty()?0:v.back());
        v.push_back(i);
    }
    v.clear();
    for(int i=n;i>=1;i--){
        while(!v.empty() && a[v.back()]>a[i]) v.pop_back();
        if(!v.empty()) rt[v.back()]=max(rt[v.back()],lt[i]);
        v.push_back(i);
    }

    vector<int> tree(4*n);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            tree[id]=rt[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        tree[id]=max(tree[id<<1],tree[id<<1|1]);
    };
    build(1,n,1);
    function<int(int,int,int,int,int)> query = [&](int l,int r,int id,int tl,int tr){
        if(tr<l || r<tl) return 0LL;
        if(tl<=l && r<=tr) return tree[id];
        int mid=(l+r)>>1;
        return max(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
    };
    for(int i=1;i<=q;i++){
        int l,r;cin >> l >> r;
        cout << (query(1,n,1,l,r)>=l?"NO":"YES") << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
