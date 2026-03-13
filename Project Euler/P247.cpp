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

#define ld long double
void solve(){
    vector<vector<int>> f(4,vector<int>(4,0));

    auto cal = [&](ld x,ld y){
        ld d = x;
        if(y>0) d-=1/y;
        ld s = (d/2)*(d/2)+1;
        ld k = sqrtl(s)+d/2;
        return k;
    };

    int N=1;
    vector<ld> l={1},r={-1};
    vector<int> a={0},b={0};
    f[0][0]=1;

    priority_queue<pair<ld,int>> pq;
    pq.push({cal(l[0],r[0])-1,0});

    int T=0,lst=-1;
    while(!pq.empty()){
        auto [dd,i]=pq.top();pq.pop();T++;
        if(a[i]<=3 && b[i]<=3) f[a[i]][b[i]]--;
        if(a[i]==3 && b[i]==3) lst=T;

        for(int j=0;j<2;j++){
            l.push_back(l[i]);
            r.push_back(r[i]);
            a.push_back(a[i]);
            b.push_back(b[i]);
        }

        ld k=l[i]+dd;

        a[N]++;
        b[N+1]++;
        l[N]=k;
        r[N+1]=k;
        
        pq.push({cal(l[N],r[N])-l[N],N});
        pq.push({cal(l[N+1],r[N+1])-l[N+1],N+1});

        if(a[N]<=3 && b[N]<=3) f[a[N]][b[N]]++;
        if(a[N+1]<=3 && b[N+1]<=3) f[a[N+1]][b[N+1]]++;

        N+=2;


        int cnt=0;
        for(int i=0;i<=3;i++) for(int j=0;j<=3;j++) cnt+=f[i][j];
        if(!cnt) break;
    }
    cout << lst << '\n';
}   
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
