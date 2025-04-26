#include<bits/stdc++.h>
using namespace std;
#define maxn 500005
#define int long long
int n,s,l[maxn],r[maxn],Min[maxn],ans,id,k,res;
deque<int> d;
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> n >> s;
    for(int i=1;i<n;i++) cin >> l[i] >> r[i];
    for(int i=n-1;i>=1;i--) Min[i]=Min[i+1]+min(l[i],r[i]);
    ans=LLONG_MAX;res=0;
    id=-1;k=-1;
    for(int i=1;i<s;i++){
        res+=l[i];
        if(i==n-1){
            if(res<ans){ans=res;id=0;k=i;}
        }
        else{
            if(res+r[i+1]+Min[i+2]<ans){
                ans=res+r[i+1]+Min[i+2];
                id=0;k=i;
            }
        }
        //cout << k << '\n';
    }
    res=0;
    for(int i=1;i<=n-s;i++){
        res+=r[i];
        if(i==n-1){
            if(res<ans){ans=res;id=1;k=i;}
        }
        else{
            if(res+l[i+1]+Min[i+2]<ans){
                ans=res+l[i+1]+Min[i+2];
                id=1;k=i;
            }
        }
    }
    int st=0,num=1;
    cout << ans << '\n';
    if(id==0){
        cout << s << ' ';
        for(int i=k;i>=1;i--) cout << i << ' ';
        if(k==n-1) return 0;
        for(int i=k+1;i<=n;i++){
            if(i!=s) d.push_back(i);
        }
        st=1;num=1;
    }
    else{
        cout << s << ' ';
        for(int i=n-k+1;i<=n;i++) cout << i << ' ';
        if(k==n-1) return 0;
        for(int i=1;i<=n-k;i++){
            if(i!=s) d.push_back(i);
        }
        st=0;num=1;
    }
    for(int i=k+2;i<n;i++){
        if(st!=(r[i]<=l[i])){
            if(st){
                for(int j=num;j>=1;j--) cout << d[(int)d.size()-j] << ' ';
                for(int j=num;j>=1;j--) d.pop_back();
            }
            else{
                for(int j=num;j>=1;j--) cout << d[j-1] << ' ';
                for(int j=num;j>=1;j--) d.pop_front();
            }
            st^=1;num=1;
        }
        else num++;
    }
    if(st){
        for(int j=num;j>=1;j--) cout << d[(int)d.size()-j] << ' ';
        for(int j=num;j>=1;j--) d.pop_back();
    }
    else{
        for(int j=num;j>=1;j--) cout << d[j-1] << ' ';
        for(int j=num;j>=1;j--) d.pop_front();
    }
}
