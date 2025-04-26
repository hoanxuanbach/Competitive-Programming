#include<bits/stdc++.h>
using namespace std;
#define int long long
const int inf=1e16;
int cnt=0;
vector<int> p={2,3,5,7,11,13,17,19,23,29,31,37,41};
void backtrack(int cur,int x){
    if(x==(int)p.size()){
        cnt++;
        return;
    }
    backtrack(cur,x+1);
    while(cur<=inf/p[x]){
        cur*=p[x];
        backtrack(cur,x+1);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    auto st=clock();
    backtrack(1,0);
    cout << cnt << '\n';
    cout << clock()-st << '\n';
}
