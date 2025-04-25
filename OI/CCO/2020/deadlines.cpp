#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+5;

int n,bit[maxn];
vector<int> pos[maxn];
void update(int x){
    for(int i=x;i<=n;i+=(i&(-i))) bit[i]++;
}
int query(int x){
    int res=0;
    for(int i=x;i>=1;i-=(i&(-i))) res+=bit[i];
    return res;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){int x;cin >> x;pos[x].push_back(i);}
    priority_queue<int> pq;
    int cnt=0;
    for(int i=n;i>=1;i--){
        for(int x:pos[i]) pq.push(x);
        if(pq.empty()){
            cout << -1 << '\n';
            return 0;
        }
        int a=pq.top();pq.pop();
        cnt+=query(a);update(a);
    }
    cout << cnt << '\n';
}
