#include "paint.h"
#include <bits/stdc++.h>
using namespace std;
const int maxn=200005;
const int maxk=105;
int n,k,d[maxn],x[maxn],num[maxk][4],c[maxk];
bool pre[maxn][maxk],suf[maxn][maxk];
bool pp[maxn][maxk],ss[maxn][maxk];

string solve_puzzle(string s, vector<int> C) {
    n=(int)s.length();k=(int)C.size();
    for(int i=0;i<k;i++) c[i+1]=C[i];
    pre[0][0]=suf[n+1][k+1]=1;d[0]=d[n+1]=3;
    for(int i=0;i<n;i++) d[i+1]=(s[i]=='.'?3:(s[i]=='X'?1:2));

    for(int i=1;i<=n;i++){
        for(int j=0;j<=k;j++) if(d[i]&2) pre[i][j]|=pre[i-1][j];
        for(int j=1;j<=k;j++){
            num[j][d[i]]++;
            if(i>c[j]) num[j][d[i-c[j]]]--;
            if(i>=c[j] && (d[i-c[j]]&2)) pp[i][j]=((i>c[j]?pre[i-c[j]-1][j-1]:j==1) && !num[j][2]);
            pre[i][j]|=pp[i][j];
        }
    }

    for(int i=1;i<=k;i++) for(int j=1;j<=3;j++) num[i][j]=0;

    for(int i=n;i>=1;i--){
        for(int j=1;j<=k+1;j++) if(d[i]&2) suf[i][j]|=suf[i+1][j];
        for(int j=1;j<=k;j++){
            num[j][d[i]]++;
            if(i+c[j]<=n) num[j][d[i+c[j]]]--;
            if(i+c[j]<=n+1 && (d[i+c[j]]&2)) ss[i][j]=((i+c[j]<=n?suf[i+c[j]+1][j+1]:j==k) && !num[j][2]);
            suf[i][j]|=ss[i][j];
        }
    }

    for(int j=1;j<=k;j++){
        for(int i=c[j];i<=n;i++) if(pp[i][j] && ss[i-c[j]+1][j]){
            x[i-c[j]+1]++;x[i+1]--;
        }
    }

    for(int i=1;i<=n;i++) x[i]+=x[i-1];
    for(int i=1;i<=n;i++) x[i]=(x[i]>=1);

    for(int j=0;j<=k;j++){
        for(int i=1;i<=n;i++) if((d[i]&2) && pre[i-1][j] && suf[i+1][j+1]) x[i]|=2;
    }
    string res;
    for(int i=1;i<=n;i++) res.push_back((x[i]==3?'?':(x[i]==1?'X':'_')));
    return res;
}
