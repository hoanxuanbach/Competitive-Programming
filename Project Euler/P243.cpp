#include<bits/stdc++.h>
using namespace std;
#define int long long

void solve(){
    int A,B;cin >> A >> B;

    int N=200;
    vector<int> p(N),X;
    for(int i=2;i<N;i++){
        if(!p[i]){
            X.push_back(i);
            for(int j=i;j<N;j+=i) p[j]=i;
        }
    }
    int a=1,b=1,c=1;
    for(int x:X){
        a*=(x-1);
        b*=x;c=x;
        if((__int128)a*B<(__int128)A*(b-1)){
            a/=(x-1);
            b/=x;
            break;
        }
    }
    for(int i=2;i<c;i++){
        int na=a*i,nb=b*i;
        if((__int128)na*B<(__int128)A*(nb-1)){
            cout << nb << '\n';
            return;
        }
    }
    cout << b*c << '\b';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
