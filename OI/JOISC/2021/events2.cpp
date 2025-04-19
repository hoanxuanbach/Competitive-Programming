#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
#define fi first
#define se second
const int maxn=100005;
const int maxl=20;
int n,k,L[maxn],R[maxn],nxt[2*maxn][maxl];
set<pii> s;
int cal(int l,int r){
    int ans=0;
    for(int i=18;i>=0;i--){
        if(nxt[l][i]<=r){
            ans+=(1<<i);
            l=nxt[l][i];
        }
    }
    return ans;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> k;
    vector<int> p;
    for(int i=1;i<=n;i++){
        cin >> L[i] >> R[i];
        p.push_back(L[i]);p.push_back(R[i]);
    }
    sort(p.begin(),p.end());
    p.erase(unique(p.begin(),p.end()),p.end());
    for(int i=1;i<=n;i++){
        L[i]=lower_bound(p.begin(),p.end(),L[i])-p.begin()+1;
        R[i]=lower_bound(p.begin(),p.end(),R[i])-p.begin()+1;
    }
    int sz=(int)p.size();
    for(int i=1;i<=sz+1;i++) nxt[i][0]=sz+1;
    for(int i=1;i<=n;i++) nxt[L[i]][0]=min(nxt[L[i]][0],R[i]);
    for(int i=sz;i>=1;i--) nxt[i][0]=min(nxt[i][0],nxt[i+1][0]);
    for(int i=1;i<=18;i++){
        for(int j=1;j<=sz+1;j++) nxt[j][i]=nxt[nxt[j][i-1]][i-1];
    }
    s.insert({0,1});s.insert({sz,sz+1});
    int cur=cal(1,sz);
    if(cur<k){
        cout << -1 << '\n';
        return 0;
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        auto it=s.upper_bound(make_pair(L[i],R[i]));
        pii y=*it,x=*(--it);
        if(L[i]<x.se || R[i]>y.fi) continue;
        int add=cal(x.se,L[i])+cal(R[i],y.fi)+1-cal(x.se,y.fi);
        if(cur+add>=k){
            cur+=add;cnt++;
            s.insert({L[i],R[i]});
            cout << i << '\n';
        }
        if(cnt==k) break;
    }
}