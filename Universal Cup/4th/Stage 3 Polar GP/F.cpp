#include<bits/stdc++.h>
using namespace std;
#define ld double 
const int N = 1e5+5;
const int M = 2e8;
ld dp[N];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int A,B;cin >> A >> B;
    if(!A){
        cout << 0 << '\n';
        return 0;
    }
    int D=min(B,M/A);
    vector<int> L(A+1),R(A+1);
    for(int i=0;i<=A;i++){
        int T=1LL*B*i/A;
        L[i]=max(T-D,0);
        R[i]=min(T+D,B);
    }

    for(int i=1;i<=A;i++){
        for(int j=L[i];j<=R[i];j++){
            ld g=0;
            if(j<=R[i-1]) g+=(dp[j]+1)*i/(i+j);
            if(j>L[i]) g+=(dp[j-1]-1)*j/(i+j);
            if(g<0) g=0;
            dp[j]=g;
        }
    }
    cout << setprecision(9) << fixed << dp[B] << '\n';
}