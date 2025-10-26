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

vector<string> P={"hello"};

void solve(){
    string S;getline(cin,S);
    vector<int> ss;

    string cur;
    for(char c:S){
        if(c>='0' && c<='9') cur+=c;
        else{
            if(!cur.empty()) ss.push_back(stoi(cur));
            cur.clear();
        }
    }
    if(!cur.empty()) ss.push_back(stoi(cur));
    //for(int x:ss) cout << x << '\n';


    for(int x='a';x<='z';x++) for(int y='a';y<='z';y++) for(int z='a';z<='z';z++){
        vector<int> T={x,y,z};

        string X;
        bool the=false,ad=false,one=false;
        for(int i=0;i<(int)ss.size();i++){
            int val=ss[i]^T[i%3];
            X+=char(val);
        }
        //if(!check) continue;
        for(int i=2;i<(int)ss.size();i++){
            if(X[i-2]=='t' && X[i-1]=='h' && X[i]=='e') the=true;
            if(X[i-2]=='a' && X[i-1]=='n' && X[i]=='d') ad=true;
            if(X[i-2]=='o' && X[i-1]=='n' && X[i]=='e') one=true;
        }
        if(the && ad && one){
            int total=0;
            for(char c:X) total+=c;
            cout << total << '\n';   
        }
    }
}
 
signed main(){
    freopen("59.txt","r",stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
