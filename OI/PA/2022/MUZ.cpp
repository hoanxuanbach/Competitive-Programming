#include<bits/stdc++.h>
using namespace std;
int num[1000005];
signed main(){
    //freopen("MUZ.INP","r",stdin);
    //freopen("MUZ.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,res;cin >> n;res=n;
    for(int i=1;i<=n;i++) num[i]=num[i-1]+__builtin_popcount(i);
    vector<int> ans;
    for(int i=n;i>=1;i--){
        if(num[i-1]>=res) continue;
        else{
            res-=__builtin_popcount(i);
            ans.push_back(i);
        }
    }
    cout << (int)ans.size() << '\n';
    for(int v:ans) cout << v << ' ';

}
