#include<bits/stdc++.h>
using namespace std;
#define int long long
int lt[35][35],rt[35][35],num[35],ans[(1<<16)+5],f[(1<<16)+5];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    string s;cin >> s;
    for(char c:s){
        num[c-'a']++;
        for(int i=0;i<16;i++) lt[c-'a'][i]+=num[i];
    }
    reverse(s.begin(),s.end());
    for(int i=0;i<16;i++) num[i]=0;
    for(char c:s){
        num[c-'a']++;
        for(int i=0;i<16;i++) rt[c-'a'][i]+=num[i];
    }
    int res=0;
    for(int i=0;i<16;i++) f[(1<<i)]=i;
    for(int i=1;i<(1<<16);i++){
        int p=f[i&(-i)],del=0,add=0;
        for(int j=0;j<16;j++){
            if(j==p) continue;
            if((i&(1<<j))) del+=rt[p][j];
            else add+=lt[p][j];
        }
        ans[i]=ans[i^(1<<p)]+add-del;
        res=max(res,ans[i]);
    }
    cout << res << '\n';
}