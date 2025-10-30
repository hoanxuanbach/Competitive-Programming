#include<bits/stdc++.h>
using namespace std;
const int S = 10000005;
vector<int> g[S];

void solve(){
    int n,m;cin >> n >> m;
    
    vector<int> com;
    
    vector<int> L(n),R(n);
    for(int i=0;i<n;i++){
        cin >> L[i] >> R[i];
        com.push_back(L[i]);
        com.push_back(R[i]+1);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    int sz=(int)com.size();

    for(int i=0;i<n;i++){
        L[i]=lower_bound(com.begin(),com.end(),L[i])-com.begin()+1;
        R[i]=lower_bound(com.begin(),com.end(),R[i]+1)-com.begin();
    }

    int T=2*n;    
    for(int i=0;i<T;i++) g[i].clear();
    vector<int> A(4*sz),B(4*sz);
    function<void(int,int,int)> build = [&](int l,int r,int id){
        A[id]=T++;
        B[id]=T++;
        g[A[id]].clear();
        g[B[id]].clear();
        if(l==r) return;
        int mid=(l+r)>>1;
        build(l,mid,id<<1);build(mid+1,r,id<<1|1);
        g[A[id]].push_back(A[id<<1]);
        g[A[id]].push_back(A[id<<1|1]);
    };
    build(1,sz,1);

    //cout << T << '\n';

    vector<vector<int>> f(4*sz);
    function<void(int,int,int,int,int,int)> add = [&](int l,int r,int id,int tl,int tr,int x){
        if(tr<l || r<tl) return;
        if(tl<=l && r<=tr){
            g[A[id]].push_back(2*x);
            if(l<r){
                g[2*x+1].push_back(A[id<<1]);
                g[2*x+1].push_back(A[id<<1|1]);
            }
            g[B[id]].push_back(2*x);
            f[id].push_back(x);
            return;
        }
        g[2*x+1].push_back(B[id]);
        int mid=(l+r)>>1;
        add(l,mid,id<<1,tl,tr,x);
        add(mid+1,r,id<<1|1,tl,tr,x);
    };
    for(int i=0;i<n;i++) add(1,sz,1,L[i],R[i],i);

    for(int i=0;i<4*sz;i++){
        if((int)f[i].size()<=1) continue;
        int sz=(int)f[i].size()-1;
        for(int j=0;j<2*sz;j++) g[T+j].clear();

        for(int j=0;j<sz;j++){
            int x=f[i][j],y=f[i][j+1];
            g[2*x+1].push_back(T+j);
            g[2*y+1].push_back(T+sz+j);
            g[T+j].push_back(2*y);
            g[T+sz+j].push_back(2*x);

            if(j+1<sz){
                g[T+j].push_back(T+j+1);
                g[T+sz+j+1].push_back(T+sz+j);
            }
        }

        T+=2*sz;
    }
    for(int i=0;i<m;i++){
        int x,y;cin >> x >> y;x--;y--;
        g[2*x].push_back(2*y+1);
        g[2*y].push_back(2*x+1);
    }

    int cnt=0;
    vector<int> scc(T,-1);
    
    int TT=0;
    vector<int> low(T),num(T);
    vector<bool> inst(T);
    vector<int> st;

    function<void(int)> dfs = [&](int u){
        low[u]=num[u]=++TT;
        st.push_back(u);
        inst[u]=true;
        for(int v:g[u]){
            if(!num[v]){
                dfs(v);
                low[u]=min(low[u],low[v]);
            }
            else if(inst[v]) low[u]=min(low[u],num[v]);
        }
        if(low[u]==num[u]){
            int v=-1;cnt++;
            do{
                v=st.back();
                st.pop_back();
                inst[v]=false;
                scc[v]=cnt;
            }while(u!=v);
        }
    };

    for(int i=0;i<T;i++) if(!num[i]) dfs(i);

    bool check=true;
    for(int i=0;i<n;i++) if(scc[2*i]==scc[2*i+1]) check=false;
    cout << (check?"YES":"NO") << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
