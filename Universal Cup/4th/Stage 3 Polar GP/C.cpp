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
    int m,n,q;cin >> m >> n >> q;

    map<string,pair<int,int>> mp;
    for(int i=0;i<m;i++){
        int p,v;string d;cin >> p >> v >> d;
        mp[d]={p,v};
    }

    vector<int> p(n+1),v(n+1);
    for(int i=1;i<=n;i++){
        string s;cin >> s;
        tie(p[i],v[i])=mp[s];
    }

    vector<int> res(q);
    vector<vector<pair<int,int>>> qq(n+1);
    for(int i=0;i<q;i++){
        int l,r;cin >> l >> r;
        qq[l].push_back({r,i});
    }

    vector<int> lx(4*n),l0(4*n),l1(4*n);
    auto fxor = [&](int id){
        lx[id]^=1;
        swap(l0[id],l1[id]);
    };
    auto fadd = [&](int id,int t,int val){
        if(t==0) l0[id]+=val;
        else l1[id]+=val;
    };
    auto pushdown = [&](int id){
        if(lx[id]){
            fxor(id<<1);
            fxor(id<<1|1);
            lx[id]=0;
        }  
        if(l0[id]){
            fadd(id<<1,0,l0[id]);
            fadd(id<<1|1,0,l0[id]);
            l0[id]=0;
        }
        if(l1[id]){
            fadd(id<<1,1,l1[id]);
            fadd(id<<1|1,1,l1[id]);
            l1[id]=0;
        }
    };
    function<void(int,int,int,int)> update = [&](int l,int r,int id,int x){
        if(r<x) return;
        if(x<=l){
            fxor(id);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        update(l,mid,id<<1,x);
        update(mid+1,r,id<<1|1,x);
    };
    function<void(int,int,int,int,int,int)> add = [&](int l,int r,int id,int x,int t,int val){
        if(r<x) return;
        if(x<=l){
            fadd(id,t,val);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        add(l,mid,id<<1,x,t,val);
        add(mid+1,r,id<<1|1,x,t,val);
    };
    function<int(int,int,int,int)> get = [&](int l,int r,int id,int x){
        if(l==r){
            if(lx[id]==0) return l0[id];
            else return l1[id];
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) return get(l,mid,id<<1,x);
        else return get(mid+1,r,id<<1|1,x);
    };

    vector<int> pos;
    for(int i=n;i>=1;i--){
        //cout << '*' << i << '\n';
        while(!pos.empty() && p[pos.back()]<=p[i]){
            update(1,n,1,pos.back());
            //cout << "update " << pos.back() << '\n';
            pos.pop_back();
        }
        pos.push_back(i);
        update(1,n,1,i);
        //cout << "update " << i << '\n';
        add(1,n,1,i,1,v[i]);
        add(1,n,1,i,0,-v[i]);
        for(auto [r,id]:qq[i]) res[id]=get(1,n,1,r);
    }

    for(int i=0;i<q;i++) cout << res[i] << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
