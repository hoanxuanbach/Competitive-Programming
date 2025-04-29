#include<bits/stdc++.h>
using namespace std;
#define maxn 100005
#define int long long
int n,a[maxn],b[maxn],ans,sum,k,l;
multiset<int> s1,s2;
signed main(){
    //ios_base::sync_with_stdio(false);
    //cin.tie(NULL);
    cin >> n;
    for(int i=1;i<=n;i++){cin >> a[i];a[i]+=a[i-1];}
    for(int i=1;i<=n;i++) cin >> b[i];
    cin >> k >> l;
    for(int i=n-k+1;i<=n;i++) s1.insert(b[i]);
    for(int i=1;i<=l;i++){
        sum+=*s1.rbegin();
        s2.insert(*s1.rbegin());
        s1.erase((--s1.end()));
    }
    ans=sum+a[n]-a[n-k];
    for(int i=1;i<=k;i++){
        if(s1.find(b[n-k+i])!=s1.end()) s1.erase(s1.find(b[n-k+i]));
        else{s2.erase(s2.find(b[n-k+i]));sum-=b[n-k+i];}
        if((int)s2.size()==l){
            if(b[i]>*s2.begin()){
                s1.insert(*s2.begin());sum-=*s2.begin();
                s2.erase(s2.begin());s2.insert(b[i]);sum+=b[i];
            }
            else s1.insert(b[i]);
        }
        else{
            if(b[i]>*s1.rbegin()){s2.insert(b[i]);sum+=b[i];}
            else{
                sum+=*s1.rbegin();s2.insert(*s1.rbegin());
                s1.erase((--s1.end()));s1.insert(b[i]);
            }
        }
        ans=max(ans,sum+a[i]+a[n]-a[n-k+i]);
    }
    cout << ans << '\n';
}
