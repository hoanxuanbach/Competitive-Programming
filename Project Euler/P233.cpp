#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a;
        a=a*a;n>>=1;
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

    int S=N/(5*5*5*13*13);

    vector<int> p(S+1);
    for(int i=2;i<=S;i++) if(!p[i]) for(int j=i;j<=S;j+=i) p[j]=i;

    vector<int> g(S+1),h(S+1),X;
    for(int i=1;i<=S;i++){
        if(i==p[i] && i%4==1) X.push_back(i);
        int x=i,d=0;g[i]=i;
        while(x%2==0) x/=2;
        while(x>1){
            int k=p[x];
            if(k%4==1) g[i]=0;
            while(x%k==0){
                x/=k;
                if(k%4==1) d++;
            }
        }
        g[i]+=g[i-1];
        if(d==1) h[i]=i;
        h[i]+=h[i-1];
    }

    int cnt=0;
    for(int x:X){
        if(x*x*x>N) break;
        for(int y:X){
            if(x==y) continue;
            if(x*x*x*y*y>N) break;
            int k=N/(x*x*x*y*y);
            cnt+=(h[k]-g[k/x]*x-g[k/y]*y)*x*x*x*y*y;
        }
    }
    for(int x:X){
        int xx=power(x,10);
        if(xx>N) break;
        for(int y:X){
            if(x==y) continue;
            if(xx*y*y>N) break;
            cnt+=g[N/(xx*y*y)]*xx*y*y;
        }
    }
    for(int x:X){
        int xx=power(x,7);
        if(xx>N) break;
        for(int y:X){
            if(x==y) continue;
            if(xx*y*y*y>N) break;
            cnt+=g[N/(xx*y*y*y)]*xx*y*y*y;
        }
    }
    cout << cnt << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
