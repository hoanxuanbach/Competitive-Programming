#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> pp(0.0,1.0);
#define pii pair<int,int>
#define fi first
#define se second

int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}
double rnd(){
    return pp(rng);
}

int N[]={6,100,100,100,100,11,20,20,11,200},
    M[]={10,100,100,100,100,11,20,20,21,200},
    S[]={20,4000,4000,4000,5000,54,33,95,104,7800};

int dx[]={0,-1,0,1},
    dy[]={-1,0,1,0};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int t=5;t<=5;t++){
        string inp="field"+(t<9?to_string(t+1):"A")+".txt";
        string out="maze"+(t<9?to_string(t+1):"A")+".txt";
        ifstream cin(inp);
        ofstream cout(out);

        vector<vector<char>> c(N[t],vector<char>(M[t]));
        for(int i=0;i<N[t];i++){
            for(int j=0;j<M[t];j++) cin >> c[i][j];
        }
        vector<vector<char>> res;
        int mx=0;

        vector<pii> E,I;
        for(int i=1;i<N[t]-1;i++){
            if(c[i][0]!='X') E.push_back({i,0});
            if(c[i][M[t]-1]!='X')E.push_back({i,M[t]-1});
        }
        for(int i=1;i<M[t]-1;i++){
            if(c[0][i]!='X') E.push_back({0,i});
            if(c[N[t]-1][i]!='X') E.push_back({N[t]-1,i});
        }
        for(int i=1;i<N[t]-1;i++) for(int j=1;j<M[t]-1;j++) if(c[i][j]!='X') I.push_back({i,j});

        vector<vector<int>> dist(N[t],vector<int>(M[t],0));
        vector<vector<char>> cc=c;

        auto get_dist = [&](){
            dist.assign(N[t],vector<int>(M[t],-1));
            int sx=-1,sy=-1;
            for(auto [x,y]:E) if(cc[x][y]=='.') sx=x,sy=y;

            int val=0;dist[sx][sy]=1;
            queue<pii> q;q.push({sx,sy});
            while(!q.empty()){
                auto [x,y]=q.front();q.pop();
                val=max(val,dist[x][y]);
                for(int k=0;k<4;k++){
                    int xt=x+dx[k],yt=y+dy[k];
                    if(xt<=0 || yt<=0 || xt>=N[t]-1 || yt>=M[t]-1 || dist[xt][yt]!=-1 || cc[xt][yt]!='.') continue;
                    dist[xt][yt]=dist[x][y]+1;
                    q.push({xt,yt});
                }
            }
            return val;
        };

        cc[1][0]='.';
        int cur=get_dist();
        res=cc,mx=cur;

        int it=1000000000;
        int cnt=0;

        for(long double T=3;true;T*=0.999999999){
            int k=rand_int(0,1);cnt++;
            if(cnt%10000000==0){
                ofstream cout(out);
                for(int i=0;i<N[t];i++){
                    for(int j=0;j<M[t];j++) cout << res[i][j];
                    cout << '\n';
                }
            }
            if(!k){
                int sx=-1,sy=-1;
                for(auto [x,y]:E) if(cc[x][y]=='.') sx=x,sy=y;
                int i=rand_int(0,(int)E.size()-1);
                auto [tx,ty]=E[i];
                cc[sx][sy]='#';cc[tx][ty]='.';
                int nw=get_dist();
                if(nw>mx){
                    mx=nw,res=cc;
                    cerr << mx << endl;
                }
                if(nw>cur || exp((nw-cur)/T)>=rnd()) cur=nw;
                else{
                    cc[tx][ty]='#';
                    cc[sx][sy]='.';
                }
            }
            else{
                int i=rand_int(0,(int)I.size()-1);
                auto [x,y]=I[i];
                cc[x][y]='.'+'#'-cc[x][y];
                int nw=get_dist();
                if(nw>mx){
                    mx=nw,res=cc;
                    cerr << mx << endl;
                }
                if(nw>cur || exp((nw-cur)/T)>=rnd()) cur=nw;
                else{
                    cc[x][y]='.'+'#'-cc[x][y];
                }
            }
            //cerr << cur << endl;
        }

        cerr << mx << ' ' << S[t] << endl;
    }
}
