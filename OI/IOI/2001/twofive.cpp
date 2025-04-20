#include<bits/stdc++.h>
using namespace std;
const int N = 25;
char C[5][5];

int cnt[(1<<10)+5];
vector<int> ss;
vector<array<int,3>> f[(1<<10)+5];

void preprocess(){
    for(int mask=0;mask<(1<<10);mask++){
        if(__builtin_popcount(mask)!=5) continue;
        ss.push_back(mask);
        int x=0,y=5;
        for(int i=0;i<10;i++){
            if(mask>>i&1) cnt[mask]+=y,x++;
            else y--;
            if((mask>>i&3)==2) f[mask].push_back({i,x,y});
        }
    }
    reverse(ss.begin(),ss.end());
}

int dp[(1<<10)+5];

int cal(string S){
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) C[i][j]='.';
    for(int i=0;i<S.length();i++) C[i/5][i%5]=S[i];
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            if(i && C[i][j]!='.' && C[i][j]<=C[i-1][j]) return 0;
            if(j && C[i][j]!='.' && C[i][j]<=C[i][j-1]) return 0;
        }
    }
    for(int mask:ss) dp[mask]=0;
    dp[ss[0]]=1;
    for(int mask:ss){
        if(!dp[mask]) continue;
        char cur=cnt[mask]+'A';
        for(auto &[i,x,y]:f[mask]){
            int nmask=mask^(3<<i);
            if(C[x][y]!='.' && C[x][y]!=cur) continue;
            dp[nmask]+=dp[mask];
        }
    }
    return dp[ss.back()];
}

namespace sub1{
    void solve(){
        string s;cin >> s;
        int total=1;
        string cur;
        for(int i=0;i<N;i++){
            for(char c='A';c<s[i];c++) total+=cal(cur+c);
            cur+=s[i];
        }
        cout << total << '\n';
    }
}
namespace sub2{
    void solve(){
        int total;cin >> total;
        string cur;
        for(int i=0;i<N;i++){
            for(char c='A';c<='Z';c++){
                int val=cal(cur+c);
                if(val<total) total-=val;
                else{cur+=c;break;}
            }
        }
        cout << cur << '\n';
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    preprocess();
    char sub;cin >> sub;
    if(sub=='W') sub1::solve();
    else sub2::solve();
}
