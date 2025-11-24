#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int,int> 
const int maxn = 2e5+5;
const int mod = 998244353;
#define i128 __int128

int m,P;
void calP(){
    int M=2*m;
    vector<int> f(M);
    for(int i=2;i<M;i++) if(!f[i]){
        if(i>=m){
            P=i;
            return;
        }
        for(int j=i*i;j<M;j+=i) f[j]=1;
    }
}

void encode(){
    int X;cin >> X;X--;
    vector<int> A(3*m);
    for(int i=0;i<3*m;i++) A[i]=i%m+1;
    rotate(A.begin()+m,A.begin()+m+P-X,A.begin()+m+P);
    for(int i=0;i<3*m;i++) cout << A[i] << ' ';
    cout << '\n';
    return;
}
void decode(){
    vector<int> A(3*m);
    for(int i=0;i<3*m;i++) cin >> A[i];
    vector<int> B(3*P);
    for(int i=0;i<P;i++) B[i]=A[i%m];
    for(int i=0;i<P;i++) B[2*P+i]=B[P+i]=A[m+i];

    vector<int> z(3*P);
    int l=1,r=0;
    for(int i=1;i<3*P;i++){
        if(i<=r) z[i]=min(r-i+1,z[i-l]);
        while(i+z[i]<3*P && B[z[i]]==B[i+z[i]]) z[i]++;
        if(i+z[i]-1>r) l=i,r=i+z[i]-1;
    }
    for(int i=0;i<P;i++){
        if(z[P+i]>=P){
            cout << i+1 << '\n';
            return;
        }
    }
}

void solve(){
    int T,n;cin >> T >> n >> m;
    calP();
    for(int i=1;i<=n;i++){
        if(T==1) encode();
        else decode();
    }
}
 
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}