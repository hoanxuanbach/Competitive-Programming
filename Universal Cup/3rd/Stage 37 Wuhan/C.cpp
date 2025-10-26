#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf = 1e9;

void solve(){
    int n,m;cin >> n >> m;
    vector<int> res(m);res[0]=n;

    vector<int> c(m),d(m),e(m);

    for(int i=1;i<n;i++){
        int x;cin >> x;

        int k=x/(2*n-1),t=0;
        if((2*n-i)+k*(2*n-1)>i+x) t=1;
        else k++;
        if(k>=m) continue;
        if(!t) c[k]++;
        else{
            int nk=x/(2*n-1)+1,nt=1;
            if(i+nk*(2*n-1)>2*n-i+x) nt=0;
            if(nt) d[k]++;
            else e[k]++;
        }
    }
    {//i==n;
        int x;cin >> x;
        int k=x/(2*n-1)+1;
        if(k<m) c[k]++;
    }

    for(int k=0;k<m;k++){
        if(k) for(int i=k;i<m;i+=k) res[i]+=c[k];
        for(int i=k;i<m;i+=(k+1)) res[i]+=d[k];
        for(int i=k;i<m;i+=2*k+1){
            res[i]+=e[k];
            if(i+(k+1)<m) res[i+k+1]+=e[k];
        }
    }
    for(int i=0;i<m;i++) cout << res[i] << ' ';
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;cin >> test;
    while(test--) solve();
}