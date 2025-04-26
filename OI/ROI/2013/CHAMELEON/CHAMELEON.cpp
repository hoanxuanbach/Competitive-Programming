// Judges with GCC >= 12 only needs Ofast
// #pragma GCC optimize("O3,no-stack-protector,fast-math,unroll-loops,tree-vectorize")
// MLE optimization
// #pragma GCC optimize("conserve-stack")
// Old judges
// #pragma GCC target("sse4.2,popcnt,lzcnt,abm,mmx,fma,bmi,bmi2")
// New judges. Test with assert(__builtin_cpu_supports("avx2"));
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma,tune=native")
// Atcoder
// #pragma GCC target("avx2,popcnt,lzcnt,abm,bmi,bmi2,fma")
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> ordered_set;
- insert(x),erase(x)
- find_by_order(k): return iterator to the k-th smallest element
- order_of_key(x): the number of elements that are strictly smaller
*/

#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<> pp(0.0,1.0);
#define ld long double
#define pii pair<int,int>
#define piii pair<pii,int>
#define mpp make_pair
#define fi first
#define se second
const int mod=998244353;
const int maxn=105;
const int bl=650;
const int maxs=655;
const int maxm=200005;
const int maxq=1000005;
const int maxl=20;
const int maxa=1000000;
const int root=3;
const int base=101;

