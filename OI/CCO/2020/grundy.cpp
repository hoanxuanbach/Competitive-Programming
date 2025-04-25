#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int N,L,R,Y;cin >> N >> L >> R >> Y;
    vector<int> cnt(N+1);
    map<int,int> mp;
    for(int i=1;i<=N;i++){
        int x,v,h;cin >> x >> v >> h;
        int d=(h*Y-1)/v,l=x-d,r=x+d;
        l=max(l,L);r=min(r,R);
        if(l>r) continue;
        mp[l]++,mp[r+1]--;
        //cout << l << ' ' << r << '\n';
    }
    int cur=0,pos=L;
    for(auto [x,val]:mp){
        cnt[cur]+=x-pos;
        cur+=val,pos=x;
    }
    cnt[cur]+=R+1-pos;
    for(int i=1;i<=N;i++) cnt[i]+=cnt[i-1];
    for(int i=0;i<=N;i++) cout << cnt[i] << '\n';
}
