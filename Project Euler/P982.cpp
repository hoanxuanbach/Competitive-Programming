#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ld long double
int f[10][10][10],g[10][10][10];
vector<pii> S[10][10];

void solve(){
    int res=0;
    for(int x=1;x<=6;x++) for(int y=1;y<=6;y++) for(int z=1;z<=6;z++){
        int a=x,b=y,c=z;
        if(a>b) swap(a,b);
        if(a>c) swap(a,c);
        if(b>c) swap(b,c);
        f[a][b][c]++;
    }
    int T=0;
    for(int x=1;x<=6;x++) for(int y=x;y<=6;y++) for(int z=y;z<=6;z++) g[x][y][z]=T++;
    
    vector<vector<ld>> M;
    for(int x=1;x<=6;x++) for(int y=x;y<=6;y++) for(int z=y;z<=6;z++){
        int id=g[x][y][z];
        vector<ld> A(3*T+1);
        A[id*3]=A[id*3+1]=A[id*3+2]=1;
        A[3*T]=(ld)f[x][y][z]/216;
        S[y][z].push_back({id*3,x});
        S[x][z].push_back({id*3+1,y});
        S[x][y].push_back({id*3+2,z});
        M.push_back(A);
    }
    for(int x=1;x<=6;x++) for(int y=x;y<=6;y++){
        vector<ld> A(3*T+1);
        for(auto [id,k]:S[x][y]) A[id]=y-k;
        M.push_back(A);
    }

    vector<int> pos;
    int sz=(int)M.size(),k=0;
    for(int x=0;x<sz;x++){
        bool ok=false;
        while(!ok){
            for(int i=x;i<sz;i++){
                if(M[i][k]!=0){
                    swap(M[i],M[x]);
                    ok=true;
                    break;
                }
            }
            if(!ok) k++;
        }
        pos.push_back(k);
        for(int i=x+1;i<sz;i++){
            ld d=M[i][k]/M[x][k];
            for(int j=k;j<=3*T;j++) M[i][j]-=d*M[x][j];
        }
        k++;
    }

    vector<ld> F(3*T);
    while(!pos.empty()){
        int x=pos.back();pos.pop_back();
        int i=(int)pos.size();
        F[x]=M[i][3*T];
        for(int j=x+1;j<3*T;j++) F[x]-=F[j]*M[i][j];
        F[x]/=M[i][x];
    }

    for(int i=0;i<T;i++){

    }
    for(int i=0;i<3*T;i++) cout << F[i] << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
