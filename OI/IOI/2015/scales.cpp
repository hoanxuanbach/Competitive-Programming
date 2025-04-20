#include "scales.h"
#include<bits/stdc++.h>
using namespace std;

const int S[]={1,3,9,27,81,243,729};

struct Query{
    int a=0,b=0,c=0,d=0;
    Query(int a=0,int b=0,int c=0,int d=0):a(a),b(b),c(c),d(d){}
    void check(){
        assert(a*b*c*d);
    }
    int ask(){
        int x;
        if(a==d) x=getHeaviest(a,b,c);
        else if(b==d) x=getLightest(a,b,c);
        else if(c==d) x=getMedian(a,b,c);
        else x=getNextLightest(a,b,c,d);
        return (a==x)+(b==x)*2+(c==x)*3;
    }

    int get(vector<int> p){
        int x=min({p[a],p[b],p[c]}),z=max({p[a],p[b],p[c]}),y=p[a]^p[b]^p[c]^x^z;
        auto f = [&](int k){return (p[a]==k)+(p[b]==k)*2+(p[c]==k)*3;};
        if(a==d) return f(z);
        else if(b==d) return f(x);
        else if(c==d) return f(y);
        else if(z<p[d] || x>p[d]) return f(x);
        else if(y>p[d]) return f(y);
        else return f(z);
    }
};

vector<Query> Q;
int W[6];
struct State{
    vector<vector<int>> p;
    Query q;
    State* nxt[4];
    void add(vector<int> x){
        p.push_back(x);
    }
    bool build(int k){
        if(!k || (int)p.size()<=1) return true;
        k--;
        for(auto cc:Q){
            vector<int> cnt(4);
            for(auto x:p) if(++cnt[cc.get(x)]>S[k]) break;
            if(max({cnt[1],cnt[2],cnt[3]})>S[k]) continue;

            bool ok=true;
            for(int i=1;i<=3;i++) nxt[i] = new State();
            for(auto x:p) nxt[cc.get(x)]->add(x);
            for(int i=1;i<=3;i++) ok&=nxt[i]->build(k);
            if(ok){
                q=cc;
                return true;
            }
        }
        return false;
    }
    void get(){
        if((int)p.size()<=1){
            for(int i=0;i<6;i++) W[p[0][i+1]-1]=i+1;
            answer(W);
            return;
        }
        nxt[q.ask()]->get();
    }
};
State* root;

void init(int T){
    for(int a=1;a<7;a++) for(int b=a+1;b<7;b++) for(int c=b+1;c<7;c++) for(int d=1;d<7;d++) Q.push_back(Query(a,b,c,d));
    root=new State();
    vector<int> c(7);
    iota(c.begin(),c.end(),0);
    do{
        if(c[0]) break;
        root->add(c);
    }while(next_permutation(c.begin(),c.end()));
    root->build(6);
}

void orderCoins() {
    root->get();
}
