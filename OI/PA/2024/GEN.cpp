#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}

const int N=10;

int n,m,q;
vector<array<int,2>> cc;
void add(int u,int v){
    if(u>v) swap(u,v);
    cc.push_back({u,v});
}

void get_del(){
    int i=rand_int(0,(int)cc.size()-1);
    cout << 2 << ' ' << cc[i][0] << ' ' << cc[i][1] << '\n';
    cc.erase(cc.begin()+i);
}
void get_add(){
    if((int)cc.size()==n-1) return get_del();
    vector<int> par(n+1);
    iota(par.begin(),par.end(),0);
    function<int(int)> findpar = [&](int u){
        if(u!=par[u]) return par[u]=findpar(par[u]);
        return u;
    };
    for(auto [u,v]:cc) par[findpar(u)]=findpar(v);
    vector<vector<int>> g;
    vector<array<int,2>> cur;
    for(int i=1;i<=n;i++) cur.push_back({findpar(i),i});
    sort(cur.begin(),cur.end());
    for(int i=0;i<(int)cur.size();i++){
        if(!i || cur[i][0]!=cur[i-1][0]) g.push_back({cur[i][1]});
        else g.back().push_back(cur[i][1]);
    }
    int sz=(int)g.size();
    int x=-1,y=-1;
    do{
        x=rand_int(0,sz-1);
        y=rand_int(0,sz-1);
    }while(x==y);
    int i=rand_int(0,(int)g[x].size()-1),j=rand_int(0,(int)g[y].size()-1);
    int d=rand_int(1,N);
    cout << 1 << ' ' << g[x][i] << ' ' << g[y][j] << ' ' << d << '\n';
    add(g[x][i],g[y][j]);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    freopen("KOL.INP","w",stdout);
    n=rand_int(4,N);m=rand_int(0,n-1);q=rand_int(N,2*N);
    cout << n << ' ' << m << ' ' << q << '\n';
    vector<array<int,3>> e;
    for(int i=2;i<=n;i++) e.push_back({rand_int(1,i-1),i,rand_int(1,N)});
    shuffle(e.begin(),e.end(),rng);
    for(int i=0;i<m;i++){
        cout << e[i][0] << ' ' << e[i][1] << ' ' << e[i][2] << '\n';
        add(e[i][0],e[i][1]);
    }
    for(int i=1;i<=q;i++){
        int op=min(4,rand_int(1,5));
        if(op==4) cout << 4 << ' ' << rand_int(1,n) << '\n';
        else if(op==3){
            int u=rand_int(1,n),k=rand_int(1,N),z=rand_int(1,2*N);
            cout << 3 << ' ' << u << ' ' << z << ' ' << k << '\n';
        }
        else if(op==2) get_del();
        else get_add();
    }
}
