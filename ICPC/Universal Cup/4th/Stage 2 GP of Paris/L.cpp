#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int maxn = 1e6+5;


vector<pair<int,int>> gg[maxn];
vector<int> g[maxn];

bool leaf[maxn];
int dp[maxn][6][2][2];

int f(int u,int e,int a,int b){
    if(dp[u][e][a][b]!=-1) return dp[u][e][a][b];
        
    int cnt=0,has_leaf=0;
    pair<int,int> x={-1,-1},y={-1,-1},z={-1,-1};
    for(int i=0;i<(int)gg[u].size();i++){
        if((i+1)==e) continue;
        auto [v,id]=gg[u][i];
        cnt++;
        if(leaf[v]) has_leaf=1;
        else if(x.first==-1) x={v,id};
        else if(y.first==-1) y={v,id};
        else z={v,id};
    }

    int &res = dp[u][e][a][b];
    if(cnt-has_leaf>3) return res=0; 
    if(a==0){   
        if(cnt-has_leaf>=3) return res=0; 
        if(b==1){
            if(y.first!=-1) return res=0;
            else if(x.first!=-1) return res=f(x.first,x.second,1,1);
            else return res=1;
        }    
        if(y.first!=-1){
            return res=(f(x.first,x.second,0,0)&f(y.first,y.second,1,1))|(f(x.first,x.second,1,1)&f(y.first,y.second,0,0));
        }
        else if(x.first!=-1){
            if(has_leaf) return res=f(x.first,x.second,1,1)|f(x.first,x.second,0,0);
            else return res=f(x.first,x.second,1,0)|f(x.first,x.second,0,0); 
        }
        else return res=1;
    }
    else{
        if(b==1){
            if(cnt-has_leaf>=3) return res=0; 
            if(y.first!=-1) return res=0;
            else if(x.first!=-1) return res=f(x.first,x.second,0,1);
            else return res=1;
        }
        if(z.first!=-1){
            res=f(x.first,x.second,0,1)&f(y.first,y.second,1,1)&f(z.first,z.second,0,0);
            res|=f(x.first,x.second,0,1)&f(z.first,z.second,1,1)&f(y.first,y.second,0,0);
            res|=f(y.first,y.second,0,1)&f(x.first,x.second,1,1)&f(z.first,z.second,0,0);
            res|=f(y.first,y.second,0,1)&f(z.first,z.second,1,1)&f(x.first,x.second,0,0);
            res|=f(z.first,z.second,0,1)&f(y.first,y.second,1,1)&f(x.first,x.second,0,0);
            res|=f(z.first,z.second,0,1)&f(x.first,x.second,1,1)&f(y.first,y.second,0,0);
            return res;
        }
        else if(y.first!=-1){
            res=f(x.first,x.second,0,1)&(f(y.first,y.second,0,0)|f(y.first,y.second,1,0));
            res|=f(y.first,y.second,0,1)&(f(x.first,x.second,0,0)|f(x.first,x.second,1,0));
            return res;
        }
        else if(x.first!=-1){
            if(has_leaf) return res=f(x.first,x.second,0,0)|f(x.first,x.second,1,0);
            else return res=f(x.first,x.second,0,0);
        }
        else return res=1;
    }
}

void solve(){
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        g[i].clear();
        gg[i].clear();
        leaf[i]=false;
        for(int j=0;j<=5;j++) for(int a=0;a<=1;a++) for(int b=0;b<=1;b++) dp[i][j][a][b]=-1;
    }

    for(int i=1;i<n;i++){
        int u,v;cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bool check=true;
    for(int i=1;i<=n;i++) if((int)g[i].size()>2) check=false;
    if(check){
        cout << 1 << '\n';
        return;
    }
    for(int i=1;i<=n;i++) if((int)g[i].size()==1) leaf[i]=1;

    for(int i=1;i<=n;i++){
        if(leaf[i]) continue;
        bool add=false;
        for(int v:g[i]){
            if(leaf[v]!=1){
                gg[i].push_back({v,-1});
            }
            else if(!add){
                gg[i].push_back({v,-1});
                gg[v].push_back({i,-1});
                add=true;
            }
        }
    }

    for(int i=1;i<=n;i++){
        if(gg[i].empty()) continue;
        if((int)gg[i].size()>5){
            cout << 3 << '\n';
            return;
        }
        for(auto &[v,id]:gg[i]){
            for(int j=0;j<(int)gg[v].size();j++) if(gg[v][j].first==i) id=j+1;
        }
    }

    for(int i=1;i<=n;i++){
        if(gg[i].empty()) continue;
        if(f(i,0,0,0)) check=true;
        //cout << '*' << i << ' ' << f(i,0,0,0) << '\n';
    }
    if(check) cout << 2 << '\n';
    else cout << 3 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}