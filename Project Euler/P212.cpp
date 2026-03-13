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
    int N;cin >> N;
    vector<int> S(6*N+1);
    for(int i=1;i<=6*N;i++){
        if(i<=55) S[i]=(100003-200003*i+300007*i*i*i)%1000000;
        else S[i]=(S[i-55]+S[i-24])%1000000;
    }

    int T=10400;
    vector<vector<array<int,4>>> f(T);
    for(int i=1;i<=N;i++){
        int x=S[6*i-5]%10000;
        int y=S[6*i-4]%10000;
        int z=S[6*i-3]%10000;
        int dx=1+S[6*i-2]%399;
        int dy=1+S[6*i-1]%399;
        int dz=1+S[6*i]%399;
        for(int j=0;j<dx;j++){
            f[x+j].push_back({y,z,z+dz-1,1});
            f[x+j].push_back({y+dy,z,z+dz-1,-1});
        }
    }

    vector<int> tree(4*T),cnt(4*T),lazy(4*T);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        cnt[id]=r-l+1;
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    };
    build(0,T-1,1);
    function<void(int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int d){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            lazy[id]+=d;
            tree[id]+=d;
            return;
        }
        int mid=(l+r)>>1;
        update(l,mid,id<<1,tl,tr,d);update(mid+1,r,id<<1|1,tl,tr,d);
        tree[id]=min(tree[id<<1],tree[id<<1|1]);cnt[id]=0;
        if(tree[id]==tree[id<<1]) cnt[id]+=cnt[id<<1];
        if(tree[id]==tree[id<<1|1]) cnt[id]+=cnt[id<<1|1];
        tree[id]+=lazy[id];
    };

    int res=0;
    for(int i=0;i<T;i++){
        cout << i << endl;
        if(f[i].empty()) continue;
        sort(f[i].begin(),f[i].end());
        int cur=0;
        for(auto [x,l,r,d]:f[i]){
            if(cur<x){
                int k=T;
                if(tree[1]==0) k-=cnt[1];
                res+=k*(x-cur);
            }
            update(0,T-1,1,l,r,d);
            cur=x;
        }
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
