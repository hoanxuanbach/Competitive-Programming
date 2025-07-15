#include <bits/stdc++.h>
#include "avian.h"
using namespace std;
const int maxn = 1005;

bitset<maxn> change(string s){
    bitset<maxn> res;
    for(int i=0;i<(int)s.length();i++) res[i]=s[i]-'0';
    return res;
}
vector<string> f(int N,vector<bitset<maxn>> X){
    vector<string> res((int)X.size());
    for(int i=0;i<(int)X.size();i++){
        for(int j=0;j<N;j++) res[i]+=char(X[i][j]+'0');
        //cout << res[i] << endl;
    }
    return res;
}
bitset<maxn> g(int N,bitset<maxn> a,bitset<maxn> b){
    bitset<maxn> res;
    for(int i=0;i<N;i++) res[i]=a[i]^b[i]^((i&1)?b[(i+1)%N]:a[(i+1)%N]);
    return res;
}

vector<string> encode(int C, int K, int N, string X) {
    bitset<maxn> a,b,c;
    a=change(X.substr(0,N));
    b=change(X.substr(N,N));
    if(C==3) c=change(X.substr(2*N,N));

    if(C==3 && K==4) return f(N,{a,b,c,a^b^c});
    else if(C==2 && K==4) return f(N,{a,b,a^b,g(N,a,b)});
    else return f(N,{a^c,b^c,a^b^c,g(N,a,b),c});
}
vector<bitset<maxn>> h(int N,vector<bitset<maxn>> Y,vector<bool> c){
    if(c[3]){
        if(c[0]){
            for(int i=0;i<N;i+=2) Y[1][i]=Y[3][i]^Y[0][i]^Y[0][(i+1)%N];
            for(int i=1;i<N;i+=2) Y[1][i]=Y[3][i]^Y[0][i]^Y[1][(i+1)%N];
        }
        else if(c[1]){
            for(int i=1;i<N;i+=2) Y[0][i]=Y[3][i]^Y[1][i]^Y[1][(i+1)%N];
            for(int i=0;i<N;i+=2) Y[0][i]=Y[3][i]^Y[1][i]^Y[0][(i+1)%N];
        }
        else{
            for(int i=0;i<N;i++) Y[i&1][(i+1)%N]=Y[3][i]^Y[2][i];
            for(int i=0;i<N;i++) Y[(i&1)^1][(i+1)%N]=Y[2][(i+1)%N]^Y[i&1][(i+1)%N];
        }
    }
    else if(c[2]){
        if(c[0]) Y[1]=Y[2]^Y[0];
        else Y[0]=Y[2]^Y[1];
    }
    return {Y[0],Y[1]};
}

string decode(int C, int K, int N, vector<string> Y2, vector<int> I) {
    vector<bitset<maxn>> X(C),Y(K);
    vector<bool> c(K,false);
    for(int i=0;i<C;i++){
        Y[I[i]]=change(Y2[i]);
        c[I[i]]=true;
    }

    if(C==3 && K==4){
        int pos=0;
        bitset<maxn> cur;
        for(int i=0;i<K;i++){
            if(c[i]) pos^=i,cur^=Y[i];
        }
        for(int i=0;i<K;i++){
            if(c[i] && i<=2) X[i]=Y[i];
            else if(pos<=2) X[pos]=cur;
        }
        //cout << pos << endl;
    }
    else if(C==2 && K==4) X=h(N,Y,c);
    else{
        if(c[4]){
            bitset<maxn> cur=Y[4];
            Y.pop_back();c.pop_back();
            for(int i=0;i<K-1;i++) if(c[i] && i<=2) Y[i]^=cur;
            X=h(N,Y,c);X.push_back(cur);
        }
        else if(c[3]){
            if(c[0] && c[1]) Y[2]=Y[0]^Y[1];
            else if(c[0] && c[2]) Y[1]=Y[2]^Y[0];
            else Y[0]=Y[1]^Y[2];
            for(int i=0;i<3;i++) c[i]=!c[i];
            X=h(N,Y,c);
            if(!c[0]) X.push_back(Y[0]^X[0]);
            else if(!c[1]) X.push_back(Y[1]^X[1]);
        }
        else X={Y[1]^Y[2],Y[0]^Y[2],Y[0]^Y[1]^Y[2]};
    }

    vector<string> X2=f(N,X);
    string res;
    for(int i=0;i<C;i++) res+=X2[i];
	return res;
}