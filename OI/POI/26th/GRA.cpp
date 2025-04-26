#include "gralib.hpp"
#include<bits/stdc++.h>
using namespace std;
#define ld long double
#define maxn 250005
ld dp[maxn],v[maxn];
vector<int> d[maxn];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n=dajN(),k=dajK(),m=dajM();
    for(int i=1;i<=k;i++){
        d[0].push_back(i);
        for(int j=i;j<=n-i;j+=i) d[j].push_back(i);
    }
    for(int i=n-1;i>=0;i--){
        int sz=0;
        for(int x:d[i]) v[++sz]=dp[i+x];
        sort(v+1,v+sz+1);
        ld sum=0;dp[i]=LLONG_MAX;
        for(int j=1;j<=sz;j++){sum+=v[j]+1;dp[i]=min(dp[i],(sum+k)/j);}
    }
    for(int t=1;t<=100;t++){
        int cur=0;
        while(true){
            int d=nastepna();
            //cout << cur << ' ' << d << '\n';
            if(cur%d!=0 || cur+d>n) continue;
            if(dp[cur]>dp[cur+d]){
                zwieksz();
                cur+=d;
            }
            if(cur==n){koniec();break;}
        }

    }
}
