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
    int n,m,q;cin >> n >> m >> q;
    
    vector<int> f(m+1),com;
    for(int i=1;i<=m;i++){
        cin >> f[i];
        if(f[i]) com.push_back(f[i]);
    }
    
    vector<int> A(q+1),B(q+1);
    for(int i=1;i<=q;i++){
        cin >> A[i] >> B[i];
        if(B[i]) com.push_back(B[i]);
    }

    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int M=(int)com.size();
    for(int i=1;i<=m;i++){
        if(f[i]) f[i]=upper_bound(com.begin(),com.end(),f[i])-com.begin();
    }
    for(int i=1;i<=q;i++) if(B[i]) B[i]=upper_bound(com.begin(),com.end(),B[i])-com.begin();

    vector<vector<array<int,3>>> op(q+1);
    vector<set<int>> g(M+1);
    for(int i=1;i<=m;i++){
        if(f[i]){
            if(!g[f[i]].empty()) op[0].push_back({1,*g[f[i]].rbegin(),i});
            g[f[i]].insert(i); 
        }
    }
    for(int i=1;i<=q;i++){
        int x=A[i],y=B[i];
        if(f[x]){
            auto it=g[f[x]].erase(g[f[x]].lower_bound(x));
            int l=-1,r=-1;
            if(it!=g[f[x]].end()) r=*it;
            if(it!=g[f[x]].begin()) l=*(--it);
            if(l!=-1) op[i].push_back({-1,l,x});
            if(r!=-1) op[i].push_back({-1,x,r});
            if(l!=-1 && r!=-1) op[i].push_back({1,l,r});
        }
        f[x]=y;
        if(f[x]){
            auto it=g[f[x]].lower_bound(x);
            int l=-1,r=-1;
            if(it!=g[f[x]].end()) r=*it;
            if(it!=g[f[x]].begin()) l=*(--it);
            if(l!=-1) op[i].push_back({1,l,x});
            if(r!=-1) op[i].push_back({1,x,r});
            if(l!=-1 && r!=-1) op[i].push_back({-1,l,r});
            g[f[x]].insert(x);
        }
    }
    com.clear();
    com.push_back(0);
    com.push_back(n);
    for(int i=0;i<=q;i++) for(auto [d,l,r]:op[i]){
        if(r-l>=n) continue;
        int x=(n-(l-1)%n)%n,y=(n-r%n)%n;
        com.push_back(x);
        com.push_back(y+1);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    M=(int)com.size()-2;

    auto cal = [&](int x){
        if(x&1) return (x>>1&1)^(x-1);
        else return ((x>>1)&1);
    };

    vector<int> mn(4*M+4),val(4*M+4),lazy(4*M+4),cnt(4*M+4);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            val[id]=cal(com[l+1])^cal(com[l]);
            cnt[id]=com[l+1]-com[l];
            return;
        }
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        val[id]=val[id<<1]^val[id<<1|1];
        cnt[id]=cnt[id<<1]+cnt[id<<1|1];
    };
    build(0,M,1);
    function<void(int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int d){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            mn[id]+=d;lazy[id]+=d;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,d);update(mid+1,r,id<<1|1,tl,tr,d);
        mn[id]=min(mn[id<<1],mn[id<<1|1]);
        cnt[id]=val[id]=0;
        if(mn[id]==mn[id<<1]) cnt[id]+=cnt[id<<1],val[id]^=val[id<<1];
        if(mn[id]==mn[id<<1|1]) cnt[id]+=cnt[id<<1|1],val[id]^=val[id<<1|1];
        mn[id]+=lazy[id];
    };  

    for(int i=0;i<=q;i++){
        for(auto [d,l,r]:op[i]){
            if(r-l>=n) continue;
            int x=(n-(l-1)%n)%n,y=(n-r%n)%n+1;
            x=lower_bound(com.begin(),com.end(),x)-com.begin();
            y=lower_bound(com.begin(),com.end(),y)-com.begin()-1;
            if(x<=y) update(0,M,1,x,y,d);
            else update(0,M,1,x,M,d),update(0,M,1,0,y,d);
        }
        if(mn[1]==0) cout << cnt[1] << ' ' << val[1] << '\n';
        else cout << 0 << ' ' << 0 << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}