#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+5;
set<int> s;
int cnt[maxn];

void add(int x,int val){
    cnt[x]+=val;
    if(!cnt[x]) s.erase(x);
    else s.insert(x);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    vector<pair<int,int>> p(n);
    for(int i=0;i<n;i++) cin >> p[i].first >> p[i].second;
    sort(p.begin(),p.end());
    int mx=0;
    for(auto [h,k]:p){
        mx=max(mx,h);
        auto it=s.upper_bound(h-k+1);
        int l=1,r=(it==s.end()?h:*it-1);
        if(it!=s.begin()){it--;l=*it;}
        if(r<h) add(r+1,1),add(h+1,-1),k-=(h-r);
        if(k) add(l,1),add(l+k,-1);
    }
    long long total=0;
    for(int i=1;i<=mx;i++){
        cnt[i]+=cnt[i-1];
        total+=1LL*cnt[i]*(cnt[i]-1)/2;
    }
    cout << total << '\n';
}
