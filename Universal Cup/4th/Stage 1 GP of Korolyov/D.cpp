#include<bits/stdc++.h>
using namespace std;
#define int long long 

void solve(){
    string s;cin >> s;
    int n=(int)s.length();

    string res;
    for(int l=0;l<n;){
        int r=l;
        while(r<n && s[r]==s[l]) r++;
        int d=r-l;
        if(!res.empty()){
            char c=res.back();res.pop_back();
            res+=s[l];res+=c;
        }
        for(int i=0;i<d;i++) res+=s[l];
        l=r;
    }
    res.pop_back();
    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}