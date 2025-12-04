#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e9+7;
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

const int L=30;
struct Trie{
    vector<int> cnt;
    vector<array<int,2>> nxt;
    Trie(){
        cnt.push_back(0);
        nxt.push_back({0,0});
    }
    void add(int x){
        int u=0;
        for(int i=0;i<L;i++){
            int t=(x>>i&1);
            if(!nxt[u][t]){
                nxt[u][t]=(int)nxt.size();
                cnt.push_back(0);
                nxt.push_back({0,0});
            }
            u=nxt[u][t];
            cnt[u]++;
        }
    }
};

void solve(){
    int n,m;cin >> n >> m;
    vector<int> a(n),b(m);
    for(int i=0;i<n;i++) cin >> a[i];
    for(int i=0;i<m;i++) cin >> b[i];

    int res=0;
    vector<Trie> T(2);
    for(int i=0;i+1<m;i++) if((b[i]^b[i+1])==1) T[b[i]&1].add(b[i]/2);
    for(int i=0;i+1<n;i++) if((a[i]&1)==(a[i+1]&1)){
        int k=a[i]&1;
        int x=a[i]/2,y=a[i+1]/2,d=x^y;
        if(!d) continue;


        x&=d;y&=d;x^=(d>>1);
        
        int u=0;
        for(int j=0;j<L;j++){
            if(!(d&1)) break;
            int t=(x>>j&1);d>>=1;
            u=T[k].nxt[u][t];
            if(!u) break;
        }
        if(!d) res+=T[k].cnt[u];
    }

    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}