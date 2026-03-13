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
    
    vector<array<int,4>> S;
    {//Generate

        auto get_max = [&](int T){
            T=(2*N*N)/T;
            if(T<=0) return -1LL;
            T=sqrtl(2*T-1);
            return (T-1)/2;
        };
        auto div = [&](int a,int b){
            return (a-1)/b+1;
        };
        auto get_min = [&](int x,int y){
            //cout << "get " << x << ' ' << y << '\n';
            int k=0,a=x+y,b=x-y;
            for(int u=0;u<x;u++){
                int v=(u*y)/x+1;
                int C=u*u+v*v-u*a+v*b;
                int D=v*x-u*y;
                //cout << C << ' ' << D << ' ' << div(-C,2*D) << '\n';
                k=max(k,div(-C,2*D));
            }
            return k;
        };
        int y=1;
        while(true){
            //cout << '*' << y << ' ' << get_min(1,y) << ' ' << get_max(1+y*y) << '\n';
            int r=get_max(1+y*y);
            int l=get_min(1,y);
            if(l>r) break;
            S.push_back({1,y,l,r});
            for(int x=3;x<y;x+=2){
                if(__gcd(x,y)!=1) continue;
                r=get_max(x*x+y*y);
                if(r<0) break;
                l=get_min(x,y);
                if(l<=r) S.push_back({x,y,l,r});
            }
            y+=2;
        }
    }

    int res=0;
    map<int,vector<int>> mp;
    for(int i=0;i<(int)S.size();i++){
        auto [x,y,l,r]=S[i];
        int s=(r-l+1);
        res+=s*(s+1)/2;
        for(int k=l;k<=r;k++){
            int d=((x*x+y*y)/2)*(2*k*k+2*k+1);
            mp[d].push_back(i);
        }
    }
    map<vector<int>,int> F;
    for(auto [d,v]:mp){
        vector<int> cur;
        function<void(int)> dfs = [&](int i){
            if(i==(int)v.size()){
                if((int)cur.size()>1) F[cur]++;
                return;
            }
            dfs(i+1);
            cur.push_back(v[i]);
            dfs(i+1);
            cur.pop_back();
        };
        dfs(0);
    }
    for(auto [v,d]:F){
        if((int)v.size()&1) res+=d*(d+1)/2;
        else res-=d*(d+1)/2;
    } 
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
