#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
#define int long long
int N,M,L,C,Q;
int A[maxn],B[maxn],T[maxn];
int dd[maxn],deg[maxn],child[maxn],son[maxn];
int nxt[maxn],dist[maxn],sum[maxn];
vector<int> edge[maxn],f[maxn];

int ans[maxn];
vector<int> qq[maxn];

struct BIT{
    int sz;
    vector<int> com,bit;
    void init(){
        for(int i=1;i<=sz;i++) bit[i]=0;
    }
    void reset(){
        com.clear();
    }
    void add(int x){
        com.push_back(x);
    }
    void build(){
        sort(com.begin(),com.end());
        com.erase(unique(com.begin(),com.end()),com.end());
        sz=(int)com.size();
        bit.assign(sz+1,0);
    }
    int get(int x){
        return upper_bound(com.begin(),com.end(),x)-com.begin();
    }
    void update(int x,int val){
        x=get(x);
        for(int i=x;i<=sz;i+=(i&(-i))) bit[i]+=val;
    }
    int query(int x){
        x=get(x);
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
        return res;
    }
};

struct BIT2{
    int sz,ss[maxn];
    vector<int> com[maxn],bit[maxn];
    void init(){
        for(int i=1;i<=sz;i++) for(int j=1;j<=ss[i];j++) bit[i][j]=0;
    }
    void reset(){
        for(int i=1;i<=sz;i++) com[i].clear();
    }
    void add(int x,int y){
        for(int i=x;i<=sz;i+=(i&(-i))) com[i].push_back(y);
    }
    int get(int x,int y){
        return upper_bound(com[x].begin(),com[x].end(),y)-com[x].begin();
    }
    void build(){
        for(int i=1;i<=sz;i++){
            sort(com[i].begin(),com[i].end());
            com[i].erase(unique(com[i].begin(),com[i].end()),com[i].end());
            ss[i]=(int)com[i].size();
            bit[i].assign(ss[i]+1,0);
        }
    }
    void update(int x,int y,int val){
        for(int i=x;i<=sz;i+=(i&(-i))){
            int ny=get(i,y);
            for(int j=ny;j<=ss[i];j+=(j&(-j))) bit[i][j]+=val;
        }
    }
    int query(int x,int y){
        int res=0;
        for(int i=x;i>=1;i-=(i&(-i))){
            int ny=get(i,y);
            for(int j=ny;j>=1;j-=(j&(-j))) res+=bit[i][j];
        }
        return res;
    }
};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> M >> L >> C;
    for(int i=1;i<=N;i++) cin >> A[i];
    for(int i=1;i<=M;i++) cin >> B[i];
    cin >> Q;
    for(int i=1;i<=Q;i++){
        int v;cin >> v >> T[i];
        qq[v].push_back(i);
    }
    for(int i=1;i<=M;i++){
        int p=(lower_bound(A+1,A+N+1,B[i])-A+2*N-2)%N+1;
        f[p].push_back((B[i]-A[p]+L)%L);
    }
    for(int i=1;i<=N;i++){
        int val=A[i]+((A[i]-A[1])<(C%L))*L-(C%L);
        nxt[i]=upper_bound(A+1,A+N+1,val)-A-1;
        dist[i]=val-A[nxt[i]]+C;deg[nxt[i]]++;
    }

    queue<int> q;
    for(int i=1;i<=N;i++) if(!deg[i]) q.push(i);
    while(!q.empty()){
        int u=q.front();q.pop();
        int v=nxt[u];
        edge[v].push_back(u);
        if(!(--deg[v])) q.push(v);
    }

    BIT cnt,cnt0;
    BIT2 cnt2;

    function<void(int)> pre_dfs = [&](int u){
        child[u]=1;
        for(int &x:f[u]) x+=dd[u],cnt.add(x);
        for(int v:edge[u]){
            dd[v]=dd[u]+dist[v];
            pre_dfs(v);child[u]+=child[v];
            if(child[son[u]]<child[v]) son[u]=v;
        }
    };
    function<void(int,int)> dfs = [&](int u,int t){
        for(int v:edge[u]) if(v!=son[u]) dfs(v,0);
        if(son[u]) dfs(son[u],1),swap(f[u],f[son[u]]);
        else for(int x:f[u]) cnt.update(x,1);
        for(int v:edge[u]) for(int x:f[v]) cnt.update(x,1),f[u].push_back(x);
        if(!deg[u]){
            for(int id:qq[u]) ans[id]=cnt.query(dd[u]+T[id]);
        }
        if(!t) for(int x:f[u]) cnt.update(x,-1);
        /*
        for(int v:edge[u]) dfs(v,0);
        cnt.init();
        for(int v:edge[u]) for(int x:f[v]) f[u].push_back(x);
        for(int x:f[u]) cnt.update(x,1);
        if(!deg[u]){
            for(int id:qq[u]) ans[id]=cnt.query(dd[u]+T[id]);
        }
        */
    };
    for(int i=1;i<=N;i++) if(deg[i]){
        cnt.reset();
        pre_dfs(i);
        cnt.build();
        dfs(i,1);
    }

    for(int i=1;i<=N;i++){
        if(!deg[i]) continue;
        int u=i;
        vector<int> cycle;
        while(deg[u]) cycle.push_back(u),deg[u]=0,u=nxt[u];
        int sz=(int)cycle.size();

        for(int i=1;i<sz;i++) sum[i]=sum[i-1]+dist[cycle[i-1]];
        int total=sum[sz-1]+dist[cycle.back()];
        /*
        for(int i=0;i<sz;i++){
            u=cycle[i];
            for(int id:qq[u]){
                for(int j=0;j<=i;j++) for(int x:f[cycle[j]]){
                    int val=x+sum[i]-sum[j];
                    if(val<=T[id]) ans[id]+=(T[id]-val)/total+1;
                }
                for(int j=i+1;j<sz;j++) for(int x:f[cycle[j]]){
                    int val=x+sum[i]-sum[j]+total;
                    if(val<=T[id]) ans[id]+=(T[id]-val)/total+1;
                }
            }
        }
        */
        cnt.reset();cnt0.reset();
        for(int i=0;i<sz;i++){
            for(int x:f[cycle[i]]){
                int val=x-sum[i];
                int d=(val%total+total)%total;
                int c=(val-d)/total;
                cnt.add(c);cnt0.add(c);
            }
        }
        cnt.build();cnt0.build();

        cnt2.reset();
        cnt2.sz=cnt.sz;
        for(int i=0;i<sz;i++){
            for(int x:f[cycle[i]]){
                int val=x-sum[i];
                int d=(val%total+total)%total;
                int c=(val-d)/total;
                cnt2.add(cnt.get(c),d);
            }
        }
        cnt2.build();

        for(int i=0;i<sz;i++){
            u=cycle[i];
            for(int x:f[u]){
                int val=x-sum[i];
                int d=(val%total+total)%total;
                int c=(val-d)/total;
                cnt2.update(cnt.get(c),d,1);
                cnt0.update(c,1);
                cnt.update(c,c);
            }
            for(int id:qq[u]){
                int val=T[id]-sum[i];
                int b=(val%total+total)%total;
                int a=(val-b)/total;
                ans[id]+=cnt2.query(cnt.get(a),b)+cnt0.query(a)*a-cnt.query(a);
            }
        }

        cnt.init();
        cnt0.init();
        cnt2.init();
        for(int i=sz-1;i>=0;i--){
            u=cycle[i];
            for(int id:qq[u]){
                int val=T[id]-sum[i];
                int b=(val%total+total)%total;
                int a=(val-b)/total-1;
                ans[id]+=cnt2.query(cnt.get(a),b)+cnt0.query(a)*a-cnt.query(a);
            }
            for(int x:f[u]){
                int val=x-sum[i];
                int d=(val%total+total)%total;
                int c=(val-d)/total;
                cnt2.update(cnt.get(c),d,1);
                cnt0.update(c,1);
                cnt.update(c,c);
            }
        }
    }

    for(int i=1;i<=Q;i++) cout << ans[i] << '\n';
}
