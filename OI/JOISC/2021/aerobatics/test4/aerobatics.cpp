#include<bits/stdc++.h>
using namespace std;
uniform_real_distribution<double> pp(0.0,1.0);

const int maxn = 1e3+5;
const double inf = 1.0e+99;
const double pi =acos(-1);
const double S = 60;
const double A = 156;
const double E = 0.16;
const double eps = 1e-6;

mt19937_64 rng(1);
int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}
mt19937_64 rng2(1);
double rnd(){
    return pp(rng2);
}

int N,X[maxn],Y[maxn];
double D[maxn][maxn];

double get_angle(int a,int b,int c){
    if(a==N || b==N || c==N) return 180.0;
    double diff = abs(D[a][b]-D[a][c]);
    return min(diff,360.0-diff);
}

void build(){
    for(int i=0;i<N;i++) for(int j=0;j<N;j++){
        if(i!=j){
            D[i][j]=arg(complex<double>(X[j]-X[i],Y[j]-Y[i]))*180.0/pi;
            if(D[i][j]<0) D[i][j]+=360.0;
        }
        else D[i][j]=inf;
    }
}

vector<int> solve(){

    int V0=max_element(X,X+N)-X;
    int V1=min_element(D[V0],D[V0]+N)-D[V0];
    vector<int> p(N,-1);
    vector<bool> vis(N+1);
    vis[V0]=1;p[0]=V0;
    vis[V1]=1;p[1]=V1;
    for(int i=2;i<N;i++){
        double mx=-inf;
        for(int j=0;j<N;j++){
            if(vis[j]) continue;
            double angle = get_angle(p[i-1],p[i-2],j);
            if(mx<angle) mx=angle,p[i]=j;
        }
        vis[p[i]]=1;
    }
    //for(int i=0;i<N;i++) p[i]=i;
    vector<array<int,2>> g(N+1);
    vector<double> angle(N+1),val(N+1);
    double total=0;
    auto f = [&](int u){
        total-=val[u];
        angle[u]=get_angle(u,g[u][0],g[u][1]);
        val[u]=(angle[u]<A?min(angle[u]-A,0.0):S);
        total+=val[u];
    };
    auto swap_edge = [&](int u,int a,int v,int b){
        int x=g[u][a],y=g[v][b];
        int c=(g[x][1]==u),d=(g[y][1]==v);
        swap(g[u][a],g[v][b]);
        swap(g[x][c],g[y][d]);
        f(u);f(v);f(x);f(y);
    };
    for(int i=0;i<N;i++){
        g[p[i]][0]=(i?p[i-1]:N);
        g[p[i]][1]=(i<N-1?p[i+1]:N);
    }
    g[N][0]=p[0],g[N][1]=p[N-1];
    for(int i=0;i<=N;i++){
        angle[i]=get_angle(i,g[i][0],g[i][1]);
        val[i]=(angle[i]<A?min(angle[i]-A,0.0):S);
        if(i!=N) total+=val[i];
    }

    double cur=total;
    long long it=0;
    while(true){
        int u=-1,a=-1,v=-1,b=-1;
        it++;
        if(it%1000000==0) cerr << "**** " << it/1000000 << endl;
        do{
            u=rand_int(0,N);
            a=rand_int(0,1);
            v=rand_int(0,N);
            b=rand_int(0,1);
        }while(u>=v || u==g[v][b] || v==g[u][a] || g[u][a]==g[v][b]);
        swap_edge(u,a,v,b);
        double nw=total;
        if(cur+eps<nw){
            cur=nw;
            int cnt=0;
            for(int i=0;i<N;i++) cnt+=(angle[i]>=A);
            cerr << cnt << endl;
            if(cnt>=N) break;
        }
        else if(cur>nw && rnd()>exp((nw-cur)*E)) swap_edge(u,a,v,b);
        else cur=nw;
    }

    auto get_cycle = [&](){
        int cnt=0;
        vis.assign(N+1,false);
        for(int i=0;i<=N;i++){
            if(vis[i]) continue;
            int u=i;cnt++;
            while(!vis[u]) vis[u]=1,u=(vis[g[u][0]]?g[u][1]:g[u][0]);
        }
        return cnt;
    };
    int cc=get_cycle();
    while(cc!=1){
        double mx=-inf;
        vector<array<int,4>> cand;
        for(int u=0;u<=N;u++) for(int v=0;v<u;v++) for(int a=0;a<2;a++) for(int b=0;b<2;b++){
            if(u==g[v][b] || v==g[u][a] || g[u][a]==g[v][b] || g[u][a]==g[v][b^1] || g[u][a^1]==g[v][b]) continue;
            swap_edge(u,a,v,b);
            if(get_cycle() == cc-1){
                double nw=total;
                if(mx+eps<nw) mx=nw,cand.clear();
                if(abs(nw-mx)<eps) cand.push_back({u,a,v,b});
            }
            swap_edge(u,a,v,b);
        }
        cc--;
        auto [u,a,v,b]=cand[rand_int(0,(int)cand.size()-1)];
        swap_edge(u,a,v,b);
    }
    vector<int> P(N+1);
    vis.assign(N+1,false);
    int u=-1;
    for(int i=0;i<N;i++) if(max(g[i][0],g[i][1])==N) u=i;
    vis[P[0]=u]=1;
    for(int i=1;i<=N;i++){
        u=(i!=1 || g[u][0]!=N) && !vis[g[u][0]]?g[u][0]:g[u][1];
        vis[P[i]=u]=1;
    }
    P.pop_back();
    return P;
}

double calculate_angle(vector<int> &P){
    double res=inf;
    for(int i=1;i<N-1;i++) res=min(res,get_angle(P[i],P[i-1],P[i+1]));
    return res;
}

signed main(){
    rng.seed(1);
    freopen("input_04.txt","r",stdin);
    freopen("output_04.txt","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int Z0;cin >> N >> Z0;
    for(int i=0;i<N;i++) cin >> X[i] >> Y[i];
    build();
    vector<int> P=solve();
    for(int i=0;i<N;i++) cout << P[i]+1 << endl;
    cerr << "angle = " << calculate_angle(P) << endl;
}
