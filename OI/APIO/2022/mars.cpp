#include "mars.h"
#include<bits/stdc++.h>
using namespace std;
const int maxn = 50;
#define pii pair<int,int>
#define fi first
#define se second

int dx[]={0,0,1,-1},
    dy[]={1,-1,0,0};

char c[maxn][maxn];
int f[maxn][maxn],cnt,K;

bool check(int x,int y){
    return (x<0 || y<0 || x>K || y>K || min(x,y)>2 || c[x][y]=='0');
}

void dfs(int x,int y){
    for(int t=0;t<4;t++){
        int xt=x+dx[t],yt=y+dy[t];
        if(check(xt,yt) || f[xt][yt]) continue;
        f[xt][yt]=f[x][y];
        dfs(xt,yt);
    }
}

int par[maxn*maxn];
bool used[maxn*maxn];
int findpar(int u){
    if(u!=par[u]) return par[u]=findpar(par[u]);
    return u;
}
void unions(int u,int v){
    u=findpar(u);v=findpar(v);
    if(u==v) return;
    par[v]=u;
}

string process(std::vector <std::vector<std::string>> a, int x, int y, int k, int n)
{

    if(max(x,y)<=2*(n-k-2)) return a[0][0];
    else if(x>y){
        a[0][0][1]=a[1][0][0];
        for(int i=0;i<=2*k;i++) a[0][0][2+i]=a[2][0][i];
        return a[0][0];
    }
    else if(x<y){
        a[0][0][1]=a[0][1][0];
        for(int i=0;i<=2*k;i++) a[0][0][2+i]=a[0][2][i];
        return a[0][0];
    }
    else if(x==2*(n-k-1)-1){
        for(int i=0;i<=2*k;i++) a[0][0][1+i]=a[1][2][i];
        for(int i=0;i<=2*k;i++) a[0][0][1+2*k+1+i]=a[2][1][i];
        return a[0][0];
    }
    else{
        for(int i=0;i<=2;i++) for(int j=0;j<=2;j++) c[i][j]=a[i][j][0];
        for(int i=1;i<=2*k;i++){
            c[0][2+i]=a[0][2][i];
            c[1][2+i]=a[1][2][i];
            c[2+i][0]=a[2][0][i];
            c[2+i][1]=a[2][1][i];
        }
        for(int i=0;i<=2*(k-1);i++){
            c[2][3+i]=a[1][1][1+i];
            c[3+i][2]=a[1][1][1+2*(k-1)+1+i];
        }
        if(k){
            c[2][2*k+2]=a[2][2][1];
            c[2*k+2][2]=a[2][2][2];
        }
        vector<vector<pii>> p;
        vector<pii> cur;

        for(int i=2*k+2;i>=2;i--){
            for(int j=2;j<=2*k+2 && min(i,j)<=2;j++){
                //if(k) cout << c[i][j];
                if(c[i][j]=='1') cur.push_back({i,j});
                else if(!cur.empty()){
                    p.push_back(cur);
                    cur.clear();
                }
            }
            //if(k) cout << '\n';
        }
        if(!cur.empty()) p.push_back(cur);

        memset(f,0,sizeof(f));
        int sz=(int)p.size();
        string S;cnt=0;
        vector<int> x(sz,0);

        if(k){
            for(int i=0;i<2*sz;i++) S+=a[2][2][3+i];
            //cout << "*" << k << ' ' << S << '\n';
            vector<int> cc;
            for(int i=0;i<sz;i++){
                if(S[i<<1]=='1'){
                    x[i]=++cnt;
                    cc.push_back(i);
                }
                if(S[i<<1|1]=='1'){
                    x[i]=x[cc.back()];
                    cc.pop_back();
                }
                if(S[i<<1]=='0' && S[i<<1|1]=='0') x[i]=x[cc.back()];
            }
            //cout << x[0] << ' ' << x[1] << '\n';
            for(int i=0;i<sz;i++) for(auto [u,v]:p[i]) f[u][v]=x[i];
        }

        K=2*k+2;
        for(int i=0;i<=2*k+2;i++){
            for(int j=0;j<=2*k+2 && min(i,j)<=2;j++){
                if(c[i][j]=='1'){
                    if(!f[i][j]) f[i][j]=++cnt;
                    dfs(i,j);
                }
                //if(k) cout << c[i][j];
            }
            //if(k) cout << '\n';
        }

        for(int i=1;i<=cnt;i++) par[i]=i,used[i]=false;
        for(int i=0;i<=2*k+2;i++) for(int j=0;j<=2*k+2 && min(i,j)<=2;j++){
            if(c[i][j]!='1') continue;
            for(int t=0;t<4;t++){
                int xt=i+dx[t],yt=j+dy[t];
                if(check(xt,yt)) continue;
                unions(f[i][j],f[xt][yt]);
            }
        }
        /*
        for(int i=0;i<=2*k+2;i++){
            for(int j=0;j<=2*k+2 && min(i,j)<=2;j++) cout << findpar(f[i][j]);
            cout << '\n';
        }
        */

        for(int i=0;i<=2*k+2;i++){
            for(int j=0;j<=2*k+2 && min(i,j)==0;j++){
                f[i][j]=findpar(f[i][j]);
                used[f[i][j]]=true;
                //cout << f[i][j];
            }
            //cout << '\n';
        }
        //cout << '*' << cnt << '\n';
        int num=0;
        if(k){
            for(int i=9;i>=0;i--) num=num<<1|(a[2][2][3+2*sz+i]-'0');
            //cout << '*' << num << '\n';
        }
        for(int i=1;i<=cnt;i++) if(findpar(i)==i && !used[i]) num++;

        if(k==n-1){
            for(int i=1;i<=cnt;i++) if(findpar(i)==i && used[i]) num++;
            string res;
            for(int i=0;i<10;i++) res+=char((num>>i&1)+'0');
            while((int)res.length()<100) res+='0';
            return res;
        }

        string res;
        res+=c[0][0];
        res+=c[0][2*k+2];
        res+=c[2*k+2][0];

        p.clear();
        cur.clear();
        for(int i=2*k+2;i>=0;i--) for(int j=0;j<=2*k+2 && min(i,j)==0;j++){
            if(c[i][j]=='1') cur.push_back({i,j});
            else if(!cur.empty()){
                p.push_back(cur);
                cur.clear();
            }
        }
        if(!cur.empty()) p.push_back(cur);

        sz=(int)p.size();
        x.assign(sz,0);
        for(int i=0;i<sz;i++) x[i]=f[p[i][0].fi][p[i][0].se];
        string add(2*sz,'0');

        vector<int> lst(cnt+1,-1);
        for(int i=0;i<sz;i++){
            if(lst[x[i]]==-1) add[i<<1]='1';
            lst[x[i]]=i;
        }
        for(int i=1;i<=cnt;i++) if(lst[i]!=-1) add[lst[i]<<1|1]='1';
        //cout << "***" << add << '\n';
        res+=add;
        for(int i=0;i<10;i++) res+=char((num>>i&1)+'0');
        while((int)res.length()<100) res+='0';
        return res;
    }
	return std::string(100 ,'0');
}
