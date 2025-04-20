#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> a[20],p;

void dfs(int x,int val){
    if(x==-1 && a[0].empty()){
        reverse(p.begin(),p.end());
        for(int k:p) cout << k << ' ';
        cout << '\n';
        reverse(p.begin(),p.end());
        return;
    }
    if(x<0){
        for(int i=0;i<n;i++){
            if(a[i].empty()) break;
            if((int)a[i].size()==(int)a[i+1].size()) continue;
            int cur=a[i].back();
            a[i].pop_back();
            dfs(i,cur);
            a[i].push_back(cur);
        }
        return;
    }
    if(!x){
        p.push_back(val);
        dfs(-1,-1);
        p.pop_back();
        return;
    }
    x--;
    for(int i=0;i<(int)a[x].size();i++){
        if(a[x][i]>val) break;
        if(i+1<(int)a[x].size() && a[x][i+1]<val) continue;
        int cur=a[x][i];
        a[x][i]=val;
        dfs(x,cur);
        a[x][i]=cur;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n;
    for(int i=0;i<n;i++){
        int sz;cin >> sz;
        for(int j=0;j<sz;j++){int x;cin >> x;a[i].push_back(x);}
    }
    dfs(-1,-1);
}
