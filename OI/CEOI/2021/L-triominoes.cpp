#include<bits/stdc++.h>
using namespace std;
const int maxk = 255;
int n,m,k,x[maxk],y[maxk];
bitset<1<<13> f,g;
vector<pair<int,int>> E;

void build(){
    for(int S=0;S<(1<<n);S++){
        function<void(int,int)> dfs = [&](int i,int T){
            if(i==n){
                E.push_back({S,T});
                return;
            }
            if(S>>i&1){
                dfs(i+1,T);
                return;
            }
            if(i<n-1 && !(S>>(i+1)&1)){
                if(!(T>>i&1)) dfs(i+2,T^(1<<i));
                if(!(T>>(i+1)&1)) dfs(i+2,T^(1<<(i+1)));
            }
            if(i && !(T>>i&1) && !(T>>(i-1)&1)) dfs(i+1,T^(3<<(i-1)));
            if(i<n-1 && !(T>>i&1) && !(T>>(i+1)&1)) dfs(i+1,T^(3<<i));
        };
        dfs(0,0);
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> k;
    build();
    vector<int> pos={1,m};
    for(int i=1;i<=k;i++){
        cin >> x[i] >> y[i];
        pos.push_back(y[i]);
    }
    sort(pos.begin(),pos.end());
    pos.erase(unique(pos.begin(),pos.end()),pos.end());
    f[0]=1;
    for(int i=0;i<(int)pos.size();i++){
        int S=0;
        for(int j=1;j<=k;j++) if(y[j]==pos[i]) S|=1<<(x[j]-1);
        g.reset();
        for(int j=0;j<(1<<n);j++) if(!(j&S)) g[j|S]=f[j];
        swap(f,g);

        if(i==(int)pos.size()-1){
            cout << (f[(1<<n)-1]?"YES":"NO") << '\n';
            return 0;
        }
        int d=pos[i+1]-pos[i];
        d=min(d,d%6+6);
        while(d--){
            g.reset();
            for(auto [x,y]:E) if(f[x]) g[y]=1;
            swap(f,g);
        }
    }
}