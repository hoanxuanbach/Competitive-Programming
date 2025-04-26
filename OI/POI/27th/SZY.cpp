#include<bits/stdc++.h>
using namespace std;
#define maxn 1000005
#define all(a) a.begin(),a.end()
vector<int> x[200];
int kmp[maxn],n,ans=1,m,l;
string s,t;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> s >> t;
    n=(int)s.length();m=(int)t.length();
    s="#"+s;kmp[0]=-1;
    for(int i=2;i<=n;i++){
        int j=kmp[i-1];
        while(j!=-1 && s[j+1]!=s[i]) j=kmp[j];
        kmp[i]=j+1;
    }
    for(int i=kmp[n]+1;i<=n;i++) x[s[i]].push_back(i);
    for(int i=1;i<=n;i++){
        if(l<m && t[l]==s[i]) l++;
    }
    if(l==m){
        cout << 0 << '\n';
        return 0;
    }
    while(l<m){
        int cur=1;ans++;
        if(x[t[l]].empty()){
            cout << "INF\n";
            return 0;
        }
        cur=x[t[l]][0]+1;l++;
        while(l<m){
            int p=lower_bound(all(x[t[l]]),cur)-x[t[l]].begin();
            if(p==(int)x[t[l]].size()) break;
            cur=x[t[l]][p]+1;l++;
        }
    }
    cout << ans-1 << '\n';
}
