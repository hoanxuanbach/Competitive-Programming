#include<bits/stdc++.h>
using namespace std;
#define int long long
string ans;
string add(string s,int n){
    if(n==0) return "";
    int d=n%9;
    string pre=add(s,n/9),res;
    if(!pre.empty()){
        res+="9";
        if((int)pre.length()>1) res+='[';
        res+=pre;
        if((int)pre.length()>1) res+=']';
    }
    if(!d) return res;
    if((int)s.length()==1){
        if(d>1) res+=char(d+'0');
        res+=s;
    }
    else{
        if(d>1) res+=char(d+'0');
        if(d>1 && (int)s.length()>1) res+='[';
        res+=s;
        if(d>1 && (int)s.length()>1) res+=']';
    }
    return res;
}
void solve2(int n);
void solve(int n){
    if(n==0) return;
    if(n%2==0){
        ans+=add("F",n/2);
        string nw=add("F",n/2);
        nw+=add("BD",n/2);nw+="B";
        ans+=add(nw,n/2);
        ans+=add("F",n/2);
        ans+=add("B",n/2);
        if(n!=2) ans+="2[";
        else ans+="2";
        solve2(n/2);
        if(n!=2) ans+="]";
    }
    else{
        ans+="F";
        solve(n-1);
        ans+="B";
        ans+=add("FB",n-1);
        ans+=add("D",n);
    }
}
void solve2(int n){
    if(n==0) return;
    if(n==1){
        ans+='D';
        return;
    }
    ans+=add("DF",n-1);
    ans+="D";
    ans+=add("BD",n-2);
    ans+="B";
    solve(n-2);
    ans+="D";
}
signed main(){
    //freopen("WDP.INP","r",stdin);
    //freopen("WDP.OUT","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;
    solve(n);
    cout << ans << '\n';
}
