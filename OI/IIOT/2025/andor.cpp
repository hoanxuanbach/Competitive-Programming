#include<bits/stdc++.h>
using namespace std;
const int L = 30;

void solve(){
    int n,K;cin >> n >> K;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++) cin >> a[i];
    for(int i=0;i<L;i++){
        int m=(1<<L)-1,m1=0;
        //cout << '*' << i << '\n';
        for(int j=n;j>=0;j--){
            int S=0;
            if(j){
                if(a[j]>>i&1) S|=a[j];
            }
            /*
            for(int k=j+1;k<=n;k++){
                if((a[k]>>i&1)) S&=a[k];
                else S|=a[k];
            }
            */
            //cout << S << ' ' << m << ' ' << m1 << '\n';
            S=(S&m)+m1;

            if(S==K){
                cout << "YES" << endl;
                return;
            }
            if(j){
                if(a[j]>>i&1){
                    //cout << '&' << a[j] << '\n';
                    m&=a[j];
                }
                else{
                    //cout << '|' << a[j] << '\n';
                    int x=(m&a[j]);
                    m^=x;m1^=x;
                }
            }
        }
    }
    cout << "NO" << endl;
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}
