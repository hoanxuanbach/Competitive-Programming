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
    int n,m;cin >> n >> m;
    if(!m){
        for(int i=0;i<n;i++) cout << i+1 << ' ';
        cout << '\n';
        return;
    }
    vector<vector<int>> S(m),C(n,vector<int>(n,-1));

    int id=0;
    for(int i=0;i<m;i++){
        int k;cin >> k;
        S[i].assign(k,0);
        for(int j=0;j<k;j++) cin >> S[i][j],S[i][j]--;
        for(int u:S[i]) for(int v:S[i]) C[u][v]=i;
        if(k>(int)S[id].size()) id=i;
    }
    int T=(int)S[id].size();
    if((T+1)/2>n-T){
        cout << -1 << '\n';
        return;
    }
    vector<int> Y(n),b(n);
    iota(Y.begin(),Y.end(),0);
    vector<int> X=S[id];
    for(int u:X) Y.erase(find(Y.begin(),Y.end(),u));
    shuffle(X.begin(),X.end(),rng);
    shuffle(Y.begin(),Y.end(),rng);
    for(int i=0;i<n;i++){
        if(!Y.empty() && (X.empty() || i%3==2)){
            b[i]=Y.back();
            Y.pop_back();
        }
        else{
            b[i]=X.back();
            X.pop_back();
        }
    }
    auto calc = [&](int i){
        i=(i+n)%n;
        return (C[b[i]][b[(i+1)%n]]!=-1 && C[b[i]][b[(i+1)%n]]==C[b[i]][b[(i+n-1)%n]]);
    };

    int cnt=0;
    for(int i=0;i<n;i++) cnt+=calc(i);
    while(cnt){
        int x=rand_int(0,n-1),y=rand_int(0,n-1);
        if(x==y) continue;
        int nxt=cnt;
        nxt-=calc(x)+calc(x-1)+calc(x+1)+calc(y)+calc(y-1)+calc(y+1);
        swap(b[x],b[y]);
        nxt+=calc(x)+calc(x-1)+calc(x+1)+calc(y)+calc(y-1)+calc(y+1);
        if(nxt<=cnt) cnt=nxt;
        else swap(b[x],b[y]);
    }
    for(int i=0;i<n;i++) cout << b[i]+1 << ' ';
    cout << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
