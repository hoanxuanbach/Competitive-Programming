#include<bits/stdc++.h>
using namespace std;

int cnt[60],num;
int f(char c){
    if(c>='a' && c<='z') return c-'a';
    else return 26+c-'A';
}
void add(int x,int val){
    num-=!cnt[x];
    cnt[x]+=val;
    num+=!cnt[x];
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m,total=0;
    string s,t;
    cin >> n >> m >> s >> t;
    for(char c:s) cnt[f(c)]++;
    for(int i=0;i<n;i++) cnt[f(t[i])]--;
    for(int i=0;i<52;i++) num+=!cnt[i];
    if(num==52) total++;
    for(int i=n;i<m;i++){
        add(f(t[i]),-1);
        add(f(t[i-n]),1);
        total+=(num==52);
    }
    cout << total << '\n';
}
