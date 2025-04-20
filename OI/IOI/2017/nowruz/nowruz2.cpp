#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=1;test<=1;test++){
        string inp="nowruz"+to_string(test)+".in.txt";
        string out="nowruz"+to_string(test)+".out.txt";
        ifstream cin(inp);
        ofstream cout(out);

        int n,m,S;cin >> n >> m >> S;
        vector<vector<char>> c(n,vector<char>(m));
        vector<pair<int,int>> p;
        for(int i=0;i<n;i++) for(int j=0;j<m;j++){
            cin >> c[i][j];
            if(c[i][j]=='.') p.push_back({i,j});
        }


        int mx=0;
        vector<vector<int>> ans;

        auto solve = [&](int x,int y){
            vector<vector<int>> a(n,vector<int>(m));
            vector<vector<bool>> ok(n,vector<bool>(m));
            queue<pair<int,int>> q;

            auto check = [&](int cx,int cy){
                return (cx<0 || cy<0 || cx>=n || cy>=m);
            };
            auto f = [&](int cx,int cy){
                if(check(cx,cy) || c[cx][cy]=='#') return -1;
                int cnt=0;
                for(int t=0;t<4;t++){
                    int xt=cx+dx[t],yt=cy+dy[t];
                    if(!check(xt,yt)) cnt+=a[xt][yt];
                }
                return cnt;
            };
            a[x][y]=1;
            while(true){
                int add=0;
                for(int i=0;i<n;i++) for(int j=0;j<m;j++){
                    if(a[i][j]) continue;
                    if(f(i,j)==1) ok[i][j]=1,add=1;
                }
                for(int i=0;i<n;i++) for(int j=0;j<m;j++){
                    if(ok[i][j]) a[i][j]=1,ok[i][j]=0;
                }
                if(!add) break;
            }

            int cnt=0;
            for(int i=0;i<n;i++) for(int j=0;j<m;j++) cnt+=(f(i,j)==1);
            if(cnt>mx) mx=cnt,ans=a;
        };

        //if(c[0][0]=='.') solve(0,0);
        if(c[n/2][m/2]=='.') solve(n/2,m/2);
        /*
        int T=100;
        for(int it=0;it<T;it++){
            int id=rand_int(0,(int)p.size()-1);
            solve(p[id].first,p[id].second);
        }
        */

        cerr << S << ' ' << mx << endl;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(c[i][j]=='#') cout << '#';
                else cout << (ans[i][j]?'.':'X');
            }
            cout << '\n';
        }

    }
}

