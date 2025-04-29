#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int>
#define maxn 200005
struct query{
    int a,b,t;
    bool operator<(query o){return a<o.a;}
};
query x[maxn];
int n,Min[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++) cin >> x[i].a >> x[i].b >> x[i].t;
    sort(x+1,x+n+1);Min[n+1]=LLONG_MAX;x[n+1].a=1e18;
    for(int i=n;i>=1;i--) Min[i]=min(Min[i+1],x[i].a+x[i].t);
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    int cur=0,id=1,nxt=0,ans=0;
    while(true){
        //cout << ans << ' ' << cur << '\n';
        while(!pq.empty() && cur+pq.top().first>pq.top().second) pq.pop();
        if(!pq.empty()) nxt=cur+pq.top().first;
        else nxt=LLONG_MAX;
        int add=1;
        if(nxt<Min[id] && !pq.empty()){
            int p=min(pq.top().second,Min[id]);
            //cout << cur << ' ' << p << '\n';
            nxt+=(p-nxt)/pq.top().first*pq.top().first;
            add=(p-cur)/pq.top().first;
        }
        else nxt=Min[id];
        if(nxt==LLONG_MAX) break;
        while(id<=n && nxt>=x[id].a){pq.push({x[id].t,x[id].b});id++;}
        ans+=add;cur=nxt;
    }
    cout << ans << '\n';
}
