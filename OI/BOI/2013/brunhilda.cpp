#include<bits/stdc++.h>
using namespace std;
#define maxa 10000000
#define maxn 100005
#define pii pair<int,int>
int q,m,dp[maxa+5],pp[maxa+5];
vector<int> pr;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> m >> q;
    for(int i=1;i<=m;i++){
        int p;cin >> p;
        for(int j=0;j<=maxa;j+=p) pp[j]=p;
    }
    int pre=0,lst=0,num=0,dead=-1;
    while(true){
        if(pre>lst){
            dead=pre;
            break;
        }
        int nxt=lst;
        for(int i=pre;i<=lst;i++) nxt=max(nxt,i+pp[i]-1);
        pre=lst+1;lst=nxt;num++;
        for(int i=pre;i<=min(lst,maxa);i++) dp[i]=num;
        if(lst>maxa) break;
    }
    for(int i=1;i<=q;i++){
        int a;cin >> a;
        if(a>=dead && dead!=-1) cout << "oo\n";
        else cout << dp[a] << '\n';
    }
}
