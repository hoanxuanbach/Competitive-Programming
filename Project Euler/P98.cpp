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
    string SS;cin >> SS;
    vector<string> S;
    string cur;
    for(char c:SS){
        if(c>='A' && c<='Z') cur+=c;
        else{
            if(!cur.empty()) S.push_back(cur);
            cur.clear();
        }
    }
    if(!cur.empty()) S.push_back(cur);
    
    /*
    vector<int> cnt(15);
    for(string x:S) cnt[(int)x.size()]++;
    for(int i=1;i<=14;i++) cout << cnt[i] << '\n';
    */
    int N=(int)S.size();
    vector<string> T(N);
    for(int i=0;i<N;i++){
        T[i]=S[i];
        sort(T[i].begin(),T[i].end());
        //T[i].erase(unique(T[i].begin(),T[i].end()),T[i].end());
    }
    int res=0;
    vector<int> f(256,-1);
    vector<int> g(256,-1);
    auto add = [&](string X,string Y){
        int d=(int)X.size(),val=1;
        for(int i=1;i<d;i++) val*=10;
        for(int x=1;x*x<10*val;x++){
            if(x*x<val) continue;
            string A=to_string(x*x);

            bool check=true;
            for(int i=0;i<d;i++){
                if(f[X[i]]!=-1 && f[X[i]]!=(A[i]-'0')) check=false;
                if(g[A[i]]!=-1 && g[A[i]]!=(X[i]-'A')) check=false;
                f[X[i]]=(A[i]-'0');
                g[A[i]]=(X[i]-'A');
            }

            int y=0;
            for(int i=0;i<d;i++) y=y*10+f[Y[i]];
            if(!f[Y[0]]) check=false;
            int s=sqrtl(y);
            if(s*s!=y) check=false;
            if(check){
                int cur=max(x,s);
                if(cur>res){
                    res=cur;
                    cout << X << ' ' << Y << ' ' << x*x << ' ' << s*s << '\n';
                }
            }
            for(int i=0;i<d;i++) f[X[i]]=-1,g[A[i]]=-1;
        }   
    };
    for(int i=0;i<N;i++) for(int j=i+1;j<N;j++){
        if(T[i]!=T[j]) continue;
        add(S[i],S[j]);
    }
    cout << res << '\n';
}
 
signed main(){
    freopen("98.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
