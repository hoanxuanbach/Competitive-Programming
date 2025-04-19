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
int get(vector<pii> add){
    int val=eval(add);
    if(val<ans){
        ans=val,A=add;
        cerr << ans << endl;
    }
    return val;
}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    string inp=to_string(4)+".in";
    string out=to_string(4)+".ans";
    ifstream cin(inp);

    int W0;cin >> n >> K >> W0;
    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end());
    int S=600;
    auto MP = [&](vector<int> X,int i){
        vector<pii> add;
        for(int u:X) add.push_back({u,i});
        return add;
    };

    vector<int> C;
    for(int j=1;j<=n;j++) if(S!=j && !binary_search(G[S].begin(),G[S].end(),j)) C.push_back(j);
    vector<double> score(n+1);
    for(int x:C) score[x]=(int)G[x].size();
    sort(C.begin(),C.end(),[&](int x,int y){return score[x]>score[y];});
    vector<int> X,Y;
    for(int j=0;j<(int)C.size();j++){
        if(j<K) X.push_back(C[j]);
        else Y.push_back(C[j]);
    }
    int cur=eval2(MP(X,S),S),mn=cur;
    long long cnt=0;
    get(MP(X,S));
    for(double T=3;true;T*=0.999999){
        int i=rand_int(0,(int)X.size()-1),j=rand_int(0,(int)Y.size()-1);
        swap(X[i],Y[j]);
        int val=eval2(MP(X,S),S);
        if(val<mn) get(MP(X,S)),mn=val;
        if(val<cur || exp((cur-val)/T)>=rnd(0,1)) cur=val;
        else swap(X[i],Y[j]);
        cnt++;
        if(cnt%100000==0){
            ofstream cout(out);
            for(auto [x,y]:A) cout << x << ' ' << y << '\n';
        }
    }
}
