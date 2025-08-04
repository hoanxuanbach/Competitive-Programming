#include "migrations.h"
#include <bits/stdc++.h>
using namespace std;

vector<int> S = {33,9,5,3,3};
vector<int> K = {140,20,6,2,2};
vector<int> M = {9828,438,69,20,9};
vector<int> T = {9827,9967,9987,9993,9995};

int ptr=0;
pair<int,int> ret;
vector<int> A,B;

vector<vector<int>> G;

int get_far(int s,int N){
    vector<int> d(N,-1);
    queue<int> q;q.push(s);d[s]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int v:G[u]) if(d[v]==-1) q.push(v),d[v]=d[u]+1;
    }
    return max_element(d.begin(),d.end())-d.begin();
}

pair<int,int> get_diameter(int N){
    int u=get_far(0,N);
    int v=get_far(u,N);
    if(u>v) swap(u,v);
    return {u,v};
}

void init(){
    G.push_back({});
    A.push_back(0);
    B.push_back(0);
    ret={-1,-1};
}

vector<int> sub(vector<int> &v,int x,int k){
    int l=x*k,r=min((x+1)*k,(int)v.size());
    return vector<int>(v.begin()+l,v.begin()+r);
}

int f(vector<int> &v,int x){
    for(int i=0;i<(int)v.size();i++) if(v[i]==x) return i;
    return -1;
}

bool eq(pair<int,int> a,pair<int,int> b){
    if(a==b) return true;
    swap(a.first,a.second);
    return (a==b);
}

vector<vector<int>> T0 = {{0,1,4,5,6},{1,0,8,7,6},{4,5,2,3,8},{2,3,8,7,6},{8,3,5,6,7}};
vector<vector<int>> T1 = {{0,1,2},{0,1,3},{0,5,4},{2,3,5},{0,1,5}};
vector<vector<int>> T2 = {{0,2},{1,2},{0,3},{1,3},{2,3}};

int send_message(int N, int i, int p) {
    if(i==1) init();
    
    G.push_back({p});
    G[p].push_back(i);
    if(i<N-3) A.push_back(i),B.push_back(i);

    if(i==T[ptr]){
        auto [u,v]=get_diameter(N);
        if(f(A,u)==-1 || f(B,v)==-1) swap(u,v);
        u=f(A,u),v=f(B,v);
        assert(u!=-1 && v!=-1);
        int X=(M[ptr]-1)/S[ptr]+1;
        u/=X,v/=X;
        A=sub(A,u,X),B=sub(B,v,X);

        int val;
        if(!ptr) val=S[ptr]*u-u*(u-1)/2+v-u;
        else val=u*S[ptr]+v;
        if(val) val--,ret={i+val/4,val%4+1};
        ptr++;
    }

    if(i==ret.first) return ret.second;
    if(i==N-3){
        while((int)A.size()<4) A.push_back(0);
        while((int)B.size()<4) B.push_back(0);
        A.insert(A.end(),B.begin(),B.end());B.clear();
        A.push_back(i);
        auto P=get_diameter(N);
        for(int x=0;x<=4;x++){
            B.clear();
            for(int j:T0[x]) B.push_back(A[j]);

            bool ok=false;
            for(int j=0;j<=1;j++) for(int k=2;k<=4-j;k++) if(eq(P,{B[j],B[k]})) ok=true;
            if(ok){
                A=B;
                return x;
            }
        }
        assert(false);
    }
    if(i==N-2){
        A.push_back(i);
        auto P=get_diameter(N);
        for(int x=0;x<=4;x++){
            B.clear();
            for(int j:T1[x]) B.push_back(A[j]);
            
            bool ok=false;
            for(int j=0;j<=1;j++) if(eq(P,{B[j],B[2]})) ok=true;
            if(ok){
                A=B;
                return x;
            }
        }
        assert(false);
    }
    if(i==N-1){
        A.push_back(i);
        auto P=get_diameter(N);
        for(int x=0;x<=4;x++){
            pair<int,int> Q = {A[T2[x][0]],A[T2[x][1]]};
            if(eq(P,Q)) return x;
        }
        assert(false);
    }
    return 0;
}

pair<int,int> longest_path(vector<int> C){

    int N=(int)C.size(),lst=0;

    ptr=0;
    A.clear();B.clear();
    while(ptr<(int)T.size()){
        for(int i=lst;i<=T[ptr];i++) A.push_back(i),B.push_back(i);

        int i=T[ptr],val=0;
        for(int j=0;j<K[ptr];j++) if(C[i+j]) val=j*4+C[i+j]; 

        int u=0,v=0;
        if(!ptr){
            while(val>=(S[ptr]-u)) val-=(S[ptr]-u),u++;
            v=u+val;
        }
        else u=val/S[ptr],v=val%S[ptr];
        int X=(M[ptr]-1)/S[ptr]+1;
        A=sub(A,u,X);B=sub(B,v,X);
        lst=T[ptr]+1;
        ptr++;
    }

    A.push_back(lst);
    B.push_back(lst);
    while((int)A.size()<4) A.push_back(0);
    while((int)B.size()<4) B.push_back(0);
    A.insert(A.end(),B.begin(),B.end());B.clear();

    A.push_back(N-3);
    B.clear();
    for(int j:T0[C[N-3]]) B.push_back(A[j]);
    A=B;

    A.push_back(N-2);    
    B.clear();
    for(int j:T1[C[N-2]]) B.push_back(A[j]);
    A=B;

    A.push_back(N-1);
    int x=C[N-1];
    return {A[T2[x][0]],A[T2[x][1]]};
}

