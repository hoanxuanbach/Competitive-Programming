#include<bits/stdc++.h>
using namespace std;
#define int long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
#define maxn 1005
char c[maxn];
void solve(){
    int n;cin >> n;
    while(true){
        int x=rng()%n;
        while(x*2+1==n) x=rng()%n;
        int y=n-x-1,a=x,b=y;
        for(int j=0;j<1000;j++){
            if(x==y) break;
            if(x>y) x-=y+1;
            else y-=x+1;
        }
        if(x!=0 || y!=0) continue;
        int sz=0;
        for(int j=0;j<1000;j++){
            if(a==0 && b==0) break;
            if(a>b){c[sz++]='a';a-=b+1;}
            else{c[sz++]='b';b-=a+1;}
        }
        for(int i=sz-1;i>=0;i--) cout << c[i];
        cout << '\n';
        return;
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--) solve();
}
