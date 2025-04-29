#include<bits/stdc++.h>
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,ans=0,num=1;string s;cin >> n >> s;
    for(int i=1;i<n;i++){
        if(s[i]==s[i-1]) num++;
        else{
            if(s[i-1]=='a' && num>=2) ans+=num;
            num=1;
        }
    }
    if(s[n-1]=='a' && num>=2) ans+=num;
    cout << ans << '\n';
}
