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

int N = 5;
int M = 6;

#define Puzzle vector<vector<pii>>

/*
Puzzle pieces = {
    {{0,0},{0,1},{1,0}},
    {{0,0}}
};

Puzzle start_pos = {
    {{0,0}},
    {{0,2},{1,1},{1,2},{2,0},{2,1},{2,2},{2,3}}
};
*/

Puzzle pieces = {
    {{0,0},{0,1},{1,0},{1,1}},
    {{0,0},{0,1},{1,0}},
    {{0,1},{1,0},{1,1}},
    {{0,0},{0,1}},
    {{0,0},{1,0}},
    {{0,0}}
};

Puzzle start_pos = {
    {{2,2}},
    {{0,1},{0,4}},
    {{0,2},{3,4}},
    {{4,2}},
    {{1,5},{2,4}},
    {{2,0},{2,1},{3,0},{3,1},{4,0},{4,1}}
};


int dx[] = {0,0,1,-1},
    dy[] = {1,-1,0,0};

int f[15][15];

void solve(){
    vector<Puzzle> X;
    set<Puzzle> S;
    auto add = [&](Puzzle T){
        if(S.find(T)==S.end()){
            S.insert(T);
            X.push_back(T);
            if((int)S.size()%10000==0) cout << (int)S.size() << endl;
        }
    };
    auto dfs = [&](Puzzle T){
        for(int i=0;i<N;i++) for(int j=0;j<M;j++) f[i][j]=0;

        int cnt=0;
        for(int i=0;i<(int)T.size();i++){
            for(auto [x,y]:T[i]){
                cnt++;
                for(auto [fx,fy]:pieces[i]){
                    f[x+fx][y+fy]=cnt;
                }
            }
        }

        cnt=0;
        for(int i=0;i<(int)T.size();i++){
            for(int j=0;j<(int)T[i].size();j++){
                cnt++;
                for(int t=0;t<4;t++){
                    auto [x,y] = T[i][j];
                    x+=dx[t],y+=dy[t];
                    bool move=true;
                    for(auto [fx,fy]:pieces[i]) if(x+fx<0 || x+fx>=N || y+fy<0 || y+fy>=M || (f[x+fx][y+fy]!=0 && f[x+fx][y+fy]!=cnt)) move=false;
                    if(move){
                        Puzzle nT = T;
                        nT[i][j] = {x,y};
                        sort(nT[i].begin(),nT[i].end());
                        add(nT);
                    }
                }
            }
        }
    };
    add(start_pos);
    while(!X.empty()){
        auto T=X.back();X.pop_back();
        dfs(T);
    }

    cout << (int)S.size() << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
