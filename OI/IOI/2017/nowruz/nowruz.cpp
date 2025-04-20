#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define pii pair<int,int>
#define piii pair<int,pii>
#define mpp make_pair
#define fi first
#define se second

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=9;test<=10;test++){
        string inp="nowruz"+to_string(test)+".in.txt";
        string out="nowruz"+to_string(test)+".out.txt";
        ifstream cin(inp);
        ofstream cout(out);

        int n,m,S;cin >> n >> m >> S;
        vector<vector<char>> C(n,vector<char>(m));
        for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin >> C[i][j];

        vector<vector<char>> c=C;
        vector<vector<int>> vis(n,vector<int>(m));
        vector<pii> q;
        set<piii> s;
        auto inside = [&](pii x){
            return (x.fi>=0 && x.se>=0 && x.fi<n && x.se<m);
        };
        auto open = [&](pii x){
            return (inside(x) && c[x.fi][x.se]=='.');
        };
        auto adj = [&](pii x,int t){
            return mpp(x.fi+dx[t],x.se+dy[t]);
        };
        auto around = [&](pii x,char cc){
            int cnt=0;
            for(int t=0;t<4;t++){
                if(inside(adj(x,t))) cnt+=(c[x.fi+dx[t]][x.se+dy[t]]==cc);
                else if(cc=='#') cnt++;
            }
            return cnt;
        };
        function<void(pii)> add;
        auto extend = [&](pii x,bool act){
            if(c[x.fi][x.se]!='.' || around(x,'X')!=1) return -1;
            int cnt=0;
            for(int t=0;t<4;t++) if(open(adj(x,t))){
                if(around(adj(x,t),'X')==0){
                    if(act) add(adj(x,t));
                    cnt++;
                }
            }
            if(act) c[x.fi][x.se]='X';
            return cnt;
        };
        add = [&](pii x){
            c[x.fi][x.se]='X';
            for(int t=0;t<4;t++) if(open(adj(x,t))){
                int cnt=extend(adj(x,t),0);
                if(cnt!=-1) s.insert({cnt,adj(x,t)});
            }
        };
        auto bfs = [&](int x,int y){
            int cnt=1,pos=0;
            vis[x][y]=1;
            q.clear();q.push_back({x,y});
            while(pos<(int)q.size()){
                pii p=q[pos++];
                for(int t=0;t<4;t++){
                    pii np=adj(p,t);
                    if(open(np) && !vis[np.fi][np.se]){
                        q.push_back(np);cnt++;
                        vis[np.fi][np.se]=1;
                    }
                }
            }
            return cnt;
        };
        auto get_val = [&](){
            int total=0;
            for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(c[i][j]=='X') total+=(around({i,j},'X')<=1);
            return total;
        };
        vector<pii> P;
        {
            int mx=-1;
            for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(c[i][j]=='.' && !vis[i][j]){
                int sz=bfs(i,j);
                if(sz>mx) mx=sz,P=q;
            }
        }
        int mx=-1,phase=1;
        vector<vector<char>> res;
        function<int(int,int,bool)> dfs = [&](int i,int j,bool ft){
            if(!open(mpp(i,j)) || vis[i][j]==phase || (!ft && around(mpp(i,j),'X')>0)) return 0;
            vis[i][j]=phase;
            int sz=1;
            for(int t=0;t<4;t++) sz+=dfs(i+dx[t],j+dy[t],false);
            return sz;
        };
        for(int it=0;it<1;it++){
            c=C;add(P[(int)P.size()/2]);
            while(true){
                while(!s.empty()){
                    auto t=*s.rbegin();
                    s.erase(t);
                    int cnt=extend(t.se,0);
                    if(cnt==t.fi) extend(t.se,1);
                    else if(cnt!=-1) s.insert({cnt,t.se});
                }
                bool changed = false;
                for(int i=0;i<n;i++){
                    if(changed) continue;
                    for(int j=0;j<m;j++){
                        if(changed) continue;
                        if(c[i][j]=='.' && around(mpp(i,j),'X')==1){
                            add(mpp(i,j));
                            changed=true;
                            break;
                        }
                    }
                }
                if(changed) continue;
                for(int i=0;i<n;i++){
                    if(changed) continue;
                    for(int j=0;j<m;j++){
                        if(changed) continue;
                        if(c[i][j]=='.' && around(mpp(i,j),'X')==2){
                            int cnt=0;
                            for(int t=0;t<4;t++){
                                pii p=adj(mpp(i,j),t);
                                if(open(p) && around(p,'X')==0) cnt++;
                            }
                            if(cnt<2) continue;
                            for(int t=0;t<4;t++){
                                pii p=adj(mpp(i,j),t);
                                if(inside(p) && c[p.fi][p.se]=='X' && around(p,'X')==1){
                                    c[p.fi][p.se]='.';
                                    add(mpp(i,j));
                                    changed=true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if(changed) continue;
                for(int i=0;i<n;i++){
                    if(changed) continue;
                    for(int j=0;j<m;j++){
                        if(changed) continue;
                        if(c[i][j]=='.' && around(mpp(i,j),'X')==2){
                            phase++;
                            int sz=dfs(i,j,true),cnt=0;
                            for(int t=0;t<4;t++){
                                pii p=adj(mpp(i,j),t);
                                if(inside(p) && c[p.fi][p.se]=='X' && around(p,'X')==1) cnt++;
                            }
                            if((cnt==2 && sz<7) || sz<4) continue;
                            for(int t=0;t<4;t++){
                                pii p=adj(mpp(i,j),t);
                                if(inside(p) && c[p.fi][p.se]=='X' && around(p,'X')==1){
                                    c[p.fi][p.se]='.';
                                    add(mpp(i,j));
                                    changed=true;
                                    break;
                                }
                            }
                        }
                    }
                }
                if(!changed) break;
            }


            int val=get_val();
            if(val>mx) mx=val,res=c;
        }

        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(res[i][j]!='#') res[i][j]^='X'^'.';
                cout << res[i][j];
            }
            cout << '\n';
        }
        cerr << mx << ' ' << S << endl;
    }
}
