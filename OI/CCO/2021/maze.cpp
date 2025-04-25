#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define fi first
#define se second
const int maxn = 8e5+5;

int n,q,S,cnt[maxn],d[maxn];
vector<int> c[maxn],f[maxn];
vector<pii> qq[maxn];

pii pos[maxn];
int res[maxn];
vector<int> E;

void dfs(int u,int p){
    pos[u].fi=(int)E.size();
    E.push_back(u);
    int dd=d[u];
    cnt[dd]++;S=max(S,dd);
    f[dd].push_back(u);
    //cout << u << ' ' << dd << '\n';
    for(int v:c[u]){
        if(v==p) dd++;
        else{
            d[v]=dd;
            if(dd>d[u]) dfs(v,u);
        }
    }
    for(int v:c[u]){
        if(v==p) break;
        dfs(v,u);
    }
    if(p){
        pos[u].se=(int)E.size();
        E.push_back(p);
    }
    else pos[u].se=-1;
}

int tree[8*maxn];
void update(int l,int r,int id,int p){
    if(l==r){
        tree[id]++;
        return;
    }
    int mid=(l+r)>>1;
    if(p<=mid) update(l,mid,id<<1,p);
    else update(mid+1,r,id<<1|1,p);
    tree[id]=tree[id<<1]+tree[id<<1|1];
}
int query(int l,int r,int id,int k){
    if(l==r) return E[l];
    int mid=(l+r)>>1;
    if(tree[id<<1]<k) return query(mid+1,r,id<<1|1,k-tree[id<<1]);
    else return query(l,mid,id<<1,k);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int k;cin >> k;
        c[i].assign(k,0);
        for(int j=0;j<k;j++) cin >> c[i][j];
        c[i].push_back(c[i][0]);
        c[i].erase(c[i].begin());
    }
    dfs(1,0);
    for(int i=1;i<=S;i++) cnt[i]+=cnt[i-1];
    for(int i=0;i<=S;i++){
        //cout << '*' << i << ' ' << cnt[i] << '\n';
        cnt[i]=2*(cnt[i]-1);
        if(i) cnt[i]+=cnt[i-1];
    }
    for(int i=1;i<=q;i++){
        int k;cin >> k;
        int p=upper_bound(cnt,cnt+S+1,k)-cnt;
        if(p>0) k-=cnt[p-1];
        if(p<=S) qq[p].push_back({k,i});
        else qq[S].push_back({k%(2*(n-1)),i});
    }
    int sz=(int)E.size()-1;
    for(int i=0;i<=S;i++){
        for(int u:f[i]){
            int a=pos[u].fi,b=pos[u].se;
            if(a>=0) update(0,sz,1,a);
            if(b>=0) update(0,sz,1,b);
        }
        for(auto [k,id]:qq[i]) res[id]=query(0,sz,1,k+1);
    }
    for(int i=1;i<=q;i++) cout << res[i] << '\n';
}
