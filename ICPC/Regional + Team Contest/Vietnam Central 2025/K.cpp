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

const int S = 6;
void solve(){
    int N;cin >> N;

    //vector<int> A(S*N);
    //for(int i=0;i<S*N;i++) cin >> A[i];

    vector<int> f(N);
    iota(f.begin(),f.end(),0);  

    auto ask = [&](int x){
        cout << "? " << x << endl;
        //return A[x-1];
        int val;cin >> val;
        return val;
    };

    vector<int> res(S);
    
    int K=720,p=0;
    while(p<6){

        vector<int> cnt(S+1),c((int)f.size());
        for(int i=0;i<(int)f.size();i++){
            c[i]=ask(f[i]*S+p+1);
            cnt[c[i]]++;
        }
        for(int i=0;i<p;i++) cnt[res[i]]=K/(S-p);
        for(int i=1;i<=S;i++){
            if(cnt[i]!=K/(S-p)){
                res[p]=i;
                break;
            }
        }
        
        vector<int> nf;
        for(int i=0;i<(int)f.size();i++) if(c[i]==res[p]) nf.push_back(f[i]);
        swap(f,nf);K/=(S-p);p++;

    }


    cout << "! ";
    for(int x:res) cout << x << ' ';
    cout << endl;
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}
