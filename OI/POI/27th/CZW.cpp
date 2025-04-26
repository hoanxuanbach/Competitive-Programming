#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define int long long
#define pii pair<int,int>
const int mod=1e9+7;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
bool vis[maxn];
vector<int> adj[maxn];
map<int,int> mp;
vector<int> v,Max;
// nxt 0,0:(x,y)->(x,y) 1,0:(x,y)->(x+(1<<m),y) 0,1: (x,y)->(x,y+(1<<m)) 1,1:(x,y)->(x+(1<<m),y+(1<<m))
// pos 0,0:x+(1<<m),y 0,1: x-(1<<m),y 1,0:x,y+(1<<m) 1,1:x,y-(1<<m)
int m,n,pos[2][2],nxt[maxn][2][2],sz[maxn],cnt;
string s;
//add px*(1<<m), py*(1<<m)
int f(int u,int x,int y){
    if(u==-1) return -1;
    if(nxt[u][x][y]==0) return u;
    return nxt[u][x][y];
}
void update(int u,int px,int py){
    if(px==0 && py==0){
        pos[0][0]=nxt[u][1][0];
        pos[1][0]=nxt[u][0][1];
        pos[0][1]=f(pos[0][1],1,0);
        pos[1][1]=f(pos[1][1],0,1);
    }
    if(px==0 && py==1){
        pos[0][0]=nxt[u][1][1];
        pos[1][0]=f(pos[1][0],0,0);
        pos[0][1]=f(pos[0][1],1,1);
        pos[1][1]=nxt[u][0][0];
    }
    if(px==1 && py==0){
        pos[0][0]=f(pos[0][0],0,0);
        pos[1][0]=nxt[u][1][1];
        pos[0][1]=nxt[u][0][0];
        pos[1][1]=f(pos[1][1],1,1);
    }
    if(px==1 && py==1){
        pos[0][0]=f(pos[0][0],0,1);
        pos[1][0]=f(pos[1][0],1,0);
        pos[0][1]=nxt[u][0][1];
        pos[1][1]=nxt[u][1][0];
    }
}
void dfs(int u){
    /*
    cout << u << '\n';
    for(int i=0;i<=1;i++){
        for(int j=0;j<=1;j++) cout << pos[i][j] << ' ';
        cout << '\n';
    }
    */
    if(s[u]=='0' || s[u]=='1'){
        if(s[u]=='0') return;
        for(int i=0;i<=1;i++){
            for(int j=0;j<=1;j++){
                if(pos[i][j]==-1) continue;
                if(s[pos[i][j]]!='1') continue;
                adj[u].push_back(pos[i][j]);
                adj[pos[i][j]].push_back(u);
            }
        }
        return;
    }
    int prep[2][2];
    for(int i=0;i<=1;i++){
        for(int j=0;j<=1;j++) prep[i][j]=pos[i][j];
    }
    for(int x=0;x<=1;x++){
        for(int y=0;y<=1;y++){
            int v=nxt[u][x][y];sz[v]=sz[u]-1;
            update(u,x,y);dfs(v);
            for(int i=0;i<=1;i++){
                for(int j=0;j<=1;j++) pos[i][j]=prep[i][j];
            }
        }
    }
}
void dfs2(int u){
    vis[u]=true;
    if(sz[u]!=-1) mp[2*sz[u]]++;
    for(int v:adj[u]){
        if(!vis[v]) dfs2(v);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> m >> s;n=(int)s.length();s="#"+s;
    stack<pii> st;
    for(int i=1;i<=n;i++){
        if(s[i]=='4') st.push({i,0});
        else{
            int cur=i;
            while(!st.empty() && st.top().second==3){
                nxt[st.top().first][1][1]=cur;
                cur=st.top().first;st.pop();
            }
            if(!st.empty()){
                int x=st.top().second;st.top().second++;
                nxt[st.top().first][((x>>1)&1)][x&1]=cur;
            }
        }
    }
    sz[1]=m;
    pos[0][0]=pos[0][1]=pos[1][0]=pos[1][1]=-1;
    dfs(1);Max.push_back(-1);
    for(int i=1;i<=n;i++){
        if(!vis[i] && s[i]=='1'){
            mp.clear();v.clear();cnt++;dfs2(i);
            for(auto x:mp){
                if(x.second>=2) mp[x.first+1]+=x.second/2;
                if(x.second%2==1) v.push_back(x.first);
            }
            reverse(v.begin(),v.end());
            int ok=1;
            for(int i=0;i<min((int)v.size(),(int)Max.size());i++){
                if(v[i]>Max[i]){Max=v;ok=2;break;}
                else if(v[i]<Max[i]){ok=0;break;}
            }
            if(ok==1 && (int)Max.size()>(int)v.size()) Max=v;
        }
    }
    int ans=0;
    for(int x:Max) ans=(ans+power(2,x))%mod;
    cout << cnt << '\n' << ans << '\n';
}
