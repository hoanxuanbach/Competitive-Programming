#include<bits/stdc++.h>
using namespace std;
int num[2],check=0;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int n;cin >> n;string s;num[0]=num[1]=n/2;
    for(int i=1;i<=n;i++){
        int a;cin >> a;
        if(a%3==0){
            if(num[0]>0) s.push_back('0');
            else{check=2;s.push_back('1');}
        }
        else{
            if(num[1]>0) s.push_back('1');
            else s.push_back('0');
        }
        num[s.back()-'0']--;
    }
    cout << check << '\n' << s << '\n';
}
