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
    int n;cin >> n;
    vector<int> p(n+1);

    auto ask = [&](int x,int y,int z){
        cout << "? " << 1 << ' ' << x << ' ' << y << ' ' << z << endl;
        int a;cin >> a;return a;
    };
    auto get = [&](int x,int y){
        cout << "? " << 2 << ' ' << x << ' ' << y << endl;
        int a;cin >> a;return a;
    };

    vector<pii> S={{ask(1,2,3),4},{ask(1,2,4),3},{ask(2,3,4),1},{ask(1,3,4),2}};
    sort(S.begin(),S.end());

    int X=S[0].first,Y=S[2].first;
    int a=S[2].second,b=S[3].second,c=S[0].second,d=S[1].second;

    for(int i=5;i<=n;i++){
        int T=ask(a,c,i);
        if(X<T && T<Y) p[i]=T;
        else if(T==X) p[a]=X,a=i,X=ask(a,b,c);
        else if(T==Y) p[c]=Y,c=i,Y=ask(b,c,d);
        else if(T<X) p[b]=X,b=i,X=T;
        else p[d]=Y,d=i,Y=T;
    }
    
    if(get(a,b)==b) swap(a,b);
    if(get(c,d)==d) swap(c,d);
    p[a]=1,p[b]=2,p[c]=n-1,p[d]=n; 

    cout << "! ";
    for(int i=1;i<=n;i++) cout << p[i] << ' ';
    cout << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
