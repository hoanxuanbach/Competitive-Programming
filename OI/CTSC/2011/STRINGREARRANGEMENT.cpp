#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn=240005;
struct node{
    int nxt[26];
    node(){memset(nxt,0,sizeof(nxt));}
};
struct st{
    int l=0,r=0,sz=0;
    st(int l=0,int r=0,int sz=0):l(l),r(r),sz(sz){}
    friend st operator+(st &a,st &b){
        return {a.l,b.r,a.sz+b.sz};
    }
};
node T[maxn];
int sz,dep[maxn],par[maxn];
vector<int> edge[maxn];
int n,q;
pii que[maxn];
int nxt[maxn],pre[maxn],lst[maxn],fst[maxn],pos[maxn],id[maxn];
st ls[maxn],fs[maxn];
vector<int> ans,res;
long long total=0;
void dfs(int u){
    for(int v:edge[u]){
        dep[v]=dep[u]+1;par[v]=u;
        dfs(v);
    }
}
bool check_lst(int u){
    if((lst[par[u]]!=0 && nxt[u]!=-1) || nxt[u]>=1) return false;
    if(ls[u].l==fst[par[u]] && ls[u].sz!=(int)edge[par[u]].size()) return false;
    return true;
}
bool check_fst(int v){
    if((fst[par[v]]!=0 && pre[v]!=-1) || pre[v]>=1) return false;
    if(fs[v].r==lst[par[v]] && fs[v].sz!=(int)edge[par[v]].size()) return false;
    return true;
}
bool check_join(int u,int v){
    if((nxt[u]!=0 && nxt[u]!=v) || (pre[v]!=0 && pre[v]!=u)) return false;
    if(nxt[u]==v) return true;
    if(ls[u].l==v) return false;
    if(ls[u].l==fst[par[u]] && fs[v].r==lst[par[u]] && ls[u].sz+fs[v].sz!=(int)edge[par[u]].size()) return false;
    return true;
}
int lca(int u,int v){
    while(dep[u]>dep[v]){
        if(!check_lst(u)) return -1;
        u=par[u];
    }
    while(dep[v]>dep[u]){
        if(!check_fst(v)) return -1;
        v=par[v];
    }
    while(par[u]!=par[v]){
        if(!check_lst(u)) return -1;
        u=par[u];
        if(!check_fst(v)) return -1;
        v=par[v];
    }
    if(!check_join(u,v)) return -1;
    return par[u];
}
void add(string s,int p){
    int u=0;
    for(char c:s){
        if(T[u].nxt[c-'a']==0){
            T[u].nxt[c-'a']=++sz;
            ls[sz]=fs[sz]={sz,sz,1};
            edge[u].push_back(sz);
        }
        u=T[u].nxt[c-'a'];
    }
    edge[u].push_back(++sz);
    pos[p]=sz;id[sz]=p;
    ls[sz]=fs[sz]={sz,sz,1};
}
void update(int u,int v,int p){
    if(u==v) return;
    u=pos[u];v=pos[v];
    int a=lca(u,v);
    if(a==-1) return;
    ans.push_back(p);
    //cout << id[u] << ' ' << id[v] << '\n';
    while(par[u]!=a){lst[par[u]]=u;nxt[u]=-1;u=par[u];}
    while(par[v]!=a){fst[par[v]]=v;pre[v]=-1;v=par[v];}
    if(!nxt[u]){
        fs[ls[u].l]=ls[fs[v].r]=ls[u]+fs[v];
        nxt[u]=v;pre[v]=u;
    }
}
void dfs2(int u,int d){
    if((int)edge[u].size()==0){
        res.push_back(id[u]);
        total+=1LL*d*d;
        return;
    }
    int c=fst[u],p=lst[u],ok=0;
    while(pre[p]>=1) p=pre[p];
    int cur=c;
    while(cur>=1){
        dfs2(cur,(ok?dep[u]:d));
        ok=1;cur=nxt[cur];
    }
    for(int v:edge[u]){
        if(v!=c && v!=p && pre[v]<1){
            cur=v;
            while(cur>=1){
                dfs2(cur,(ok?dep[u]:d));
                ok=1;cur=nxt[cur];
            }
        }
    }
    if(p!=c){
        cur=p;
        while(cur>=1){
            dfs2(cur,(ok?dep[u]:d));
            ok=1;cur=nxt[cur];
        }
    }
}
void solve(){
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        string s;cin >> s;
        add(s,i);
    }
    dfs(0);
    for(int i=1;i<=q;i++) cin >> que[i].fi >> que[i].se;
    for(int i=q;i>=1;i--) update(que[i].fi,que[i].se,i);
    dfs2(0,0);
    cout << total << '\n';
    reverse(ans.begin(),ans.end());
    cout << (int)ans.size() << ' ';
    for(int x:ans) cout << x << ' ';
    cout << '\n';
    for(int x:res) cout << x << ' ';
    cout << '\n';
}
signed main(){
    //freopen("9.in","r",stdin);
    //freopen("out.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
