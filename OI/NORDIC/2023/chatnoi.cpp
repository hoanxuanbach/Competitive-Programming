#include<bits/stdc++.h>
using namespace std;
const int maxn = 5e5+5;
const int inf = 1e9;
int n,k;

int M=0;
map<string,int> str;

int N=0;
map<vector<int>,int> mp;

int mx,s[maxn],f[maxn];
vector<int> dist[maxn],nxt[maxn];
vector<pair<int,int>> E[maxn];
vector<int> edge[maxn];
int used[maxn],vis[maxn];
string Z,ss[maxn];

void dfs(int u){
    vis[u]=1;
    int val=0,pos=-1;
    for(int v:edge[u]){
        if(!vis[v]) dfs(v);
        if(vis[v]==1) pos=v,val=inf;
        else if(dist[v].back()+1>val) pos=v,val=dist[v].back()+1;
    }
    dist[u].push_back(val);
    nxt[u].push_back(pos);
    vis[u]=2;
}

void build(){
    for(int i=1;i<=n;i++){
        string S;cin >> S;
        if(str.find(S)==str.end()) str[S]=++M,ss[M]=S;
        s[i]=str[S];Z=S;
    }
    map<vector<int>,int> cnt;
    for(int i=1;i<=n-k+1;i++){
        vector<int> cur(k);
        for(int j=0;j<k;j++) cur[j]=s[i+j];
        if(mp.find(cur)==mp.end()) mp[cur]=++N,f[N]=i+k-1;
        if(i<=n-k){
            cur.push_back(s[i+k]);
            cnt[cur]++;
        }
    }
    for(int i=1;i<=n-k;i++){
        vector<int> cur(k);
        for(int j=0;j<k;j++) cur[j]=s[i+j];
        int u=mp[cur];
        cur.push_back(s[i+k]);
        int val=cnt[cur];
        cur.erase(cur.begin());
        int v=mp[cur];
        E[val].push_back({u,v});
        mx=max(mx,val);
    }

    vector<int> V;
    for(int i=mx;i>=1;i--){
        sort(E[i].begin(),E[i].end());
        E[i].erase(unique(E[i].begin(),E[i].end()),E[i].end());
        for(auto [u,v]:E[i]){
            if(!used[u]) V.push_back(u);
            if(!used[v]) V.push_back(v);
            used[u]=used[v]=true;
            edge[u].push_back(v);
        }
        for(int u:V) vis[u]=0;
        for(int u:V) if(!vis[u]) dfs(u);
    }
    for(int i=1;i<=n;i++){
        reverse(dist[i].begin(),dist[i].end());
        reverse(nxt[i].begin(),nxt[i].end());
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    build();
    int q;cin >> q;
    for(int i=1;i<=q;i++){
        int m;cin >> m;
        bool check=true;
        vector<int> cur(k);
        for(int j=0;j<k;j++){
            string S;cin >> S;
            if(str.find(S)==str.end()) check=false;
            else cur[j]=str[S];
        }
        if(mp.find(cur)==mp.end()) check=false;
        if(!check){
            for(int j=1;j<=m;j++) cout << Z << ' ';
            cout << '\n';
            continue;
        }
        int u=mp[cur];
        int l=0,r=(int)dist[u].size();
        while(l<r){
            int d=(l+r+1)>>1;
            if(dist[u][d-1]>=m) l=d;
            else r=d-1;
        }
        if(!l){
            for(int j=1;j<=m;j++) cout << Z << ' ';
            cout << '\n';
            continue;
        }
        while(m--){
            int v=nxt[u][l-1];
            cout << ss[s[f[v]]] << ' ';
            u=v;
        }       
        cout << '\n';
    }
}