int n,tt,c[maxn][maxn];
namespace sub{
    string cal(int cx,int cy,vector<vector<int>> d){
        vector<int> num(2,0);cx--;cy--;
        for(int i=0;i<2;i++) for(int j=0;j<2;j++) num[d[i][j]]++;
        string res;
        if(cx==1) res+="u";
        if(num[0]==0) res+="LD";
        else if(num[0]==1){
            if(d[0][0]==0) res+="dL";
            else if(d[1][0]==0) res+="L";
            else if(d[0][1]==0) res+="lRdLU";
            else res+="LdRulD";
        }
        else if(num[0]==2){
            if(d[0][0]==0){
                if(d[0][1]==0) res+="lRdL";
            }
            else if(d[1][0]==0) res+="LdR";
            else if(d[0][1]==0) res+="lRdLUrD";
        }
        else if(num[0]==3){
            if(d[0][0]==1) res+="LdRU";
            else if(d[1][0]==1) res+="dLuRD";
            else if(d[0][1]==1) res+="ldR";
            else res+="lR";
        }
        else res+="lRD";
        return res;
    }
    void solve(){
        string res;
        int cx=1,cy=1;
        for(int i=1;i<=n;i++){
            if(i&1){
                if(cy==1){
                    for(int j=1;j<n;j++) res+="R";
                    cy=n;
                }
                else{
                    for(int j=n;j>1;j--) res+="L";
                    cy=1;
                }
            }
            else{
                res+="D";cx++;
                if(i<n) res+="Du";
                if(cy==n) res+="lR";
                else res+="rL";
                if(i<n) res+="d",cx++;
            }
        }
        for(int i=n;i>=3;i--){
            if(cy==1){
                for(int j=1;j<=n;j++){
                    if(c[i][j]!=(i&1)) res+="uD";
                    if(j<n) res+="r";
                }
                cy=n;
            }
            else{
                for(int j=n;j>=1;j--){
                    if(c[i][j]!=(i&1)) res+="uD";
                    if(j>1) res+="l";
                }
                cy=1;
            }
            cx--;res+="u";
        }
        if(cy==1){
            for(int i=1;i<=n;i++){
                if(cx==2) res+="U",cx--;
                else res+="D",cx++;
                if(i<n) res+="r",cy++;
            }
            for(int i=n;i>=3;i--){
                bool ok=false;
                if(c[cx][i]==(i&1)) res+="lR",ok=true;
                if(cx==2) res+="u";
                else res+="d";
                cx^=3;
                if(c[cx][i]==(i&1)){
                    if(ok) res.back()=char(res.back()-'a'+'A');
                    else res+="lR";
                }
                res+="l";cy--;
            }
            vector<vector<int>> d(2,vector<int>(2,0));
            for(int i=0;i<2;i++) for(int j=0;j<2;j++) d[i][j]=c[i+1][j+1];
            string s=cal(cx,cy,d);
            res+=s;
        }
        else{
            for(int i=n;i>=1;i--){
                if(cx==2) res+="U",cx--;
                else res+="D",cx++;
                if(i>1) res+="l",cy--;
            }
            for(int i=1;i<=n-2;i++){
                bool ok=false;
                if(c[cx][i]!=((n-i)&1)) res+="rL",ok=true;
                if(cx==2) res+="u";
                else res+="d";
                cx^=3;
                if(c[cx][i]!=((n-i)&1)){
                    if(ok) res.back()=char(res.back()-'a'+'A');
                    else res+="rL";
                }
                res+="r";cy++;
            }
            vector<vector<int>> d(2,vector<int>(2,0));
            for(int i=0;i<2;i++) for(int j=0;j<2;j++) d[i][j]=c[i+1][n-j];
            //cout << d[0][0] << ' ' << d[0][1] << ' ' << d[1][0] << ' ' << d[1][1] << '\n';
            string s=cal(cx,n-cy+1,d);
            //cout << cx << ' ' << cy << ' ' << s << '\n';
            for(int i=0;i<(int)s.length();i++){
                if(s[i]=='R') s[i]='L';
                else if(s[i]=='L') s[i]='R';
                else if(s[i]=='r') s[i]='l';
                else if(s[i]=='l') s[i]='r';
            }
            res+=s;
        }
        //cout << (int)res.size() << '\n';
        cout << res << '\n';
    }
}
void solve(){
    cin >> n;
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++){
        char ch;cin >> ch;
        c[i][j]=(ch=='B'?1:0);
    }
    cin >> tt;
    if(tt<14){
        sub::solve();
        return;
    }
    string res;
    int px=-1,py=-1;
    for(int i=1;i<n;i++) for(int j=1;j<=n;j++){
        if(px!=-1) break;
        if(c[i][j]==c[i+1][j]){
            px=i,py=j;
            break;
        }
    }
    int cx=1,cy=1;
    for(int i=1;i<=n;i++){
        if(i&1){
            if(cy==1){
                for(int j=1;j<n;j++) res+="R";
                cy=n;
            }
            else{
                for(int j=n;j>1;j--) res+="L";
                cy=1;
            }
        }
        else{
            res+="D";cx++;
            if(i<n) res+="Du";
            if(cy==n) res+="lR";
            else res+="rL";
            if(i<n) res+="d",cx++;
        }
    }
    for(int i=n;i>px+1;i--){
        if(cy==1){
            for(int j=1;j<=n;j++){
                if(c[i][j]!=(i&1)) res+="uD";
                if(j<n) res+="r";
            }
            cy=n;
        }
        else{
            for(int j=n;j>=1;j--){
                if(c[i][j]!=(i&1)) res+="uD";
                if(j>1) res+="l";
            }
            cy=1;
        }
        cx--;res+="u";
    }
    cx--;res+="u";
    if(px>1){
        for(int i=1;i<px;i++) cx--,res+="u";
        for(int i=1;i<px;i++){
            if(cy==1){
                for(int j=1;j<=n;j++){
                    if(c[i][j]!=(i&1)) res+="dU";
                    if(j<n) res+="r";
                }
                cy=n;
            }
            else{
                for(int j=n;j>=1;j--){
                    if(c[i][j]!=(i&1)) res+="dU";
                    if(j>1) res+="l";
                }
                cy=1;
            }
            res+="d",cx++;
        }
    }
    //cout << px << ' ' << py << ' ' << cx << ' ' << cy << '\n';
    if(cy==n){
        int st=px&1;
        if(((n-py)&1)!=((cx&1)^c[px][py])) res+="d",cx++,st^=1;
        for(int i=n;i>=1;i--){
            if(cx==px) res+="D",cx++;
            else res+="U",cx--;
            if(i>1) res+="l",cy--;
        }
        for(int i=1;i<py;i++){
            if(c[cx][cy]!=((st^(n-i))&1)) res+="rL";
            if(cx==px+1) res+="u",cx--;
            else res+="d",cx++;
            if(c[cx][cy]!=((st^(n-i))&1)) res+="rL";
            res+="r",cy++;
        }
        for(int i=py;i<n;i++) res+="r",cy--;
        for(int i=n;i>py;i--){
            if(c[cx][cy]!=((st^(n-i))&1)) res+="lR";
            if(cx==px+1) res+="u",cx--;
            else res+="d",cx++;
            if(c[cx][cy]!=((st^(n-i))&1)) res+="lR";
            res+="l",cy--;
        }
    }
    else{
        int st=px&1;
        if(((py-1)&1)!=((cx&1)^c[px][py])) res+="d",cx++,st^=1;
        for(int i=1;i<=n;i++){
            if(cx==px) res+="D",cx++;
            else res+="U",cx--;
            if(i<n) res+="r",cy++;
        }
        for(int i=n;i>py;i--){
            if(c[cx][cy]!=((st^(i-1))&1)) res+="lR";
            if(cx==px+1) res+="u",cx--;
            else res+="d",cx++;
            if(c[cx][cy]!=((st^(i-1))&1)) res+="lR";
            res+="l",cy--;
        }
        for(int i=py;i>1;i--) res+="l",cy--;
        for(int i=1;i<py;i++){
            if(c[cx][cy]!=((st^(i-1))&1)) res+="rL";
            if(cx==px+1) res+="u",cx--;
            else res+="d",cx++;
            if(c[cx][cy]!=((st^(i-1))&1)) res+="rL";
            res+="r",cy++;
        }
    }
    //cout << n << '\n';
    //cout << (int)res.size() << '\n';
    cout << res << '\n';
}

signed main(){
    //freopen("17","r",stdin);
    //freopen("17.out","w",stdout);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();

}
