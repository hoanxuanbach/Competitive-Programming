#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 50515093;
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
    int N;cin >> N;
    vector<pii> P(N);
    int S=290797;
    for(int i=0;i<2*N;i++){
        S=S*S%mod;
        if(i&1) P[i/2].second=S%2000;
        else P[i/2].first=S%2000;
    }

    map<pii,set<pii>> mp;
    for(int i=0;i<N;i++) for(int j=0;j<i;j++){
        int A=P[i].second-P[j].second;
        int B=P[i].first-P[j].first;
        int C=P[i].first*P[j].second-P[i].second*P[j].first;
        int D=B;

        int g=__gcd(A,B);
        A/=g;B/=g;
        g=__gcd(C,D);
        C/=g;D/=g;
        if(B<0) A=-A,B=-B;
        if(D<0) C=-C,D=-D;
        //cout << i << ' ' << j << ' ' << A << ' ' << B << ' ' << C << ' ' << D << '\n';
        if(!B){
            //assert(A==1);
            //cout << i << ' ' << j << ' ' << P[i].first << ' ' << C << ' ' << D << '\n';
            mp[{1,0}].insert({P[i].first,P[i].first});
            //mp[{1,0}].insert({C,D});
            continue;
        }
        else mp[{A,B}].insert({C,D});
    }
    int cnt=0,sub=0;
    for(auto [x,v]:mp){
        int sz=(int)v.size();
        cnt+=sz;
        sub+=sz*(sz-1);
    }
    cout << cnt << '\n';
    cout << cnt*(cnt-1)-sub << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
