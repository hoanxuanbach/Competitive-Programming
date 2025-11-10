#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

void solve(){
    int N;cin >> N;
    
    int L=0;
    while((1<<2*L)<=N) L++;

    auto cal = [&](int x,int y){
        int val=0;
        for(int i=0;i<L;i++) if(x>>i&1) val^=(y<<i);
        return val;
    };
    auto get = [&](int x){
        int cur=0;
        for(int i=0;i<L;i++) cur|=(x>>i&1)<<(2*i+1);
        
        int res=0;
        bool ok=false;
        for(int i=2*L-1;i>=0;i--){
            int a=(N>>i&1),b=(cur>>i&1);
            if(i&1){
                if(a>b) ok=true;
                else if(a<b){
                    if(!ok) return res-1;
                }
            }
            else{
                if(ok) res+=(1<<(i/2));
                else res+=(a<<(i/2));
            }
        }
        return res;
    };

    vector<vector<array<int,3>>> f(4*N);
    for(int x=0;x<(1<<L);x++) for(int y=0;y<(1<<L);y++){
        int d=cal(x,y);
        f[d<<1].push_back({x,y,1});
        f[d].push_back({x,y,0});
    }
    cout << "start" << endl;
    int res=0;
    for(int i=0;i<4*N;i++){
        if(i%100000==0) cout << i/100000 << endl; 
        if(!f[i].empty()){
        
            vector<pii> A,B;
            for(auto [x,y,t]:f[i]){
                if(!t) A.push_back({x,y+1});
                else{
                    x=get(x);
                    y=get(y);
                    B.push_back({x,y+1});
                }
            }
            sort(A.begin(),A.end());
            sort(B.begin(),B.end());
            
            vector<int> bit((1<<L)+1);
            auto update = [&](int x){
                for(int i=x;i<=(1<<L);i+=(i&(-i))) bit[i]++;
            };
            auto query = [&](int x){
                int val=0;
                for(int i=x;i>=1;i-=(i&(-i))) val+=bit[i];
                return val;
            };
            int pos=0;
            for(auto [x,y]:B){
                while(pos<(int)A.size() && A[pos].first<=x) update(A[pos++].second);
                res+=query(y);
            }
        }
    }
    cout << (res+1)/2 << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
