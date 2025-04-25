#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
const int maxn = 1e6+5;
const int inf = 1e18;

int n,a,b,c,d,T,X,Y,L[maxn],pos[maxn];
vector<pii> edge[4*maxn];
int dist[4*maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    cin >> a >> b >> c >> d;
    vector<int> pre;
    for(int k=1;k<=n;k++){
        cin >> L[k];
        vector<int> cur={1};
        if(L[k]) cur.push_back(L[k]+1);
        if(b<=L[k] && 1<b) cur.push_back(b);
        if(d<=L[k] && 1<d && b!=d) cur.push_back(d);
        sort(cur.begin(),cur.end());
        int sz=(int)cur.size();
        for(int i=0;i<sz;i++){
            if(a==k && cur[i]==b) X=T+i;
            if(c==k && cur[i]==d) Y=T+i;
        }
        for(int i=0;i<sz-1;i++){
            edge[T+i].push_back({T+i+1,cur[i+1]-cur[i]});
            edge[T+i+1].push_back({T+i,cur[i+1]-cur[i]});
        }
        if(!pre.empty()){
            edge[T].push_back({T-1,1});
            edge[T-1].push_back({T,1});
            int psz=(int)pre.size();
            for(int i=0;i<sz;i++){
                if(cur[i]>pre.back()) edge[T+i].push_back({T-1,1});
                else{
                    for(int j=0;j<psz;j++){
                        if(pre[j]==cur[i]) edge[T+i].push_back({T-psz+j,1});
                        if(j<psz-1 && pre[j]<cur[i] && cur[i]<pre[j+1]){
                            edge[T+i].push_back({T-psz+j,cur[i]-pre[j]+1});
                            edge[T+i].push_back({T-psz+j+1,pre[j+1]-cur[i]+1});
                        }
                    }
                }
            }
            for(int i=0;i<psz;i++){
                if(pre[i]>cur.back()) edge[T-psz+i].push_back({T+sz-1,1});
                else{
                    for(int j=0;j<sz;j++){
                        if(pre[i]==cur[j]) edge[T-psz+i].push_back({T+j,1});
                        if(j<sz-1 && cur[j]<pre[i] && pre[i]<cur[j+1]){
                            edge[T-psz+i].push_back({T+j,pre[i]-cur[j]+1});
                            edge[T-psz+i].push_back({T+j+1,cur[j+1]-pre[i]+1});
                        }
                    }
                }
            }
        }
        pos[k]=T+sz-1;
        pre=cur;T+=sz;
    }
    vector<int> v;
    map<int,int> mp;
    for(int i=1;i<=n;i++){
        while(!v.empty() && L[v.back()]>L[i]) v.pop_back();
        int lt=(v.empty()?0:v.back());
        if(lt) edge[pos[i]].push_back({pos[lt],i-lt});
        if(mp.find(L[i]+1)!=mp.end()){
            int id=mp[L[i]+1];
            if(lt<id) edge[pos[i]].push_back({pos[id],i-id+1});
        }
        mp[L[i]]=i;
        v.push_back(i);
    }
    mp.clear();
    v.clear();
    for(int i=n;i>=1;i--){
        while(!v.empty() && L[v.back()]>L[i]) v.pop_back();
        int rt=(v.empty()?n+1:v.back());
        if(rt<=n) edge[pos[i]].push_back({pos[rt],rt-i});
        if(mp.find(L[i]+1)!=mp.end()){
            int id=mp[L[i]+1];
            if(id<rt) edge[pos[i]].push_back({pos[id],id-i+1});
        }
        mp[L[i]]=i;
        v.push_back(i);
    }

    for(int i=0;i<T;i++) dist[i]=inf;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    dist[X]=0;pq.push({0,X});
    while(!pq.empty()){
        auto [d,u]=pq.top();pq.pop();
        if(u==Y){
            cout << d << '\n';
            return 0;
        }
        if(d!=dist[u]) continue;
        for(auto [v,w]:edge[u]) if(d+w<dist[v]) pq.push({dist[v]=d+w,v});
    }
    cout << -1 << '\n';
}
