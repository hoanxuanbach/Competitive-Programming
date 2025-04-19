#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> pp(0.0,1.0);
#define pii pair<int,int>
#define piii pair<int,pii>
#define fi first
#define se second
const int TL=1000000;
const double Stemp=1000;
const double mul=1e-6;
double query_temp(int tm){
    double res=Stemp*pow(mul,(long double)tm/TL);
    return res;
}
const int maxn=505;
int n,m,Max,cur;
pii f[maxn][maxn];
map<char,int> mp;
char ch[]={'-','|','/',char(92)};
int dx[]={0,1,1,1},
    dy[]={1,0,-1,1};
char c[maxn][maxn],ans[maxn][maxn],x[maxn][maxn];
vector<piii> p;
bool ok(int i,int j){
    if(i<=0 || j<=0 || i>n || j>m) return false;
    return true;
}
void add(int i,int j,int k){
    x[i][j]=ch[k];
    f[i][j]={i,j};
    f[i+dx[k]][j+dy[k]]={i,j};
    f[i-dx[k]][j-dy[k]]={i,j};
}
void del(int ci,int cj){
    int i=f[ci][cj].fi,j=f[ci][cj].se;
    int k=mp[x[i][j]];
    x[i][j]=c[i][j];
    f[i][j]=f[i+dx[k]][j+dy[k]]=f[i-dx[k]][j-dy[k]]={0,0};
}
bool check(int i,int j,int k){
    if(x[i][j]==ch[k]) return false;
    int i1=i+dx[k],j1=j+dy[k],i2=i-dx[k],j2=j-dy[k];
    if(!ok(i1,j1) || !ok(i2,j2)) return false;
    if(c[i1][j1]=='P' && c[i2][j2]=='G') return true;
    if(c[i1][j1]=='G' && c[i2][j2]=='P') return true;
    return false;
}
void getmax(){
    if(cur>max(40000,Max)){
        Max=cur;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++) ans[i][j]=x[i][j];
        }
    }
}
void process(double T){
    int pos=rng()%(int)p.size(),i=p[pos].se.fi,j=p[pos].se.se,k=p[pos].fi,nw=cur+1;
    if(x[i][j]==ch[k]) return;
    if(f[i][j].fi!=0) nw--;
    if(f[i+dx[k]][j+dy[k]].fi!=0) nw--;
    if(f[i-dx[k]][j-dy[k]].fi!=0) nw--;
    if(nw>cur || exp((nw-cur)/T)>=pp(rng)){
        cur=nw;
        if(f[i][j].fi!=0) del(i,j);
        if(f[i+dx[k]][j+dy[k]].fi!=0) del(i+dx[k],j+dy[k]);
        if(f[i-dx[k]][j-dy[k]].fi!=0) del(i-dx[k],j-dy[k]);
        add(i,j,k);
    }
    getmax();
}
signed main(){
    freopen("input_05.txt","r",stdin);
    ofstream fout("output_05.txt");
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) cin >> c[i][j];
    }
    for(int i=0;i<4;i++) mp[ch[i]]=i;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i][j]=='W'){
                for(int k=0;k<4;k++){
                    if(check(i,j,k)) p.push_back({k,{i,j}});
                }
            }
            x[i][j]=c[i][j];
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(c[i][j]=='W'){
                for(int k=0;k<4;k++){
                    if(check(i,j,k) && f[i+dx[k]][j+dy[k]].fi!=0 && f[i-dx[k]][j-dy[k]].fi!=0){cur++;add(i,j,k);}
                }
            }
        }
    }
    getmax();
    auto st=clock();
    while(clock()-st<=TL){
        process(query_temp(clock()-st));
        if(Max>=48620) break;
    }
    fout << Max << '\n';
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++) fout << ans[i][j];
        fout << '\n';
    }
}
