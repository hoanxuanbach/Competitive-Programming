#include "ancient2.h"

#include<bits/stdc++.h>
using namespace std;
const int maxn=1005;
int n;
bitset<maxn> bs[maxn],cur;
bool ok[maxn];

bool add(int t=1){
    for(int i=n;i>=1;i--){
        if(cur[i]){
            if(!ok[i]){
                if(t) bs[i]=cur,ok[i]=true;
                return true;
            }
            else cur^=bs[i];
        }
    }
    return false;
}
void cal_first(int x){
    for(int i=0;i<x;i++){
        cur.reset();
        vector<int> a(i+3),b(i+3);
        for(int j=0;j<i;j++) a[j]=b[j]=j+1;
        a[i]=i+1;b[i]=i+2;
        a[i+1]=b[i+1]=i+1;
        a[i+2]=b[i+2]=i+2;
        int d=Query(i+3,a,b)-i-1;
        cur[i+1]=1;cur[0]=d;
        add();
    }
}
bool check(string s){
    int sz=(int)s.size();
    vector<int> kmp(sz+1,-1);
    vector<int> a(sz+1),b(sz+1);
    for(int i=1;i<=sz;i++){
        int j=kmp[i-1];
        while(j>=0 && s[j]!=s[i-1]) j=kmp[j];
        kmp[i]=j+1;
    }
    vector<vector<int>> nxt(sz+1,vector<int>(2,0));
    for(int i=0;i<=sz;i++){
        int j=kmp[i];
        for(int k=0;k<2;k++){
            if(i<sz && (s[i]-'0')==k) nxt[i][k]=i+1;
            else if(j!=-1) nxt[i][k]=nxt[j][k];
        }
        a[i]=nxt[i][0];b[i]=nxt[i][1];
    }

    if(Query(sz+1,a,b)!=sz) return false;
    else return true;
}
void cal_last(int x){
    string s;
    for(int i=n;i>n-x;i--){
        s='0'+s;
        if(!check(s)) s[0]='1';
        cur.reset();
        cur[i]=1;cur[0]=s[0]-'0';
        add();
    }
}
void cal_mid(int x){
    for(int i=1;i<=51;i++){
        for(int j=0;j<i;j++){
            cur.reset();
            for(int k=0;k<n;k++) if(k%i==j) cur[k+1]=1;
            if(!add(0)) continue;

            cur.reset();
            for(int k=0;k<n;k++) if(k%i==j) cur[k+1]=1;

            vector<int> a(2*i),b(2*i);
            for(int k=0;k<i;k++){
                if(k!=j){
                    a[k]=b[k]=(k+1)%i;
                    a[i+k]=b[i+k]=i+(k+1)%i;
                }
                else{
                    a[k]=b[i+k]=(k+1)%i;
                    b[k]=a[i+k]=i+(k+1)%i;
                }
            }
            int d=Query(2*i,a,b);
            //cout << i << ' ' << j << ' ' << (d>=i) << '\n';
            cur[0]=(d>=i);
            add();x--;
            if(x==0) return;
        }
    }
}
string Solve(int N) {
    n=N;
    cal_first(100);
    cal_last(101);
    cal_mid(799);
    string res;
    for(int i=1;i<=N;i++){
        cur.reset();cur[i]=1;
        for(int j=i;j>=1;j--) if(cur[j]) cur^=bs[j];
        int d=cur[0];
        res+=char('0'+d);
    }
    return res;
}
