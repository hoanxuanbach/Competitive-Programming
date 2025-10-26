#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int LG = 18;
const int B = 100;

struct DS{
    int n,sz;
    vector<int> val,lazy;
    vector<vector<int>> ss;

    void build(int id){
        for(int i=id*B;i<min(n,(id+1)*B);i++) val[i]+=lazy[id];
        ss[id]=vector<int>(val.begin()+id*B,val.begin()+min(n,(id+1)*B));
        sort(ss[id].begin(),ss[id].end());
        lazy[id]=0;
    }
    void update(int l,int r,int d){
        int lid=l/B,rid=r/B;
        for(int i=l;i<=r;i++){
            if(i%B==0 && i+B-1<=r){
                lazy[i/B]+=d;
                i+=B-1;
            }
            else val[i]+=d;
        }
        build(lid);
        if(lid!=rid) build(rid);
    }
    int query(int l,int r,int d){
        //cout << "DS query " << n << ' ' << l << ' ' << r << ' ' << d << endl;
        if(l>r) return 0;
        int cnt=0;
        for(int i=l;i<=r;i++){
            if(i%B==0 && i+B-1<=r) cnt+=upper_bound(ss[i/B].begin(),ss[i/B].end(),d-lazy[i/B])-ss[i/B].begin(),i+=B-1;
            else cnt+=((val[i]+lazy[i/B])<=d);
        }
        //cout << "result: " << cnt << endl;
        return cnt;
    }
    int get(int x){
        return val[x]+lazy[x/B];
    }
    DS(){}
    void init(vector<int> base){
        val=base;
        n=(int)val.size();sz=(n-1)/B+1;
        lazy.assign(sz,0);
        for(int i=0;i<sz;i++){
            ss.push_back({});
            build(i);
        }
    }
};

void solve(){
    int n,q;cin >> n >> q;
    vector<vector<pair<int,int>>> g(n+1);
    vector<array<int,3>> E(n);
    for(int i=1;i<n;i++){
        int u,v,w;cin >> u >> v >> w;
        E[i]={u,v,w};
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }

    int S=0;
    vector<int> sz(n+1);
    vector<bool> used(n+1);
    function<void(int,int)> pre_dfs = [&](int u,int p){
        sz[u]=1;
        for(auto [v,w]:g[u]){
            if(v==p || used[v]) continue;
            pre_dfs(v,u);sz[u]+=sz[v];
        }
    };
    function<int(int,int)> get_centroid = [&](int u,int p){
        for(auto [v,w]:g[u]){
            if(v==p || used[v]) continue;
            if(sz[v]>S/2) return get_centroid(v,u);
        }
        return u;
    };

    int T=0;
    vector<int> dad(n+1),f(n+1);
    vector<vector<int>> L(n+1),R(n+1),A(n+1);

    vector<int> dist;
    function<void(int,int,int)> dfs = [&](int u,int p,int a){
        A[u].push_back(a);
        L[u].push_back(T++);
        for(auto [v,w]:g[u]){
            if(v==p || used[v]) continue;
            dist[T]=dist[L[u].back()]+w;
            dfs(v,u,(a?a:v));
        }
        R[u].push_back(T);
    };

    vector<DS> Z(n+1);
    function<int(int,int)> decompose = [&](int u,int d){
        pre_dfs(u,0);S=sz[u];
        int x=get_centroid(u,0);
        used[x]=true;f[x]=d;

        T=0;
        dist.assign(S,0);
        dfs(x,0,0);
        Z[x].init(dist);

        for(auto [v,w]:g[x]) if(!used[v]) dad[decompose(v,d+1)]=x;
        return x;
    };
    int root=decompose(1,0);
    //for(int i=1;i<=n;i++) cout << "dad " << i << ' ' << dad[i] << '\n';

    auto lca = [&](int u,int v){
        if(f[u]>f[v]) swap(u,v);
        while(f[v]>f[u]) v=dad[v];
        while(u!=v) u=dad[u],v=dad[v];
        return u;
    };
    auto update = [&](int x,int u,int v,int w){
        //cout << "update " << x << ' ' << u << ' ' << v << ' ' << w << endl;
        int k=f[x];
        if(L[u][k]>L[v][k]) swap(u,v);
        Z[x].update(L[v][k],R[v][k]-1,w);
    };
    auto query = [&](int x,int u,int d){
        //cout << "query " << x << ' ' << u << ' ' << d << endl;
        int k=f[x];
        if(x==u) return Z[x].query(L[x][k],R[x][k]-1,d);
        else{
            int a=A[u][k];d-=Z[x].get(L[u][k]);
            //cout << "top: " << a << endl;
            return Z[x].query(L[x][k],L[a][k]-1,d)+Z[x].query(R[a][k],R[x][k]-1,d);
        }
    };

    for(int i=0;i<q;i++){
        int op,x,d;cin >> op;
        if(op == 1){
            cin >> x >> d;
            auto [u,v,w]=E[x];d-=w;
            E[x][2]+=d;

            int a=lca(u,v);
            while(a){
                update(a,u,v,d);
                a=dad[a];
            }
        }
        else{
            cin >> x >> d;

            int u=x,res=0;
            while(u){
                res+=query(u,x,d);
                u=dad[u];
            }

            cout << res << '\n';
        }
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int test=1;//cin >> test;
    while(test--) solve();
}