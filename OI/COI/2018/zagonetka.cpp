#include<bits/stdc++.h>
using namespace std;
#define maxn 105
#define pii pair<int,int>
int n,p[maxn],deg[maxn],Min[maxn],Max[maxn],cnt,rev_deg[maxn],t[maxn],sz;
vector<int> edge[maxn],rev_edge[maxn];
pii a[maxn];
int query(){
    cout << "query ";
    for(int i=1;i<=n;i++) cout << t[i] << ' ';
    cout << endl;
    int y;cin >> y;
    return y;
}
bool topo(int u,int l,int r){
    t[u]=-1;
    for(int v:edge[u]){
        if(t[v]==-1) return false;
        if(p[v]<l || p[v]>r || t[v]) continue;
        if(!topo(v,l,r)) return false;
    }
    t[u]=sz--;
    //cout << u << ' ' << t[u] << '\n';
    return true;
}
bool check(int l,int r){
    //cout << "*" << l << ' ' << r << '\n';
    sz=r;
    for(int i=1;i<=n;i++){
        if(p[i]<l || p[i]>r) t[i]=p[i];
        else t[i]=0;
    }
    bool c=true;
    for(int i=l;i<=r;i++){
        //cout << sz << '\n';
        if(!t[a[i].second]){
            if(!topo(a[i].second,l,r)) c=false;
        }
    }
    if(!c) return true;
    if(!query()) return true;
    else return false;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){cin >> p[i];a[i]={p[i],i};}
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n-i;j++){
            int f1=a[j].second,f2=a[j+i].second;sz=0;
            edge[f2].push_back(f1);
            if(check(j,j+i)){
                edge[f1].push_back(f2);deg[f2]++;
                //cout << f1 << ' ' << f2 << '\n';
            }
            edge[f2].pop_back();
        }
    }
    cout << "end" << endl;
    priority_queue<int> pq;
    for(int i=1;i<=n;i++){
        if(deg[i]==0) pq.push(i);
    }
    while(!pq.empty()){
        int u=pq.top();pq.pop();
        Max[u]=++cnt;
        for(int v:edge[u]){
            deg[v]--;
            if(deg[v]==0) pq.push(v);
        }
    }
    for(int i=1;i<=n;i++){
        for(int v:edge[i]){rev_edge[v].push_back(i);rev_deg[i]++;}
    }
    for(int i=1;i<=n;i++){
        if(rev_deg[i]==0) pq.push(i);
    }
    while(!pq.empty()){
        int u=pq.top();pq.pop();
        Min[u]=cnt--;
        for(int v:rev_edge[u]){
            rev_deg[v]--;
            if(rev_deg[v]==0) pq.push(v);
        }
    }
    for(int i=1;i<=n;i++) cout << Min[i] << ' ';
    cout << endl;
    for(int i=1;i<=n;i++) cout << Max[i] << ' ';
    cout << endl;
}
