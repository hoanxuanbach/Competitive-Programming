#include<bits/stdc++.h>
using namespace std;
#define int long long

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    map<int,int> cnt;
    vector<int> a(n),b(n);

    for(int i=0;i<n;i++) cin >> a[i],cnt[a[i]]++;
    for(int i=0;i<n;i++) cin >> b[i],cnt[b[i]]++;
    cnt[a[0]]--;
    a[0]=b[0]=0;

    for(int i=1;i<n;i++) a[i]=max(a[i],a[i-1]),b[i]=max(b[i],b[i-1]);

    int x=0;
    for(int i=1;i<n;i++){
        while(x<n && b[x]<=a[i]) x++;
        cnt[a[i]]+=x-1;
        //cout << i << ' ' << x << '\n';
    }
    x=0;
    for(int i=1;i<n;i++){
        while(x<n && a[x]<b[i]) x++;
        cnt[b[i]]+=x-1;
        //cout << i << ' ' << x << '\n';
    }

    int c=0,val=0;
    for(auto [x,d]:cnt){
        if(d>=val) c=x,val=d;
    }
    cout << c << ' ' << val << '\n';
}