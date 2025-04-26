#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
bool c[maxn];
void solve(){
    string a,b;int k;
    cin >> a >> b >> k;
    int d=0,id=-1,n=(int)a.length();
    for(int i=0;i<n;i++) c[i]=0;
    for(int i=0;i<n;i++){
        if(a[i]<b[i]){
            if(b[i]=='1' && k-d<=n-i-1) id=i;
            else if(b[i]!='1' && k-d<=n-i) id=i;
        }
        else{
            if(b[i]!='0' && k-d<=n-i && k-d>=1) id=i;
        }
        if(a[i]!=b[i]) d++;
        if(d>k) break;
    }
    if(id==-1){cout << -1 << '\n';return;}
    for(int i=0;i<id;i++){
        if(a[i]!=b[i]) k--;
        a[i]=b[i];
    }
    if(k==0) cout << a << '\n';
    else{
        if(a[id]!=char(b[id]-1)){a[id]=char(b[id]-1);k--;c[id]=1;}
        for(int i=id+1;i<n;i++){
            if(k==0) break;
            if(a[i]!='9'){k--;a[i]='9';c[i]=1;}
        }
        for(int i=n-1;i>=id+1;i--){
            if(k==0) break;
            if(c[i]==0){a[i]='8';k--;}
        }
        if(k>=1 && c[id]==0) a[id]=char(a[id]-1);
        cout << a << '\n';
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--) solve();
}
