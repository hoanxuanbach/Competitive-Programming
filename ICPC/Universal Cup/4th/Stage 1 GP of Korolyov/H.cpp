#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int inf = 1e9;

void solve(){
    int n,m,k;cin >> n >> m >> k;
    
    vector<vector<int>> a(n,vector<int>(k,0));
    for(int i=0;i<k;i++) for(int j=0;j<n;j++) cin >> a[j][i];
    
    int res=0;
    vector<int> p(n);
    
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<n;i++){
        sort(a[i].begin(),a[i].end());
        for(int j=0;j<k;j++) res+=a[i][j];
        pq.push({k,i});
    }


    while(m){
        auto [d,i]=pq.top();pq.pop();

        int cnt=0;
        if(!p[i]) cnt=a[i][0];
        else if(p[i]<k) cnt=a[i][p[i]]-a[i][p[i]-1];
        else cnt=inf;

        int t=min(m,cnt);
        m-=t;res-=d*t;
        
        p[i]++;
        pq.push({d-2,i});
    }
    cout << res/2 << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}