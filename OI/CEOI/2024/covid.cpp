#include<bits/stdc++.h>
using namespace std;
int N,T;
double P;

int query(int l,int r){
    string s(N,'0');
    for(int i=l;i<r;i++) s[i]++;
    cout << "Q " << s << endl;
    char C;cin >> C;
    return (C=='P');
}
void answer(vector<int> &ans){
    string s(N,'0');
    for(int i=0;i<N;i++) if(ans[i]) s[i]++;
    cout << "A " << s << endl;
    char C;cin >> C;
    if(C=='W') exit(0);
}

void solve(){
    vector<int> ans(N);
    if(T==1){
        for(int i=0;i<N;i++) ans[i]=query(i,i+1);
        answer(ans);
        return;
    }
    int D=(int)(0.75/P);
    if(0.05<P && P<0.08) D=(int)(0.6/P);
    for(int i=0;i<N;){
        int x=min(N,i+D);
        if(!query(i,x)) i=x;
        else{
            int l=i,r=x;
            while(l+1<r){
                int m=(l+r)>>1;
                (query(i,m)?r:l)=m;
            }
            ans[l]=1,i=l+1;
        }
    }
    answer(ans);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> N >> P >> T;
    for(int i=0;i<T;i++) solve();
}
