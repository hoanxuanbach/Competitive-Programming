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


/*

dp[0] = 0 
dp[i] = dp[j] + delta + cost(j,i) 

dp[N+1] 

cost(l,r) = sum(C_i) l < S_i < T_i < r
*/

void solve(){
    int N,M,K;cin >> N >> M >> K;

    int total=0;
    vector<vector<pii>> g(N+1);
    for(int i=0;i<M;i++){
        int l,r,w;cin >> l >> r >> w;r--;
        g[r].push_back({l,w});total+=w;
    }

    int mx=0,pos=0;
    for(int i=1;i<=N;i++) for(auto [l,d]:g[i]) if(l>pos) pos=i,mx++;
    if(K>=mx){
        cout << 0 << '\n';
        return;
    }

    vector<pii> dp(N+1);
    auto cal = [&](int delta){

        vector<int> lazy(4*N+4);
        vector<pii> tree(4*N+4,{inf,inf});
        function<void(int,int,int,int)> fix = [&](int l,int r,int id,int x){
            if(l==r){
                tree[id]=dp[x];
                return;
            }
            int mid=(l+r)>>1;
            if(x<=mid) fix(l,mid,id<<1,x);
            else fix(mid+1,r,id<<1|1,x);
            tree[id]=min(tree[id<<1],tree[id<<1|1]);
            if(tree[id].first!=inf) tree[id].first+=lazy[id];
        };
        function<void(int,int,int,int,int,int)> update = [&](int l,int r,int id,int tl,int tr,int val){
            if(tr<l || r<tl) return;
            if(tl<=l && r<=tr){
                lazy[id]+=val;
                if(tree[id].first!=inf) tree[id].first+=val;
                return;
            }
            int mid=(l+r)>>1;
            update(l,mid,id<<1,tl,tr,val);update(mid+1,r,id<<1|1,tl,tr,val);
            tree[id]=min(tree[id<<1],tree[id<<1|1]);
            if(tree[id].first!=inf) tree[id].first+=lazy[id];
        };

        dp[0]={0,0};
        fix(0,N,1,0);
        for(int i=1;i<=N;i++){
            dp[i]={tree[1].first+delta,tree[1].second+1};
            fix(0,N,1,i);
            for(auto [l,d]:g[i]) update(0,N,1,0,l-1,d);
        }
        //cout << dp[N+1].first-dp[N+1].second*delta << ' ' << dp[N+1].second-1 << endl;
        return pii{dp[N].first-delta,dp[N].second-1};
    };

    int ld=0,rd=2*total,res=total;
    while(ld<=rd){
        int mid=(ld+rd)>>1;
        auto [cost,k]=cal(mid);
        if(k<=K) res=cost-mid*K,rd=mid-1;
        else ld=mid+1;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
