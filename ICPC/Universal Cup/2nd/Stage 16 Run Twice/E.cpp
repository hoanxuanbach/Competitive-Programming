#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define ll long long
#define ull unsigned long long
#define pii pair<int,int>
#define mpp make_pair
#define fi first
#define se second

const int N=28558,M=3919;
int S[]={2,3,2,2,3,2,2,2,2,2,2,3,3,2,2,2,1,3,3,2,2,2,2,1,2,2};
struct Password{
    string s;
    ull mask=0;
    Password(){};
    Password(string ss):s(ss){
        vector<int> cnt(26);
        for(char c:s) cnt[c-'a']++;
        int total=0;
        for(int i=0;i<26;i++){
            mask+=((1ULL<<min(S[i],cnt[i]))-1)<<total;
            total+=S[i];
        }
    }
    int submask(Password P){
        return (mask&P.mask)==P.mask;
    }
    friend bool operator<(Password a,Password b){
        return a.s<b.s;
    }
};

int f[M][M];
Password P[N],K[M];
vector<int> V[N];
map<string,int> key,pass;
bitset<M> g[N],c[M];

void init(){
    int n;cin >> n;
    for(int i=0;i<N;i++){
        string s;cin >> s;
        P[i]=s;pass[s]=i;
    }
    int m;cin >> m;
    for(int i=0;i<M;i++){
        string s;cin >> s;
        K[i]=s;
    }
    shuffle(K,K+M,mt19937(24));
    for(int i=0;i<M;i++) key[K[i].s]=i;

    vector<pii> order(N);
    for(int i=0;i<N;i++){
        order[i].se=i;
        for(int j=0;j<M;j++){
            g[i][j]=P[i].submask(K[j]);
        }
        order[i].fi=g[i].count();
    }
    sort(order.begin(),order.end());
    for(int i=0;i<M;i++) c[i].set();
    for(auto [cnt,id]:order){
        if(cnt<3) continue;
        vector<int> res;
        function<vector<int>()> get = [&](){
            for(int x=g[id]._Find_first();x<M;x=g[id]._Find_next(x)){
                bitset<M> ny=g[id]&c[x];
                for(int y=ny._Find_next(x);y<M;y=ny._Find_next(y)){
                    if(!c[x][y]) continue;
                    bitset<M> nz=ny&c[y];
                    for(int z=ny._Find_next(y);z<M;z=nz._Find_next(z)){
                        if(!c[x][z] || !c[y][z]) continue;
                        return res={x,y,z};
                    }
                }
            }
            for(int x=g[id]._Find_first();x<M;x=g[id]._Find_next(x)){
                if(c[x][x]) return res={x,x,x};
            }
            return res={-1,-1,-1};
        };
        V[id]=get();
        int x=V[id][0],y=V[id][1],z=V[id][2];
        if(x==-1) continue;
        c[x][y]=c[x][z]=c[y][z]=c[y][x]=c[z][x]=c[z][y]=0;
        f[x][y]=f[x][z]=f[y][z]=f[y][x]=f[z][x]=f[z][y]=id+1;
    }
}
void encode(string s){
    int id=pass[s];
    //cout << id << ' ' << V[id][0] << ' ' << V[id][1] << ' ' << V[id][2] << '\n';
    assert(V[id][0]!=-1 && V[id][1]!=-1 && V[id][2]!=-1);
    cout << K[V[id][0]].s << ' ' << K[V[id][1]].s << ' ' << K[V[id][2]].s << '\n';
}
void decode(string a,string b){
    int x=key[a],y=key[b];
    assert(f[x][y]);
    cout << P[f[x][y]-1].s << '\n';
}

void solve(){
    string type;cin >> type;
    int n;cin >> n;
    vector<pair<string,string>> p(n);
    if(type=="password"){
        for(int i=0;i<n;i++) cin >> p[i].fi;
    }
    else{
        for(int i=0;i<n;i++) cin >> p[i].fi >> p[i].se;
    }
    init();
    if(type=="password"){
        for(int i=0;i<n;i++) encode(p[i].fi);
    }
    else{
        for(int i=0;i<n;i++) decode(p[i].fi,p[i].se);
    }
}

signed main(){
    //freopen("input.txt","r",stdin);
    //freopen("001.phase1.full.input","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
