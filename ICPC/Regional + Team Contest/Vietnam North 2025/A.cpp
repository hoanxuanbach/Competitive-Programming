#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii array<int,2>
const int S = 155;
int c[S][S][S],d[S][S][S],f[S][S][S];

int lt[S],a[S];
int get(int P,int Q,int R){
    for(int k=1;k<=R;k++){
        for(int i=1;i<=P;i++){
            for(int j=1;j<=Q;j++){
                f[i][j][k]=(d[i][j][k]?0:min({f[i-1][j][k],f[i][j-1][k],f[i-1][j-1][k]})+1);
            }
        }
    }
    int res=0;
    for(int i=1;i<=P;i++) for(int j=1;j<=Q;j++){
        for(int k=1;k<=R;k++) a[k]=f[i][j][k];
        vector<int> v;
        for(int k=1;k<=R;k++){
            while(!v.empty() && a[v.back()]>=a[k]) v.pop_back();
            lt[k]=(v.empty()?1:v.back()+1);
            v.push_back(k);
        }
        v.clear();
        for(int k=R;k>=1;k--){
            while(!v.empty() && a[v.back()]>=a[k]) v.pop_back();
            int r=(v.empty()?R:v.back()-1);
            res=max(res,(r-lt[k]+1)*a[k]);
            v.push_back(k);
        }
    }
    return res;
}

void solve(){
	int P,Q,R;cin >> P >> Q >> R;
    for(int j=1;j<=Q;j++) for(int i=1;i<=P;i++) for(int k=1;k<=R;k++){
        char cc;cin >> cc;
        c[i][j][k]=d[i][j][k]=(cc=='P');
    }
    int res=get(P,Q,R);
    for(int i=1;i<=P;i++) for(int j=1;j<=Q;j++) for(int k=1;k<=R;k++) d[i][k][j]=c[i][j][k];
    res=max(res,get(P,R,Q));
    for(int i=1;i<=P;i++) for(int j=1;j<=Q;j++) for(int k=1;k<=R;k++) d[j][k][i]=c[i][j][k];
    res=max(res,get(Q,R,P));
    cout << 4*res << '\n';
} 

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
