#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll maxN = 1e18;

void solve(){
    ll n = inf.readLong();
    int k = ouf.readInt();
    int K = ans.readInt();
    if(k!=K) quitf(_wa,"Wrong Answer");
    
    int D=0;

    int cnt=0;
    vector<ll> S;
    for(int i=0;i<k;i++){
        int m=ouf.readInt();
        vector<ll> f(m);cnt+=m;
        for(int j=0;j<m;j++){
            f[j]=ouf.readLong(1,n);
            if(n%f[j]!=0){
                quitf(_wa,"Wrong Answer");
            }
            if(j && f[j]%f[j-1]!=0){
                quitf(_wa,"Wrong Answer");
            }
            if(j && f[j]<=f[j-1]){
                quitf(_wa,"Wrong Answer");
            }
            S.push_back(f[j]);
        }

        m=ans.readInt();D+=m;
        for(int j=0;j<m;j++) ans.readLong();
    }
    if(cnt!=D){
        quitf(_wa,"Wrong Answer");
    }
    sort(S.begin(),S.end());
    S.erase(unique(S.begin(),S.end()),S.end());
    if((int)S.size()!=cnt){
        quitf(_wa,"Wrong Answer");
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    int T = inf.readInt();
    for(int test=1;test<=T;test++){
        setTestCase(test);
        solve();
    }
    quitf(_ok, "Accepted");
}
