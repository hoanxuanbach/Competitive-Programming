#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;
#define fi first
#define se second

int res[maxn],rt;
int cnt,val[maxn],f[maxn],lst[maxn];
vector<int> edge[maxn];

int T,tree[4*maxn][2],child[maxn],son[maxn];
int par[maxn],head[maxn],L[maxn],R[maxn],cn[maxn];
void pre_dfs(int u){
    child[u]=1;son[u]=-1;
    for(int v:edge[u]){
        pre_dfs(v),child[u]+=child[v];
        if(son[u]==-1 || child[v]>child[son[u]]) son[u]=v;
    }
    if(val[u]>=0){
        if(!edge[u].empty()) f[u]=f[edge[u][0]];
    }
    else{
        char op=char(val[u]+256);
        int x=edge[u][0];
        if(op=='!') f[u]=f[x]^1;
        else{
            int y=edge[u][1];
            if(op=='&') f[u]=f[x]&f[y];
            else if(op=='|') f[u]=f[x]|f[y];
            else if(op=='^') f[u]=f[x]^f[y];
        }
    }
    //cout << "pre_dfs " << u << ' ' << f[u] << '\n';
}
void dfs(int u,int p,int t){
    if(t) head[u]=head[p];
    else head[u]=u;
    lst[head[u]]=u;
    par[u]=p;L[u]=++T;cn[T]=u;
    if(son[u]!=-1) dfs(son[u],u,1);
    for(int v:edge[u]) if(v!=son[u]) dfs(v,u,0);
    R[u]=T;
}

void build(int l,int r,int id){
    if(l==r){
        int u=cn[l];
        if(val[u]>=0) tree[id][0]=0,tree[id][1]=1;
        else{
            char op=char(val[u]+256);
            if(op=='!') tree[id][0]=1,tree[id][1]=0;
            else{
                int x=edge[u][0],y=edge[u][1];
                int k=(head[x]==head[u]?f[y]:f[x]);
                //cout << u << ' ' << x << ' ' << y << ' ' << head[u] << ' ' << head[x] << ' ' << head[y] << '\n';
                if(op=='&') tree[id][0]=0,tree[id][1]=k&1;
                else if(op=='|') tree[id][0]=k,tree[id][1]=1;
                else if(op=='^') tree[id][0]=k,tree[id][1]=k^1;
            }
        }
        return;
    }
    int mid=(l+r)>>1;
    build(l,mid,id<<1);build(mid+1,r,id<<1|1);
    for(int i=0;i<=1;i++) tree[id][i]=tree[id<<1][tree[id<<1|1][i]];
}

int query(int l,int r,int id,int tl,int tr,int k){
    if(tr<l || r<tl) return k;
    if(tl<=l && r<=tr) return tree[id][k];
    int mid=(l+r)>>1;
    return query(l,mid,id<<1,tl,tr,query(mid+1,r,id<<1|1,tl,tr,k));
}
void update(int l,int r,int id,int p,int k){
    if(l==r){
        int u=cn[l];
        char op=char(val[u]+256);
        if(op=='&') tree[id][0]=0,tree[id][1]=k&1;
        else if(op=='|') tree[id][0]=k,tree[id][1]=1;
        else if(op=='^') tree[id][0]=k,tree[id][1]=k^1;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p,k);
    else update(mid+1,r,id<<1|1,p,k);
    for(int i=0;i<=1;i++) tree[id][i]=tree[id<<1][tree[id<<1|1][i]];
}

int ans=0,fst=0;
void hld_update(int u){
    int p=head[u],v=lst[p];
    int x=query(1,T,1,L[p],L[v],f[v]);
    if(x==f[p] && fst) return;
    f[p]=x;fst=1;
    if(par[p]!=-1){
        update(1,T,1,L[par[p]],x);
        hld_update(par[p]);
    }
    else ans=x;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,q;cin >> n >> q;
    string s;cin >> s;
    vector<pair<int,char>> cc;
    auto add_edge = [&](int u,int v){
        par[v]=u;
        edge[u].push_back(v);
        //cout << u << ' ' << v << '\n';
    };
    function<void(int,vector<pair<int,char>>,char)> add = [&](int u,vector<pair<int,char>> ss,char op){
        if((int)ss.size()==1) return;
        vector<pair<int,char>> c;
        int cur=u;
        char nop=(op=='|'?'^':'&');
        for(int i=(int)ss.size()-1;i>=0;i--){
            if(ss[i].se==op){
                val[cur]=op-256;
                //cout << cur << ' ' << op << '\n';
                reverse(c.begin(),c.end());c.back().se='*';
                int nxt=((int)c.size()==1?c[0].fi:++cnt);
                add_edge(cur,nxt);
                add(nxt,c,nop);
                nxt=(i?++cnt:ss[0].fi);
                add_edge(cur,nxt);
                cur=nxt;c.clear();
            }
            c.push_back(ss[i]);
        }
        reverse(c.begin(),c.end());
        c.back().se='*';
        add(cur,c,nop);
        return;
    };
    int num=0;
    vector<pair<int,int>> p;
    for(char c:s){
        if(c=='(') cc.push_back({-1,'('});
        else if(c==')'){
            vector<pair<int,char>> ss;
            while(!cc.empty() && cc.back().se!='(') ss.push_back(cc.back()),cc.pop_back();
            reverse(ss.begin(),ss.end());cc.pop_back();
            int cur=((int)ss.size()>1?++cnt:ss[0].fi);
            add(cur,ss,'|');
            while(!cc.empty() && cc.back().se=='!'){
                add_edge(cc.back().fi,cur);
                cur=cc.back().fi,cc.pop_back();
            }
            cc.push_back({cur,'*'});
        }
        else if(c=='[') cnt++,num=0;
        else if(c==']'){
            val[cnt]=num;
            int cur=cnt;
            while(!cc.empty() && cc.back().se=='!'){
                add_edge(cc.back().fi,cur);
                cur=cc.back().fi;cc.pop_back();
            }
            cc.push_back({cur,'*'});
            p.push_back({num,cnt});
        }
        else if(c>='0' && c<='9') num=num*10+(c-'0');
        else if(c=='!'){
            cc.push_back({++cnt,'!'});
            val[cnt]='!'-256;
        }
        else cc.back().se=c;
    }
    if((int)cc.size()>1) add(0,cc,'|');
    else rt=cc[0].fi;
    pre_dfs(rt);dfs(rt,-1,0);
    build(1,T,1);ans=f[rt];
    sort(p.begin(),p.end());
    vector<pair<int,int>> Q(q);
    for(int i=0;i<q;i++) cin >> Q[i].fi,Q[i].se=i;
    sort(Q.begin(),Q.end());

    int pos=0;
    for(int i=0;i<q;i++){
        int x=Q[i].fi,id=Q[i].se;
        while(pos<(int)p.size() && p[pos].fi<=x){
            int u=p[pos++].se;
            f[u]=1;fst=0;hld_update(u);
        }
        res[id]=ans;
    }
    for(int i=0;i<q;i++) cout << (res[i]?"True":"False") << '\n';
}
