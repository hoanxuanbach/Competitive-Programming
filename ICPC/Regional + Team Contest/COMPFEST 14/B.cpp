#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
int num=0,r,n,a[maxn],d;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> d;r=n;
    for(int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1,greater<int>());
    for(int i=1;i<=n;i++){
        int cur=r;
        while(a[i]*(cur-r+1)<=d && r>=i) r--;
        if(r<i) break;
        else num++;
    }
    cout << num << '\n';
}
