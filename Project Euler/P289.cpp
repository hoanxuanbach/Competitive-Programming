#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 1e10;
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

vector<int> connections = {
    1111,
    1114,
    1133,
    1134,
    1131,
    1211,
    1214,
    1221,
    1222,
    1224,
    1231,
    1232,
    1233,
    1234
};



void solve(){
    int n,m;cin >> n >> m;

    vector<vector<int>> link;
    for(int X:connections){
        vector<int> T={X/1000,X/100,X/10,X};
        for(int &d:T) d%=10;
        link.push_back(T);
    }

    map<int,int> f;

    for(int i=0;i<(1<<(n-1));i++){
        int X=0;
        for(int j=0;j<n-1;j++) X+=((j<<1)|(i>>j&1))<<(4*j);
        f[X]++;
    }

    auto transform = [&](int s,int a,int b){
        for(int i=0;i<n;i++) if((s>>(4*i)&15)==a) s^=(a^b)<<(4*i);
        return s;
    };
    auto compress = [&](int s,int sz){
        int T=0,ss=0;
        vector<int> h(n+2,-1);
        for(int i=0;i<sz;i++){
            int k=(s>>(4*i))&15;
            int kk=k>>1;
            if(h[kk]==-1) h[kk]=T++;
            ss+=(h[kk]<<1|(k&1))<<(4*i);
        }
        return ss;
    };
    auto cnt = [&](int s,int sz,int d){
        for(int i=0;i<sz;i++){
            int k=(s>>(4*i))&15;
            if(k==d) return 1;
        }
        return 0;
    };
    auto print = [&](int s){
        for(int i=0;i<n;i++){
            int k=(s>>(4*i))&15;
        }
    };
    for(int y=1;y<m;y++){
        map<int,int> g;
        for(auto [s,d]:f){
            g[(s<<4)+(n-1)*2]+=d;
            g[(s<<4)+(n-1)*2+1]+=d;
        }
        swap(f,g);
        for(int x=1;x<n;x++){
            g.clear();
            for(auto [s,d]:f){
                int dd=d%mod;
                int a=(s>>(4*x))&15,b=(s&15);
                for(auto k:link){
                    int ns=s;
                    bool ok=true;

                    vector<int> T={a,b,n<<1,(n+1)<<1},ST=T;
                    for(int i=1;i<4;i++){
                        int j=i-1;
                        while(j>=0 && k[i]!=k[j]) j--;
                        if(j==-1) continue;
                        if(T[i]==T[j]){
                            ok=false;
                            break;
                        }
                        if((T[i]&1) && (T[j]&1)){
                            ok=false;
                            break;
                        }
                        int c=T[j]|(T[i]&1);
                        ns=transform(ns,T[i],c);
                        ns=transform(ns,T[j],c);
                        int val=T[j];T[i]=val;
                        for(int t=0;t<4;t++) if(T[t]==val) T[t]=c;
                    }
                    if(!ok) continue;
                    
                    ns^=(T[0]^T[2])<<(4*x);
                    ns^=(T[1]^T[3]);

                    if(cnt(ns,n,T[0])==0 && !(T[0]&1)) ok=false;
                    if(cnt(ns,n,T[1])==0 && !(T[1]&1)) ok=false;
                    if(!ok) continue;
                    g[compress(ns,n)]+=dd;
                }
            }
            swap(f,g);
        }
        g.clear();
        for(auto [s,d]:f){
            int dd=d%mod;
            int ns=s>>4,k=s&15;
            if(cnt(ns,n-1,k)!=0 || (k&1)) g[compress(ns,n-1)]+=dd;
            if(!(k&1)){
                ns=transform(ns,k,k|1);
                g[compress(ns,n-1)]+=dd;
            }
        }
        swap(f,g);
    }

    int res=0;
    for(auto [s,d]:f){
        int cur=d%mod;
        map<int,int> dd;
        for(int i=0;i<n-1;i++){
            int k=(s>>(4*i))&15;
            if(!(k&1)) dd[k]++;
        }
        for(auto [x,val]:dd) cur=cur*val%mod;
        res=(res+cur)%mod;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
