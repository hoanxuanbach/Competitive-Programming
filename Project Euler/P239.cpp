#include<bits/stdc++.h>
using namespace std;
#define int long long 
#define pii pair<int,int>
const int mod = 998244353;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
 
const int maxn = 2e5+5;
const int inf = 1e18;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand_int(int l,int r){
    return l+abs((int)rng())%(r-l+1);
}

#define ld long double
#define i128 __int128 

i128 f[25][25][25][25];

string mul(string s,int x){
    string res;
    int d=0;
    for(char c:s){
        int k=c-'0';
        d+=k*x;
        res+=char('0'+d%10);
        d/=10;
    }
    while(d){
        res+=char('0'+d%10);
        d/=10;
    }
    return res;
}
string add(string a,string b){
    int d=0;
    string res;

    int s=max(a.length(),b.length());
    while((int)a.length()<s) a+='0';
    while((int)b.length()<s) b+='0';
    for(int i=0;i<s;i++){
        d+=(a[i]-'0')+(b[i]-'0');
        res+=char('0'+d%10);
        d/=10;
    }
    if(d) res+='1';
    return res;
}

bool cmp(string a,string b){
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    if((int)a.size()!=(int)b.size()) return (int)a.size()<(int)b.size();
    else return a<b;
}
string del(string a,string b){
    int d=0;
    string res;
    cout << a << ' ' << b << endl;
    while((int)b.size()<(int)a.size()) b+='0';
    for(int i=0;i<(int)a.size();i++){
        int k=(a[i]-'0')-(b[i]-'0')-d;d=0;
        if(k<0) k+=10,d=1;
        res+=char('0'+k);
    }
    assert(!d);
    while(res.back()=='0') res.pop_back();
    return res;
}

void solve(){
    int N=22,T=100;
    f[0][0][0][0]=1;
    for(int i=0;i<N;i++) for(int j=0;j<=i;j++) for(int a=0;a<=i;a++) for(int b=0;b<=i;b++){
        for(int x=-1;x<=1;x++) for(int y=0;y<=1;y++){
            int nj=j,na=a,nb=b,mul=1;
            if(x==0) nj++;
            else if(x==1) mul*=a,na--;
            else if(x==-1) nb++;

            if(y==0) mul*=b,nb--;
            else na++;

            if(na>=0 && nb>=0) f[i+1][nj][na][nb]+=f[i][j][a][b]*mul;
        }
    }

    string res="0";
    for(int i=0;i<=N;i++){
        for(int a=0;a<=N;a++){
            i128 cnt=f[N][i][a][0]*25*23*4;
            if(!cnt) continue;

            ld cur=0;
            
            string s;
            while(cnt){
                s+=char('0'+cnt%10);
                cnt/=10;
            }
            cout << s << '\n';
            for(int j=0;j<i;j++) s=mul(s,T-25-j);
            cout << '*' << s << '\n';
            res=add(res,s);
        }
    }
    cout << res << '\n';

    string dd="1";
    for(int i=76;i<=100;i++) dd=mul(dd,i);
    res="0000000000000"+res;

    string ans;
    for(int i=12;i>=0;i--){
        for(int k=9;k>=0;k--){
            int d=k;
            for(int j=0;j<i;j++) d*=10;
            string val=mul(dd,d);
            if(cmp(res,val)) continue;
            else{
                res=del(res,val);
                ans+=char('0'+k);
                break;
            }
        }
    }
    cout << ans << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
