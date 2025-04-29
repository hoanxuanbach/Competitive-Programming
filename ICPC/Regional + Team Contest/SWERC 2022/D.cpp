#include<bits/stdc++.h>
using namespace std;
pair<int,string> decode(string s){
    int numb=0;
    for(int i=0;i<s.length();i++) numb+=(s[i]=='B');
    numb%=2;
    string ans;
    for(int i=0;i<s.length();i++){
        if(s[i]=='B') continue;
        if(ans.empty()) ans.push_back(s[i]);
        else{
            if(ans.back()==s[i]) ans.pop_back();
            else ans.push_back(s[i]);
        }
    }
    return {numb,ans};
}
bool solve(){
    string a,b;cin >> a >> b;
    pair<int,string> x=decode(a),y=decode(b);
    if(x!=y) return false;
    else return true;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--){
        if(solve()) cout << "YES\n";
        else cout << "NO\n";
    }
}

