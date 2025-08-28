#include<bits/stdc++.h>
#include<ext/rope>
using namespace __gnu_cxx;
using namespace std;

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    crope r="";
    int t,k=0;cin >> t;
    while(t--){
        int n;string s;cin >> s;
        if(s=="Move") cin >> k;
        else if(s=="Insert"){
            cin >> n;
            string add;crope cr;
            while((int)cr.size()<n){
                getline(cin,add);
                for(char c:add) cr.push_back(c);
            }
            r.insert(k,cr);
        }
        else if(s=="Delete"){cin >> n;r.erase(k,n);}
        else if(s=="Get"){
            cin >> n;crope cr=r.substr(k,n);
            cout << cr << '\n';
        }
        else if(s=="Prev") k--;
        else k++;
    }
}