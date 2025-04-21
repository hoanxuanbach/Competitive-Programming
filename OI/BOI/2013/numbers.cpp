#include<bits/stdc++.h>
using namespace std;
#define int long long
#define maxl 20
int dp[maxl][10][10],power[maxl];
int f(int len,int p,int q){
    if(p==q) return 0;
    if(len==2){
        if(p==q) return 0;
        else return 1;
    }
    if(dp[len][p][q]!=-1) return dp[len][p][q];
    int res=0;
    for(int i=0;i<=9;i++){
        if(i==q || i==p) continue;
        res+=f(len-1,q,i);
    }
    //cout << len << ' ' << p << ' ' << q << ' ' << res << '\n';
    return dp[len][p][q]=res;
}
int solve(int n){
    int sum=0;
    if(n<=9) return n+1;
    else sum=10;
    if(n==1e18) n--;
    string s=to_string(n);reverse(s.begin(),s.end());
    int len=s.length();
    for(int i=2;i<len;i++){
        for(int p=1;p<=9;p++){
            for(int q=0;q<=9;q++) sum+=f(i,p,q);
        }
    }
    int pre1=-1,pre2=-1,lst=len;
    for(int i=1;i<(s[len-1]-'0');i++){
        for(int p=0;p<=9;p++) sum+=f(len,i,p);
    }
    pre1=s[len-1]-'0';
    for(int i=len-1;i>=2;i--){
        int x=s[i-1]-'0';
        for(int p=0;p<x;p++){
            for(int q=0;q<=9;q++){
                if(p==pre2 || p==pre1 || q==pre1) continue;
                sum+=f(i,p,q);
            }
        }
        if(x==pre1 || x==pre2) break;
        pre2=pre1;pre1=x;lst=i;
    }
    if(lst==2){
        for(int i=0;i<=s[0]-'0';i++){
            if(i==pre1 || i==pre2) continue;
            sum++;
        }
    }
    return sum;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int a,b;cin >> a >> b;power[0]=1;
    for(int i=0;i<=18;i++){
        for(int p=0;p<=9;p++){
            for(int q=0;q<=9;q++) dp[i][p][q]=-1;
        }
    }
    for(int i=1;i<=18;i++) power[i]=power[i-1]*10;
    cout << solve(b)-solve(a-1) << '\n';
}
