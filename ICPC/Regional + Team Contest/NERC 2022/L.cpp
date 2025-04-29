#include<bits/stdc++.h>
using namespace std;
#define maxn 200005
int n,m,s,trace[maxn],anc[maxn],t,x1,x2;
vector<int> edge[maxn];
void tracing(){
    vector<int> s1={t},s2={t};
    while(x1!=s){s1.push_back(x1);x1=trace[x1];}
    while(x2!=s){s2.push_back(x2);x2=trace[x2];}
    cout << (int)s1.size()+1 << '\n' << s << ' ';
    for(int i=(int)s1.size()-1;i>=0;i--) cout << s1[i] << " ";
    cout << '\n' << (int)s2.size()+1 << '\n' << s << ' ';
    for(int i=(int)s2.size()-1;i>=0;i--) cout << s2[i] << " ";
    return;
}
void bfs(){
    if((int)edge[s].size()==1){cout << "Impossible\n";return;}
    queue<int> q;
    for(int v:edge[s]){q.push(v);trace[v]=s;anc[v]=v;}
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:edge[u]){
            if(v==s) continue;
            if(trace[v]!=0){
                if(anc[v]==anc[u]) continue;
                t=v;x1=u;x2=trace[v];
                cout << "Possible\n";
                tracing();return;
            }
            else{trace[v]=u;anc[v]=anc[u];q.push(v);}
        }
    }
    cout << "Impossible\n";return;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> m >> s;
    for(int i=1;i<=m;i++){
        int u,v;cin >> u >> v;
        edge[u].push_back(v);
    }
    bfs();
}
