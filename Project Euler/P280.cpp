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

const int N=5;
int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};


#define ld long double
void solve(){
    int T=0;

    vector<vector<int>> adj;
    vector<array<int,5>> S;
    map<array<int,5>,int> mp;
    
    auto add = [&](int A,int B,int x,int y,int d){
        array<int,5> v={A,B,x,y,d};
        if(mp.find(v)!=mp.end()) return mp[v];
        S.push_back(v);
        adj.emplace_back();
        return mp[v]=T++;
    };
    add(0,31,2,2,0);

    vector<int> F;
    function<void(int)> dfs = [&](int id){
        auto [A,B,x,y,d]=S[id];
        if(A==31 && B==0){
            F.push_back(id);
            return;
        }
        for(int t=0;t<4;t++){
            int xt=x+dx[t],yt=y+dy[t];
            if(xt<0 || yt<0 || xt>=N || yt>=N) continue;
            int At=A,Bt=B,dt=d;
            if(dt && xt==0 && !(At>>yt&1)) dt^=1,At^=(1<<yt);
            if(!dt && xt==4 && (Bt>>yt&1)) dt^=1,Bt^=(1<<yt);
            
            int nid=add(At,Bt,xt,yt,dt);
            adj[id].push_back(nid);
        }
    };

    int pos=0;
    while(pos<T) dfs(pos++);

    vector<ld> f(T);f[0]=1;

    int M;cin >> M;

    ld res=0;
    for(int it=1;it<M;it++){
        vector<ld> nf(T);
        for(int i=0;i<T;i++){
            int s=(int)adj[i].size();
            for(int j:adj[i]) nf[j]+=f[i]/s;
        }
        swap(nf,f);
        for(int x:F){
            res+=f[x]*it;
            f[x]=0;
        }
    }
    cout << setprecision(10) << fixed << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
