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

map<string,char> mp;
void init(){
    mp["UUU"]=mp["UUC"]='F';
    mp["UUA"]=mp["UUG"]=mp["CUU"]=mp["CUC"]=mp["CUA"]=mp["CUG"]='L';
    mp["AUU"]=mp["AUC"]=mp["AUA"]='I';
    mp["AUG"]='M';
    mp["GUU"]=mp["GUC"]=mp["GUA"]=mp["GUG"]='V';
    mp["UCU"]=mp["UCC"]=mp["UCA"]=mp["UCG"]=mp["AGU"]=mp["AGC"]='S';

    vector<pair<string,char>> cc;
    cc.push_back({"CCU CCC CCA CCG",'P'});
    cc.push_back({"ACU ACC ACA ACG",'T'});
    cc.push_back({"GCU GCC GCA GCG",'A'});
    cc.push_back({"UAU UAC",'Y'});
    cc.push_back({"CAU CAC",'H'});
    cc.push_back({"CAA CAG",'Q'});
    cc.push_back({"AAU AAC",'N'});
    cc.push_back({"AAA AAG",'K'});
    cc.push_back({"GAU GAC",'D'});
    cc.push_back({"GAA GAG",'E'});
    cc.push_back({"UGU UGC",'C'});
    mp["UGG"]='W';
    cc.push_back({"CGU CGC CGA CGG AGA AGG",'R'});
    cc.push_back({"GGU GGC GGA GGG",'G'});
    cc.push_back({"UAA UAG UGA",'.'});

    for(auto [S,ch]:cc){
        string cur;
        for(char x:S){
            if(x==' '){
                mp[cur]=ch;
                cur.clear();
            }
            else cur+=x;
        }
        if(!cur.empty()) mp[cur]=ch;
    }
}

void solve(){
    string S,res;cin >> S;
    for(int i=0;i+2<(int)S.size();i+=3){
        char add=mp[S.substr(i,3)];
        if(add=='.') break;
        res+=add;
    }
    cout << res << '\n';
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    init();
    int test=1;cin >> test;
    while(test--) solve();
}
