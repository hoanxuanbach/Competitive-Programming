#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+5;
#define pii pair<int,int>
#define fi first
#define se second

int N,rt,dA,dB;
vector<int> edge[maxn];
int L[maxn],R[maxn],cn[maxn],T,dep[maxn];    
int A[maxn],A2[maxn],B[maxn];
vector<int> f[maxn],g[maxn];

int val0[maxn],val1[maxn],dd[maxn],tree[4*maxn];
void update(int l,int r,int id,int x,int val){
    if(l==r){
        tree[id]=val;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) update(l,mid,id<<1,x,val);
    else update(mid+1,r,id<<1|1,x,val);
    tree[id]=min(tree[id<<1],tree[id<<1|1]);
}
int query(int l,int r,int id,int tl,int tr){
    if(tr<l || r<tl || tl>tr) return N+1;
    if(tl<=l && r<=tr) return tree[id];
    int mid=(l+r)>>1;
    return min(query(l,mid,id<<1,tl,tr),query(mid+1,r,id<<1|1,tl,tr));
}

int mn[maxn],mn2[maxn];
vector<pii> del[maxn];


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> rt >> dA >> dB;
    if(dA<=dB){
        cout << 1 << '\n';
        return 0;
    }
    for(int i=1;i<N;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
        edge[v].push_back(u);
    }
    vector<int> st;
    function<void(int,int)> dfs = [&](int u,int p){
        L[u]=++T;cn[T]=u;
        dep[u]=dep[p]+1;
        st.push_back(u);
        f[dep[u]].push_back(u);
        if((int)st.size()>=dA) g[st.end()[-dA]].push_back(u);
        if(p) edge[u].erase(find(edge[u].begin(),edge[u].end(),p));
        for(int v:edge[u]) dfs(v,u);
        st.pop_back();
        R[u]=T;
    };
    dfs(rt,0);
    memset(val0,-1,sizeof(val0));
    memset(val1,-1,sizeof(val1));
    for(int d=N;d>=1;d--){
        for(int u:f[d]) update(1,N,1,L[u],u);
        if(d+dB+1<=N){
            for(int u:f[d+dB+1]) update(1,N,1,L[u],N+1);
        }
        for(int u:f[d]){
            int mx=0;
            for(int v:edge[u]){
                if(dd[v]+1>dd[u]) mx=dd[u],dd[u]=dd[v]+1;
                else mx=max(mx,dd[v]+1);
            }
            if(dd[u]<dA) val0[u]=query(1,N,1,L[u],R[u]);
            for(int v:edge[u]){
                int nd=(dd[v]+1==dd[u]?mx:dd[u]);
                if(nd<dA) val1[v]=min(query(1,N,1,L[u],L[v]-1),query(1,N,1,R[v]+1,R[u]));
            }
        }
    }
    auto check = [&](int K){
        set<int> ss;
        for(int i=1;i<=N;i++) del[i].clear(),B[i]=1;
        for(int d=N;d>=1;d--){
            for(int u:f[d]) ss.insert(L[u]);
            if(d+dB+1<=N){
                for(int u:f[d+dB+1]) ss.erase(L[u]);
            }
            for(int u:f[d]){
                mn[u]=mn2[u]=N+1;
                for(int v:edge[u]){
                    int val=mn[v]+1;
                    if(val<mn[u]) mn2[u]=mn[u],mn[u]=val;
                    else mn2[u]=min(mn2[u],val);
                }

                int cnt=0,pos=-1;
                for(int v:edge[u]){
                    for(int x:g[v]) if(B[x]){cnt++,pos=v;break;}    
                }
                for(int v:edge[u]){
                    if(val1[v]!=-1) A2[v]=(val1[v]>K);
                    else A2[v]=(cnt>1 || (cnt==1 && pos!=v));
                }
                if(val0[u]!=-1) A[u]=(val0[u]>K);
                else A[u]=(cnt>0);
                if(mn[u]<=dB) B[u]=0;
                for(int v:edge[u]){ 
                    int nd=(mn[v]+1==mn[u]?mn2[u]:mn[u]);
                    if(nd+1<=dB && nd<d){
                        del[d-nd].push_back({L[v],R[v]});
                    }
                    if(!A2[v]) del[d].push_back({L[v],R[v]});
                }
                if(!A[u]) B[u]=0,mn[u]=0;
            }

            for(auto [l,r]:del[d]){
                while(true){
                    auto it=ss.lower_bound(l);
                    if(it!=ss.end() && *it<=r){
                        B[cn[*it]]=0;
                        it=ss.erase(it);
                    }
                    else break;
                }
            }
        }
        /*
        for(int i=1;i<=N;i++) cout << A[i];
        cout << '\n';
        for(int i=1;i<=N;i++) cout << A2[i];
        cout << '\n';
        for(int i=1;i<=N;i++) cout << B[i];
        cout << '\n';
        */
        return A[rt];
    };
    int l=1,r=N;
    while(l<r){
        int mid=(l+r)>>1;
        if(check(mid)) l=mid+1;
        else r=mid;
    }   
    cout << l << '\n';
}
