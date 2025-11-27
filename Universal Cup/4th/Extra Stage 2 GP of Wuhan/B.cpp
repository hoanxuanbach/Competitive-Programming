#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>

void solve(){
    int n,m;cin >> n;
    vector<int> f(n,-1),d(n,0);
    vector<vector<int>> adj(n);
    vector<vector<pii>> S(n);  
    for(int i=1;i<n;i++){
        cin >> f[i];f[i]--;
        adj[f[i]].push_back(i);
        d[i]=d[f[i]]+1;
    }

    int tm=0;
    vector<int> L(n),R(n);
    function<void(int)> pre_dfs = [&](int u){
        L[u]=++tm;
        S[d[u]].push_back({L[u],u});
        for(int v:adj[u]) pre_dfs(v);
        R[u]=tm;
    };
    pre_dfs(0);
    vector<int> st(n),cn(n+1);st[0]=0;
    for(int i=1;i<n;i++) st[i]=st[i-1]+(int)S[i-1].size();
    for(int i=0;i<n;i++) for(int j=0;j<(int)S[i].size();j++) cn[st[i]+j+1]=S[i][j].second;


    int T=2*n;    
    vector<vector<int>> g(T);

    for(int i=1;i<n;i++){
        int x=f[i];
        g[2*x].push_back(2*i+1);
        g[2*i].push_back(2*x+1);
    }

    vector<int> A(4*n),B(4*n);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        if(l==r){
            A[id]=2*cn[l];
            B[id]=2*cn[l]+1;
            return;
        }
        A[id]=T++;
        B[id]=T++;
        g.emplace_back();
        g.emplace_back();
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        g[A[id]].push_back(A[id<<1]);
        g[A[id]].push_back(A[id<<1|1]);
        g[B[id<<1]].push_back(B[id]);
        g[B[id<<1|1]].push_back(B[id]);
    };
    build(1,n,1);
    function<void(int,int,int,int,int,int)> add = [&](int l,int r,int id,int tl,int tr,int x){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            g[2*x+1].push_back(A[id]);
            g[B[id]].push_back(2*x);
            return;
        }
        int mid=(l+r)>>1;
        add(l,mid,id<<1,tl,tr,x);add(mid+1,r,id<<1|1,tl,tr,x);
    };

    cin >> m;
    for(int i=0;i<m;i++){
        int x,y;cin >> x >> y;x--;
        int dd=d[x]+y;
        if(dd>=n) continue;
        int l=upper_bound(S[dd].begin(),S[dd].end(),pii{L[x],0})-S[dd].begin()+1;
        int r=upper_bound(S[dd].begin(),S[dd].end(),pii{R[x],n})-S[dd].begin();
        l+=st[dd];r+=st[dd];
        if(l<=r) add(1,n,1,l,r,x);
        //cout << "add " << x << ' ' << y << ' ' << l << ' ' << r << '\n';
    }

    vector<int> scc(T,-1);
    vector<bool> vis(T);
    vector<vector<int>> rev(T);

    for(int i=0;i<T;i++){
        for(int j:g[i]) rev[j].push_back(i);
    }

    int tt=0;
    vector<int> ord;

    function<void(int)> dfs = [&](int u){
        vis[u]=true;
        for(int v:g[u]) if(!vis[v]) dfs(v);
        ord.push_back(u);
    };
    function<void(int)> dfs2 = [&](int u){
        scc[u]=tt;
        for(int v:rev[u]) if(scc[v]==-1) dfs2(v);
    };

    for(int i=0;i<T;i++) if(!vis[i]) dfs(i);
    //cout << "first scc" << endl;
    reverse(ord.begin(),ord.end());
    for(int u:ord) if(scc[u]==-1) dfs2(u),tt++;

    //cout << "finish scc" << endl;
    vector<int> res;
    bool check=true;
    for(int i=0;i<n;i++){
        if(scc[2*i]==scc[2*i+1]) check=false;
        if(scc[2*i+1]>scc[2*i]) res.push_back(i+1);
    }
    cout << (check?"Yes":"No") << '\n';
    if(check){
        cout << (int)res.size() << '\n';
        for(int x:res) cout << x << ' ';
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}