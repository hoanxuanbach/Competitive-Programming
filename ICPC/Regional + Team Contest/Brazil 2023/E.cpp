#include<bits/stdc++.h>
using namespace std;
#define maxa 1000005
int num[maxa],cnt=0;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    for(int i=1;i<=n;i++){
        int a;cin >> a;
        if(num[a+1]>=1){num[a+1]--;cnt--;}
        num[a]++;cnt++;
    }
    cout << cnt << '\n';
}
