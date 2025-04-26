#include<bits/stdc++.h>
using namespace std;
const int maxn=2000005;
void solve(){
    int n,cur=1,ans=0,ok=0;cin >> n;
    priority_queue<int> pq;
    for(int i=1;i<=n;i++){
        int a;cin >> a;pq.push(a);
        while(!pq.empty() && cur<i+(i!=n)){cur+=pq.top()-1;ans++;pq.pop();}
        if(cur<i+(i!=n)) ok=1;
    }
    cout << (ok?-1:ans) << '\n';
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
