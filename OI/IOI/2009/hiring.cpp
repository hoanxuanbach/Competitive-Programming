#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 5e5+5;
int N,S[maxn],Q[maxn],W;
int sum;
priority_queue<int> pq;

signed main(){
    cin >> N >> W;
    for(int i=1;i<=N;i++) cin >> S[i] >> Q[i];
    vector<int> ord(N);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return S[x]*Q[y]<S[y]*Q[x];
    });
    pair<pair<int,long double>,int> Max={{-1,-1},-1};
    for(int x:ord){
        int mx=(W*Q[x])/S[x];
        pq.push(Q[x]);sum+=Q[x];
        while(sum>mx) sum-=pq.top(),pq.pop();
        Max=max(Max,{{(int)pq.size(),-(long double)sum*S[x]/Q[x]},x});
    }
    cout << Max.first.first << '\n';
    int a=Max.second;
    vector<int> cur;
    for(int x:ord){
        cur.push_back(x);
        if(x==a) break;
    }
    W=(W*Q[a])/S[a];
    sort(cur.begin(),cur.end(),[&](int x,int y){
        return Q[x]<Q[y];
    });
    for(int x:cur){
        W-=Q[x];
        if(W<0) break;
        cout << x << '\n';
    }
}
