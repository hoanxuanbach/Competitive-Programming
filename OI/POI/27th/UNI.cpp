#include<bits/stdc++.h>
using namespace std;
#define int long long
int sa,sb,cur,total=0;
int g(int l,int r){
    if(cur<0) return 0;
    if(l>=r) return 0;
    if(((l>>cur)&1)==0 && ((r>>cur)&1)==1){
        cur--;
        return (1LL<<(cur+1))+g(l,r-(1LL<<(cur+1)));
    }
    else if(((l>>cur)&1)==0 && ((r>>cur)&1)==0){cur--;return g(l,r);}
    else {cur--;return g(l-(1LL<<(cur+1)),r-(1LL<<(cur+1)));}
}
int cal(int l,int r){
    if(l==0 || r==0) return 0;
    int res=((sa^sb)>>cur)<<cur;
    sb&=((1LL<<cur)-1);
    sa&=((1LL<<cur)-1);
    cur--;res+=g(sb,sa);
    return res;
}
int f(int a,int b,int l,int r){
    if(a>b){total=cal(l,r);return 0;}
    int pa=a/2+(a&1),pb=b/2-((b&1)^1),res=pb-pa+1;
    if(pa*2>a){
        if(l!=0) res++;
        l+=(1LL<<cur);
    }
    if(pb*2+1<b){
        if(r!=0) res++;
        r+=(1LL<<cur);
    }
    cur++;
    res+=f(pa,pb,l,r)*2;
    return res;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int t;cin >> t;
    while(t--){
        cin >> sa >> sb;cur=0;total=0;
        cout << total+f(sa,sb,0,0) << '\n';
    }
}
