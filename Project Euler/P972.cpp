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

pii mul(pii x,pii y){
    pii P={x.first*y.first,x.second*y.second};
    int g=__gcd(P.first,P.second);assert(g);
    P.first/=g;P.second/=g;
    return P;
}
pii div(pii x,pii y){
    pii P={x.first*y.second,x.second*y.first};
    int g=__gcd(P.first,P.second);assert(g);
    P.first/=g;P.second/=g;
    return P;
}
pii del(pii x,pii y){
    pii P={x.first*y.second-y.first*x.second,x.second*y.second};
    int g=__gcd(P.first,P.second);assert(g);
    P.first/=g;P.second/=g;
    return P;
}
pii add(pii x,pii y){
    pii P={x.first*y.second+y.first*x.second,x.second*y.second};
    int g=__gcd(P.first,P.second);assert(g);
    P.first/=g;P.second/=g;
    return P;
}

void solve(){
    int N;cin >> N;
    vector<pii> pp;
    for(int x=1;x<=N;x++) for(int i=0;i<x;i++) if(__gcd(i,x)==1){
        pp.push_back({i,x});
        if(i) pp.push_back({-i,x});
    }

    vector<array<pii,3>> P;
    for(auto x:pp) for(auto y:pp){
        auto z=add(mul(x,x),mul(y,y));
        if(z.first>=z.second) continue;
        P.push_back({x,y,z});
    }
    int res=0;
    map<pii,vector<int>> S,S2;
    map<pair<pii,pii>,vector<int>> mp; 
    cout << (int)P.size() << endl;
    for(int i=0;i<(int)P.size();i++){
        cout << i << endl;
        for(int j=i+1;j<(int)P.size();j++){
            auto [x1,y1,z1]=P[i];
            auto [x2,y2,z2]=P[j];
            pii D=del(mul(x1,y2),mul(x2,y1));

            if(D.first==0){
                if(y1.first!=0){
                    pii T=div(x1,y1);
                    S[T].push_back(i);
                    S[T].push_back(j);
                }
                else if(x1.first!=0){
                    pii T=div(y1,x1);
                    S2[T].push_back(i);
                    S2[T].push_back(j);
                }
            }
            else{
                pii r1=add({1,2},mul(z1,{1,2}));
                pii r2=add({1,2},mul(z2,{1,2}));
                pii A=del(mul(r1,y2),mul(r2,y1));
                pii B=del(mul(r2,x1),mul(r1,x2));
                A=div(A,D);B=div(B,D);
                mp[{A,B}].push_back(i);
                mp[{A,B}].push_back(j);
            }
        }
    }
    for(auto [_,v]:S2){
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        int s=(int)v.size()+1;
        res+=s*(s-1)*(s-2);
    }
    for(auto [_,v]:S){
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        int s=(int)v.size()+1;
        res+=s*(s-1)*(s-2);
    }
    for(auto [_,v]:mp){
        sort(v.begin(),v.end());
        v.erase(unique(v.begin(),v.end()),v.end());
        int s=(int)v.size();
        res+=s*(s-1)*(s-2);
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
