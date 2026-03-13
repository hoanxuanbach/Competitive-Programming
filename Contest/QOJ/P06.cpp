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
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    int X,Y;cin >> X >> Y;
    
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int x,int y){
        return a[x]<a[y];
    });

    int S=1;    
    vector<int> p(n+1);
    for(int i=0;i<n;i++) p[i+1]=p[i]+a[ord[i]];
    for(int i=0;i<n;i++){
        while(S<=i && a[ord[i]]*(S+1)*Y<=(p[i+1]-p[i-S])*X) S++;
    }
    vector<int> v;
    for(int i=0;i<n;i++){
        v.push_back(i);
        if(i+1<S) continue;
        while(!v.empty()){
            int x=v.back();
            int sum=p[i+1]-p[i-S+2];
            if(x>i-S) sum+=a[ord[i-S+1]];
            else sum+=a[ord[x]];
            if(a[ord[i]]*S*Y<=sum*X) v.pop_back();
            else break;
        }
    }
    for(int &x:v) x=ord[x];
    sort(v.begin(),v.end());
    cout << (int)v.size() << '\n';
    for(int x:v) cout << x << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
