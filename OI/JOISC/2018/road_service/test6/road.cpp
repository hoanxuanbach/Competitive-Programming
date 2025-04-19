#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define pii pair<int,int>
#define fi first
#define se second

int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}
double rnd(double l,double r){
    uniform_real_distribution<double> pp(l,r);
    return pp(rng);
}

const int inf = 1e9;
const int maxn = 1005;

int n,K;
vector<int> g[maxn],G[maxn];
int dist[maxn];

int bfs(int s){
    memset(dist,-1,sizeof(dist));
    queue<int> q;q.push(s);dist[s]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:g[u]) if(dist[v]==-1){dist[v]=dist[u]+1;q.push(v);}
    }
    int total=0;
    for(int i=1;i<=n;i++) total+=dist[i];
    return total;
}
int eval(vector<pii> &add){
    for(int i=1;i<=n;i++) g[i]=G[i];
    for(auto [u,v]:add) g[u].push_back(v),g[v].push_back(u);
    int total=0;
    for(int i=1;i<=n;i++) total+=bfs(i);
    return total/2;
}
int eval2(vector<pii> add,int s){
    for(int i=1;i<=n;i++) g[i]=G[i];
    for(auto [u,v]:add) g[u].push_back(v),g[v].push_back(u);
    return bfs(s);
}

int ans=inf;
vector<pii> A;
void get(vector<pii> add){
    int val=eval(add);
    if(val<ans){
        ans=val,A=add;
        cerr << ans << endl;
    }
}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    string inp=to_string(6)+".in";
    string out=to_string(6)+".ans";
    ifstream cin(inp);

    int W0;cin >> n >> K >> W0;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    auto MP = [&](vector<int> X,int i){
        vector<pii> add;
        for(int u:X) add.push_back({u,i});
        return add;
    };
    for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end());
    vector<pair<pair<int,int>,pair<vector<int>,vector<int>>>> T;
    for(int i=1;i<=n;i++){
        vector<int> C;
        for(int j=1;j<=n;j++) if(i!=j && !binary_search(G[i].begin(),G[i].end(),j)) C.push_back(j);
        vector<double> score(n+1);
        for(int t=0;t<100;t++){
            double k=rnd(0,5);
            for(int x:C) score[x]=(int)G[x].size()+rnd(0,k);
            sort(C.begin(),C.end(),[&](int x,int y){return score[x]>score[y];});
            vector<int> X,Y;
            for(int j=0;j<(int)C.size();j++){
                if(j<K) X.push_back(C[j]);
                else Y.push_back(C[j]);
            }
            T.push_back({{eval2(MP(X,i),i),i},{X,Y}});
        }
    }

    cerr << "Start" << endl;
    sort(T.begin(),T.end());
    for(auto tt:T){
        int u=tt.fi.se;
        vector<int> X=tt.se.fi,Y=tt.se.se;
        while(true){
            int cur=eval2(MP(X,u),u);
            int mn=cur,x=-1,y=-1;
            for(int i=0;i<(int)X.size();i++) for(int j=0;j<(int)Y.size();j++){
                swap(X[i],Y[j]);
                int nxt=eval2(MP(X,u),u);
                if(nxt<mn) mn=nxt,x=i,y=j;
                swap(X[i],Y[j]);
            }
            get(MP(X,u));
            if(mn<cur) swap(X[x],Y[y]);
            else break;
        }
        get(MP(X,u));
        cerr << "cout" << endl;
        ofstream cout(out);
        for(auto [x,y]:A) cout << x << ' ' << y << '\n';
    }
}
