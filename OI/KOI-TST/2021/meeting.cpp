#include "meeting.h"
#include<bits/stdc++.h>
using namespace std;

using i32 = int;
#define int long long
#define pii pair<int,int>
#define piii pair<pii,int>
#define fi first
#define se second
const int maxn = 5005;
const int inf = 1e18;
int dp[maxn];
vector<pii> lt[maxn],rt[maxn];

int min_charge(i32 K,vector<i32> S,vector<i32> E,vector<i32> W){
    int N=(int)S.size();
    vector<int> com;
    for(int i=0;i<N;i++){
        com.push_back(S[i]);
        com.push_back(E[i]+1);
    }
    sort(com.begin(),com.end());
    com.erase(unique(com.begin(),com.end()),com.end());
    for(int i=0;i<N;i++){
        S[i]=lower_bound(com.begin(),com.end(),S[i])-com.begin()+1;
        E[i]=lower_bound(com.begin(),com.end(),E[i]+1)-com.begin();
        lt[S[i]].push_back({E[i],W[i]});
        rt[E[i]].push_back({S[i],W[i]});
    }
    int sz=(int)com.size();
    for(int i=1;i<=sz;i++){
        int total=0,sum=0;
        priority_queue<int,vector<int>,greater<int>> pq;
        dp[i]=inf;
        for(int j=i;j>=1;j--){
            for(auto [x,val]:rt[j]) total+=val;
            for(auto [x,val]:lt[j]){
                if(x<=i){
                    sum+=val;
                    pq.push(val);
                    if((int)pq.size()>K) sum-=pq.top(),pq.pop();
                }
            }
            dp[i]=min(dp[i],dp[j-1]+total-sum);
        }
    }
    return dp[sz];
}

#undef int
/*
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int N,K;cin >> N >> K;
    vector<int> S(N),E(N),W(N);
    for(int i=0;i<N;i++) cin >> S[i] >> E[i] >> W[i];
    cout << min_charge(K,S,E,W) << '\n';
}
*/
