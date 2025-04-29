#include<bits/stdc++.h>
using namespace std;
int num[30];
bool check[30];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n,a,s1=0,s2=0;cin >> n;
    cin >> s1 >> a;a=min(a,10);s1=min(s1,10);
    num[a]++;num[s1]++;s1+=a;
    cin >> s2 >> a;a=min(a,10);s2=min(s2,10);
    num[a]++;num[s2]++;s2+=a;
    for(int i=1;i<=n;i++){
        cin >> a;a=min(a,10);num[a]++;
        s1+=a;s2+=a;
    }
    for(int i=1;i<=9;i++){
        if(num[i]!=4) check[i]=true;
    }
    if(num[10]!=16) check[10]=true;
    if(s1<=s2){
        if(check[23-s2]) cout << 23-s2 << '\n';
        else cout << -1 << '\n';
    }
    else{
        for(int i=24-s1;i<=23-s2;i++){
            if(check[i]){
                cout << i << '\n';
                return 0;
            }
        }
        cout << -1 << '\n';
    }
}
