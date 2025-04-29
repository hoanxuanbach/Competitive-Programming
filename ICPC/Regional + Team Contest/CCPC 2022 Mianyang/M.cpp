#include<bits/stdc++.h>
using namespace std;
#define pii pair<int,int>
map<char,int> mp;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    mp['R']=0;mp['P']=1;mp['S']=2;
    while(t--){
        vector<pii> x;
        string s;cin >> s;
        for(int i=0;i<(int)s.length();i++){
            char c=s[i];
            int k=mp[c],total=1;
            while(!x.empty() && (k+1)%3!=x.back().first){
                total+=x.back().second;
                x.pop_back();
            }
            x.push_back({k,total});
        }
        int d=x[0].first;
        if(d==0) cout << 'R' << '\n';
        else if(d==1) cout << 'P' << '\n';
        else cout << 'S' << '\n';
    }
}
