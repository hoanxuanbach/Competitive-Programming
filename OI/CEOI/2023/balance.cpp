#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
const int maxS = 1e6+5;
#define pii pair<int,int>
#define fi first
#define se second;

int n,s,t;
int deg[maxn];
vector<pii> edge[maxn];
int d[maxS];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> s >> t;
    vector<vector<int>> a(n,vector<int>(s,0));
    for(int i=0;i<n;i++) for(int j=0;j<s;j++) cin >> a[i][j];
    function<void(int,int)> dnc = [&](int l,int r){
        if(l+1==r) return;
        int m=(l+r)>>1,S=m-l,T=0;

        function<void(int)> dfs = [&](int x){
            while(deg[x]){
                auto [y,id]=edge[x].back();
                edge[x].pop_back();deg[x]--;
                if(d[abs(id)]!=-1) continue;
                d[abs(id)]=(id<0);dfs(y);
            }
        };
        vector<int> cc;
        for(int i=0;i<n;i++){
            for(int j=0;j<S;j++){
                int x=a[i][l+j],y=a[i][m+j];
                if(!deg[x]) cc.push_back(x);
                deg[x]++;
                if(!deg[y]) cc.push_back(y);
                deg[y]++;T++;
                edge[x].push_back({y,T});
                edge[y].push_back({x,-T});
            }
        }
        vector<int> cur;
        for(int x:cc) if(deg[x]&1) cur.push_back(x);
        for(int i=0;i<(int)cur.size();i+=2){
            int x=cur[i],y=cur[i+1];
            deg[x]++;deg[y]++;T++;
            edge[x].push_back({y,T});
            edge[y].push_back({x,-T});
        }
        for(int i=1;i<=T;i++) d[i]=-1;
        for(int x:cc) if(deg[x]) dfs(x);
        for(int x=1;x<=n*S;x++){
            int i=(x-1)/S,j=(x-1)%S;
            if(d[x]) swap(a[i][l+j],a[i][m+j]);
        }
        for(int x:cc) deg[x]=0,edge[x].clear();
        dnc(l,m);dnc(m,r);
    };
    dnc(0,s);
    for(int i=0;i<n;i++){
        for(int j=0;j<s;j++) cout << a[i][j] << ' ';
        cout << '\n';
    }
}
