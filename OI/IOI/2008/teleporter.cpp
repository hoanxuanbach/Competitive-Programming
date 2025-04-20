#include<bits/stdc++.h>
using namespace std;
const int maxa = 2e6;
const int maxn = 1e6+5;
int f[maxa+5],nxt[maxa+5],res=0;
bool vis[maxa+5];

 signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,m;cin >> n >> m;
    vector<pair<int,int>> p(n);
    for(int i=0;i<n;i++){
        int x,y;cin >> x >> y;
        f[x]++,f[y]++;
        p[i]={x,y};
    }
    for(int i=1;i<=maxa;i++) f[i]+=f[i-1];
    for(auto [x,y]:p){
        x=f[x],y=f[y];
        nxt[x-1]=y;
        nxt[y-1]=x;
    }
    int N=2*n;
    vector<int> S;
    for(int i=0;i<=N;i++){
        if(!vis[i]){
            int u=i,cnt=0;
            while(!vis[u]) vis[u]=true,cnt++,u=nxt[u];
            if(!i) res+=cnt-1;
            else S.push_back(cnt);
        }
    }
    sort(S.begin(),S.end(),greater<int>());
    for(int x:S){if(m) res+=x+2,m--;}
    for(int i=0;i<m;i++) res+=(i&1)<<1|1;
    cout << res << '\n';
 }

