#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+9;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 4e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){

    int N,K;cin >> N >> K;
    auto cal = [&](vector<array<int,3>> &X,int T){
        int cnt=0,ret=0;

        priority_queue<pii,vector<pii>,greater<pii>> pq;
        for(auto [x,t,w]:X){
            if(!t) pq.push({w-T,0});
            else{
                if(!pq.empty() && pq.top().first+w<0){
                    if(!pq.top().second) cnt++;
                    ret+=pq.top().first+w;
                    pq.pop();pq.push({-w,1});
                }
            }
        }
        return make_pair(cnt,ret);
    };

    vector<array<int,3>> X,Y;
    for(int i=1;i<=N;i++){
        int t,x,y,w;cin >> t >> x >> y >> w;
        if(t<=2) X.push_back({x,2-t,w});
        else Y.push_back({y,4-t,w});
    }
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());

    int l=0,r=2e9,res=-1;
    while(l<=r){
        int mid=(l+r)>>1;
        auto [kx,dx]=cal(X,mid);
        auto [ky,dy]=cal(Y,mid);
        if(kx+ky>=K) res=dx+dy+K*mid,r=mid-1;
        else l=mid+1;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
