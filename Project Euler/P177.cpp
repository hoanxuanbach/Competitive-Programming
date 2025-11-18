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

#define double long double

const double PI = acos(-1);
const double eps = 1e-9;
double sina[200],cosa[200];

void solve(){
    int res=0;
    for(int i=0;i<=180;i++){
        sina[i]=sin(i*PI/180);
        cosa[i]=cos(i*PI/180);
    }

    int cnt=0;
    set<vector<int>> S;
    for(int DAC=1;DAC<=45;DAC++) for(int BAC=DAC;BAC<=180-DAC*3;BAC++) for(int ABD=DAC;ABD<=180-DAC*2-BAC;ABD++) for(int CBD=DAC;CBD<=180-DAC-BAC-ABD;CBD++){
        int BCA=180-(BAC+ABD+CBD);
        int ADB=180-(DAC+BAC+ABD);
        double AC=sina[ABD+CBD]/sina[BCA];
        double AD=sina[ABD]/sina[ADB];
        double DC=sqrt(AC*AC+AD*AD-2*AC*AD*cosa[DAC]);
        double T=acos((AC*AC+DC*DC-AD*AD)/(2*AC*DC))*180/PI;
        int ACD=(int)(round(T));
        if(fabs(ACD-T)>eps) continue;
        int CDB=180-(DAC+ACD+ADB);
        if(min(ACD,CDB)<DAC) continue;

        //cnt++;
        int A=DAC+BAC;
        int B=ABD+CBD;
        int C=BCA+ACD;
        int D=ADB+CDB;

        vector<int> fAB={DAC,BAC,ABD,CBD};
        vector<int> fAD={BAC,DAC,ADB,CDB};
        vector<int> fBA={CBD,ABD,BAC,DAC};
        vector<int> fBC={ABD,CBD,BCA,ACD};
        vector<int> fCB={ACD,BCA,CBD,ABD};
        vector<int> fCD={BCA,ACD,CDB,ADB};
        vector<int> fDC={ADB,CDB,ACD,BCA};
        vector<int> fDA={CDB,ADB,DAC,BAC};

        if(fAB==min({fAB,fAD,fBA,fBC,fCB,fCD,fDC,fDA})) cnt++;
    }
    cout << cnt << '\n';
}
 
signed main(){  
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}
