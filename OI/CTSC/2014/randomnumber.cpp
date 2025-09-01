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

const int root=3;
const int iroot=power(3,mod-2);
void fft(vector<int> &a,bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit){j^=bit;bit>>=1;}
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        int wn=power((invert?iroot:root),(mod-1)/len);
        for(int i=0;i<n;i+=len){
            int w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j],v=a[i+j+len/2]*w%mod;
                a[i+j]=(u+v)%mod;
                a[i+j+len/2]=(u-v+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(invert){
        int dd=power(n,mod-2);
        for(int i=0;i<n;i++) a[i]=a[i]*dd%mod;
    }
    return;
}
 
vector<int> mul(vector<int> a,vector<int> b){
    int n=(int)a.size()+(int)b.size(),sz=1;
    while(sz<n) sz<<=1;
    a.resize(sz);b.resize(sz);
    fft(a,false);fft(b,false);
    for(int i=0;i<sz;i++) a[i]=a[i]*b[i]%mod;
    fft(a,true);
    for(int i=0;i<sz;i++) a[i]&=1;
    return a;
}

vector<int> get_inv(vector<int> &F){
    int N=(int)F.size();
    vector<int> G={1};

    int n=1;
    while(n<N){
        vector<int> f(2*n),g(2*n);
        for(int i=0;i<min(N,2*n);i++) f[i]=F[i];
        for(int i=0;i<n;i++) g[i]=G[i];
        fft(f,false);
        fft(g,false);
        for(int i=0;i<2*n;i++) f[i]=f[i]*g[i]%mod;
        fft(f,true);
        for(int i=0;i<2*n;i++) f[i]&=1;
        for(int i=0;i<n;i++) f[i]=0;
        fft(f,false);
        for(int i=0;i<2*n;i++) f[i]=f[i]*g[i]%mod;
        fft(f,true);
        for(int i=n;i<2*n;i++) G.push_back(f[i]&1);
        n<<=1;
    }
    G.resize(N);
    return G;
}

pair<vector<int>,vector<int>> divmod(vector<int> a,vector<int> b){
    int n=(int)a.size(),m=(int)b.size();
    if(n<m) return {{},a};
    vector<int> fa=a,fb=b;
    reverse(fa.begin(),fa.end());
    reverse(fb.begin(),fb.end());
    int d=n-m+1;
    fa.resize(d);fb.resize(d);
    fb=get_inv(fb);
    fa=mul(fa,fb);
    fa.resize(d);
    reverse(fa.begin(),fa.end());
    fb=mul(fa,b);
    for(int i=0;i<n;i++) a[i]^=fb[i];
    while(!a.empty() && a.back()>0) a.pop_back();
    return {fa,a};
}

const int M=1005;

void solve(){
    int n;cin >> n;
    vector<int> X(n,0),S(n,0);
    for(int i=0;i<n;i++) cin >> X[i];
    for(int i=0;i<n;i++) cin >> S[i];
    int T=0;cin >> T;
    if(T==0){
        int k;cin >> k;
        if(n<=2000){
            auto cal = [&](vector<int> &x,vector<int> &y){
                int nx=(int)x.size(),ny=(int)y.size(),ns=nx+ny-1;
                vector<int> a(ns);
                for(int i=0;i<nx;i++) for(int j=0;j<ny;j++) a[i+j]^=(x[i]&y[j]);
                for(int i=ns-1;i>=n;i--){
                    if(a[i]) for(int j=0;j<n;j++) a[i-n+j]^=X[j];
                }
                if(ns>n) a.resize(n);
                return a;
            };  

            vector<int> Y={0,1};
            while(k){
                if(k&1) S=cal(S,Y);
                Y=cal(Y,Y);k>>=1;
            }
            for(int i=0;i<n;i++) cout << S[i];
            cout << '\n';
        }
        else{
            reverse(S.begin(),S.end());
            for(int i=0;i<k;i++) S.push_back(0);
            reverse(S.begin(),S.end());            
            X.push_back(1);
            auto res=divmod(S,X).second;
            for(int i=0;i<n;i++) cout << res[i];
            cout << '\n';
        }
    }
    else{
        int L;cin >> L;
        vector<int> V(n);
        for(int i=0;i<n;i++) cin >> V[i];

        vector<bitset<M>> G(2*n);
        auto gauss = [&](){
            for(int i=2*n-1;i>=n;i--) for(int j=0;j<n;j++) if(X[j]) G[i-n+j]^=G[i];
            for(int i=0;i<n;i++) G[i][n]=V[i];
            for(int k=0;k<n;k++){
                int i=k;
                while(i<n && !G[i][k]) i++;
                assert(i<n);
                for(int j=i+1;j<n;j++) if(G[j][k]) G[j]^=G[i];
                if(i!=k) swap(G[k],G[i]);
            }
            
            for(int i=0;i<n;i++) V[i]=G[i][n];
            for(int i=n-1;i>=0;i--){
                for(int j=i+1;j<n;j++) if(G[i][j]) V[i]^=V[j];
            }
        };
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) if(S[j]) G[i+j][i]=1;
        gauss();

        while(L--){
            for(int i=0;i<2*n;i++) G[i].reset();
            for(int i=0;i<n;i++) G[2*i][i]=1;
            gauss();
        }
        vector<int> res(2*n);
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) res[i+j]^=(V[i]&S[j]);
        for(int i=2*n-1;i>=n;i--) for(int j=0;j<n;j++) if(X[j]) res[i-n+j]^=res[i];
        for(int i=0;i<n;i++) cout << res[i];
        cout << '\n';
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
