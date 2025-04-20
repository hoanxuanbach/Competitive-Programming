#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=1;test<=11;test++){
        string T=to_string(test);
        if(test<=9) T="0"+T;
        ifstream cin(T);
        ofstream cout(T+".out");
        int n;cin >> n;
        vector<vector<int>> p(n+1,vector<int>(n+1,0));
        vector<vector<int>> res;
        auto add = [&](int x,int y,int u,int v){
            res.push_back({x,y,u,v});
            p[x][y]^=1;p[x][v]^=1;p[u][y]^=1;p[u][v]^=1;
            assert(0<=x && 0<=y && x<u && u<=n && y<v && v<=n);
        };
        for(int i=0;i<n;i++) for(int j=0;j<n;j++){
            char c;cin >> c;
            p[i][j]=c-'0';
        }
        for(int i=n;i>=0;i--) for(int j=n;j>=0;j--){
            if(i) p[i][j]^=p[i-1][j];
            if(j) p[i][j]^=p[i][j-1];
            if(i && j) p[i][j]^=p[i-1][j-1];
        }
        for(int i=0;i<=n;i++) for(int j=0;j<=n;j++){
            if(!p[i][j]) continue;
            vector<int> x,y;
            for(int k=i+1;k<=n;k++) if(p[k][j]) x.push_back(k);
            for(int k=j+1;k<=n;k++) if(p[i][k]) y.push_back(k);
            assert(!x.empty() && !y.empty());
            bool found=false;
            for(int cx:x){
                for(int cy:y){
                    if(p[cx][cy]){
                        found=true;
                        add(i,j,cx,cy);
                        break;
                    }
                }
                if(found) break;
            }
            if(!found) add(i,j,x[0],y[0]);
        }
        cout << (int)res.size() << '\n';
        for(auto a:res) cout << a[1]+1 << ' ' << a[3] << ' ' << a[0]+1 << ' ' << a[2] << '\n';
        for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) if(p[i][j]) assert(false);
    }
}
