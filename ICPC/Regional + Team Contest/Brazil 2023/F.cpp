#include<bits/stdc++.h>
using namespace std;
map<string,int> mp;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,c;cin >> n >> c;
    for(int i=1;i<=n;i++){
        string s;cin >> s;
        for(int j=0;j<c;j++){
            if(s[j]!='*') continue;
            for(int k=0;k<26;k++){
                s[j]=char(k+'a');
                mp[s]++;
            }
        }
    }
    int ans=0;string res;
    for(auto it:mp){
        if(it.second>ans){
            ans=it.second;
            res=it.first;
        }
    }
    cout << res << ' ' << ans << '\n';
}

