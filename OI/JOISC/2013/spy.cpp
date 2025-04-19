#include<bits/stdc++.h>
using namespace std;
#define maxn 2005
#define maxa 500005
int n,m;
vector<int> edge1[maxn],edge2[maxn];
bitset<maxa> ans2[maxn],ans1[maxn];
void dfs1(int u){
    for(int v:edge1[u]){
        ans1[v]|=ans1[u];
        dfs1(v);
    }
}
void dfs2(int u){
    for(int v:edge2[u]){
        ans2[v]|=ans2[u];
        dfs2(v);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int p1,p2;cin >> p1 >> p2;
        edge1[p1].push_back(i);
        edge2[p2].push_back(i);
    }
    for(int i=0;i<m;i++){
        int p1,p2;cin >> p1 >> p2;
        ans1[p1][i]=1;ans2[p2][i]=1;
    }
    dfs1(0);dfs2(0);
    for(int i=1;i<=n;i++){
        ans1[i]&=ans2[i];
        cout << ans1[i].count() << '\n';
    }
}
