#include<bits/stdc++.h>
using namespace std;
bool c[30],ok[40];
bool solve(){
    string s,t;cin >> s >> t;
    int id=t.length()-1;
    for(int i=0;i<26;i++) c[i]=false;
    for(int i=s.length()-1;i>=0;i--){
        if(id>=0 && s[i]==t[id]){ok[i]=true;id--;}
        else ok[i]=false;
    }
    if(id>=0) return false;
    for(int i=0;i<s.length();i++){
        if(ok[i]) c[s[i]-'A']=true;
        else if(c[s[i]-'A']) return false;
    }
    return true;
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
