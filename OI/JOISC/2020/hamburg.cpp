#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
const int inf = 1e9;
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second

struct rec{
    int l,r,u,d;
    rec(int l=0,int r=0,int u=0,int d=0):l(l),r(r),u(u),d(d){}
};

int N,K;
vector<rec> A;
int rev(int x){
    return (x>2*N?x-2*N:x+2*N);
}

int T,f[maxn],lt[4],rt[4];
vector<int> edge[8*maxn];
vector<piii> cc[4];

void add_edge(int u,int v){
    edge[u].push_back(v);
}

int num[8*maxn],low[8*maxn],scc[8*maxn],cnt;
bool inst[8*maxn];
vector<int> st;

void dfs(int u){
    num[u]=low[u]=++T;
    inst[u]=true;st.push_back(u);
    for(int v:edge[u]){
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
            scc[v]=cnt;
            st.pop_back();
            inst[v]=false;
        }while(v!=u);
    }
}

void solve(){
    int L=0,R=inf,U=inf,D=0;
    for(auto [l,r,u,d]:A) L=max(L,l),R=min(R,r),U=min(U,u),D=max(D,d);
    for(int i=0;i<4;i++) lt[i]=0,rt[i]=inf;

    auto add = [&](int l,int r,int u,int d){
        int k=0,op=-1,oq=-1;
        pii p,q;
        if(l<=L && L<=r) q={d,u},oq=0,swap(p,q),swap(op,oq),k++;
        if(l<=R && R<=r) q={d,u},oq=1,swap(p,q),swap(op,oq),k++;
        if(d<=D && D<=u) q={l,r},oq=2,swap(p,q),swap(op,oq),k++;
        if(d<=U && U<=u) q={l,r},oq=3,swap(p,q),swap(op,oq),k++;
        if(k>=3) return;
        if(k==1){
            lt[op]=max(lt[op],p.fi);
            rt[op]=min(rt[op],p.se);
        }
        else{
            cc[op].push_back({p,++T});
            cc[oq].push_back({q,++T});
            add_edge(rev(T-1),T);
            add_edge(rev(T),T-1);
        }
    };
    for(auto [l,r,u,d]:A) add(l,r,u,d);

    int S=T;T+=2*N;
    for(int t=0;t<4;t++){
        sort(cc[t].begin(),cc[t].end(),[&](piii a,piii b){
            return a.fi.se<b.fi.se;
        });
        int sz=(int)cc[t].size();
        for(int i=0;i<sz;i++){
            auto [p,id]=cc[t][i];
            if(p.se<lt[t] || rt[t]<p.fi) add_edge(id,rev(id));
            f[i]=++T;add_edge(f[i],rev(id));
            if(i) add_edge(f[i],f[i-1]);
            int l=-1,r=i-1;
            while(l<r){
                int m=(l+r+1)>>1;
                if(cc[t][m].fi.se<p.fi) l=m;
                else r=m-1;
            }
            if(l>=0) add_edge(id,f[l]);
        }
        sort(cc[t].begin(),cc[t].end(),[&](piii a,piii b){
            return a.fi.fi<b.fi.fi;
        });
        for(int i=sz-1;i>=0;i--){
            auto [p,id]=cc[t][i];
            f[i]=++T;add_edge(f[i],rev(id));
            if(i<sz-1) add_edge(f[i],f[i+1]);
            int l=i+1,r=sz;
            while(l<r){
                int m=(l+r)>>1;
                if(cc[t][m].fi.fi>p.se) r=m;
                else l=m+1;
            }
            if(l<sz) add_edge(id,f[l]);
        }
    }
    int M=T;T=0;
    for(int i=1;i<=M;i++) if(!num[i]) dfs(i);

    vector<bool> use(S+1);
    for(int i=1;i<=S;i++) use[i]=(scc[i]<scc[rev(i)]);
    for(int t=0;t<4;t++){
        for(auto [p,id]:cc[t]){
            if(use[id]) lt[t]=max(lt[t],p.fi),rt[t]=min(rt[t],p.se);
        }
    }
    cout << L << ' ' << lt[0] << '\n';
    cout << R << ' ' << lt[1] << '\n';
    cout << lt[2] << ' ' << D << '\n';
    cout << lt[3] << ' ' << U << '\n';
}

bool check=false;
vector<pii> cur;

vector<rec> get(int x,int y,vector<rec> a){
    cur.push_back({x,y});
    vector<rec> res;
    for(auto [l,r,u,d]:a) if(x<l || r<x || y<d || u<y) res.push_back(rec(l,r,u,d));
    return res;
}

void dfs(int k,vector<rec> a){
    if(check) return;
    if(!k){
        if(!a.empty() || check) return;
        check=true;
        for(auto [x,y]:cur) cout << x << ' ' << y << '\n';
        return;
    }
    int L=0,R=inf,U=inf,D=0;
    for(auto [l,r,u,d]:a) L=max(L,l),R=min(R,r),U=min(U,u),D=max(D,d);
    dfs(k-1,get(L,U,a));cur.pop_back();
    dfs(k-1,get(L,D,a));cur.pop_back();
    dfs(k-1,get(R,U,a));cur.pop_back();
    dfs(k-1,get(R,D,a));cur.pop_back();
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> K;
    for(int i=0;i<N;i++){
        int l,r,u,d;cin >> l >> d >> r >> u;
        A.push_back(rec(l,r,u,d));
    }
    dfs(K,A);
    if(check) return 0;
    solve();
}
