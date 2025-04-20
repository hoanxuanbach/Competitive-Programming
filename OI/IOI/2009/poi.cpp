#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int N,T,P;cin >> N >> T >> P;P--;
    vector<vector<int>> c(N,vector<int>(T,0));
    vector<int> cnt(T,N);
    for(int i=0;i<N;i++) for(int j=0;j<T;j++) cin >> c[i][j],cnt[j]-=c[i][j];
    vector<array<int,3>> cc(N);
    for(int i=0;i<N;i++){
        int total=0,sum=0;
        for(int j=0;j<T;j++) sum+=c[i][j],total+=c[i][j]*cnt[j];
        cc[i]={-total,-sum,i};
    }
    sort(cc.begin(),cc.end());
    for(int i=0;i<N;i++) if(cc[i][2]==P){
        cout << -cc[i][0] << ' ' << i+1 << '\n';
        return 0;
    }
}
