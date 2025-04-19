#include "shopping.h"
#include <bits/stdc++.h>
using namespace std;

namespace Anna{
    const int maxn = 1e4+5;
    const int D = 13;
    int Q = 18;
    int sz,pos,nxt,T[maxn];
    int l,r,s,t,d;
    int N,L,R;
    int f(int x){return (x==1?0:32-__builtin_clz(x-1));}
    string get(int k,int d){
        string S;
        if(d==0) S+="000";
        else if(d==1) S+="001";
        else for(int i=3;i>=0;i--) S+=char('0'+((d+2)>>i&1));
        for(int i=d-1;i>=0;i--) S+=char('0'+(k>>i&1));
        return S;
    }
    void InitA(){
        l=0,r=N;
        int k=1;
        while(d<D){
            int m=(l+r)>>1;
            if(R<m) r=m,k<<=1;
            else if(m<L) l=m+1,k=k<<1|1;
            else break;
            d++;
        }
        //cout << "Anna " << l << ' ' << r << ' ' << k << ' ' << d << '\n';
        string S=get(k,d);
        for(int i=0;i<(int)S.size();i++) SendA(S[i]-'0');
        Q-=(int)S.size();
        int m=(l+r)>>1;
        s=t=m;sz=pos=0;
        if(d<D && (r-l)>=2) nxt=f(s-l+1);
        else nxt=-1;
    }
    void ReceiveA(bool x) {
        T[sz++]=x;
        while(sz==nxt){
            Q--;
            int k=f(s-l+1),p=0;
            for(int i=0;i<k;i++) p|=T[pos++]<<i;
            p+=l;
            int a=t-s,b=r-l;
            int m=(a+b-1)>>1;
            int q=p+m+1;
            //cout << "ReceiveA " << p << ' ' << q << '\n';
            if(p<=L && R<q){
                //cout << 1 << '\n';
                SendA(1);
                l=p,r=q;
            }
            else{
                //cout << 0 << '\n';
                SendA(0);
                s=p,t=q;
            }
            //cout << "ReceiveA " << l << ' ' << r << ' ' << s << ' ' << t << '\n';
            if(Q>0 && (s-l)+(r-t)>=2) nxt=sz+f(s-l+1);
            else nxt=-1;
        }
    }
    int Answer(){
        int p=-1;
        if(s!=t){
            int k=f(t-s);p=s;
            for(int i=0;i<k;i++) p+=T[pos++]<<i;
        }
        vector<int> ord;
        for(int i=l;i<s;i++) ord.push_back(i);
        if(p!=-1) ord.push_back(p);
        for(int i=t;i<r;i++) ord.push_back(i);
        vector<int> st;
        st.push_back(ord[0]);
        int lst=1,ret=-1;
        if(L<=ord[0] && ord[0]<=R) ret=ord[0];
        while(pos<sz){
            if(ret==-1 && L<=ord[lst] && ord[lst]<=R) ret=ord[lst];
            if(T[pos++]) st.push_back(ord[lst++]);
            else{
                int x=st.back();st.pop_back();
                if(L<=ord[lst] && ord[lst]<=R && ret==x) ret=ord[lst];
            }
        }
        return ret;
    }
}

void InitA(int N, int L, int R) {
    Anna::N = N;Anna::L = L;Anna::R = R;
    Anna::InitA();
}
void ReceiveA(bool x){
    Anna::ReceiveA(x);
}

int Answer(){
    return Anna::Answer();
}
namespace Bruno{
    const int maxn = 1e6+5;
    const int D = 13;
    int Q = 18;
    int N,sz=0,pos=0,T[maxn];
    int l=-1,r=-1,s,t,d=-1,k=-1;
    int f(int x){return (x==1?0:32-__builtin_clz(x-1));}
    vector<int> P,ord;
    void InitB(){
        l=r=d=k=-1;
        sz=pos=0;
    }
    void ReceiveB(bool y) {
        T[sz++]=y;
        if(d==-1){
            int cc=0;
            for(int i=0;i<sz;i++) cc=cc<<1|T[i];
            if(sz==3 && cc<=1) d=cc;
            else if(sz==4) d=cc-2;
        }
        if(d==-1) return;
        if(k==-1){
            pos=3+(d>1);
            if(sz==pos+d){
                k=1;
                for(int i=0;i<d;i++) k=k<<1|T[pos+i];
                pos=sz;
            }
        }
        if(k==-1) return;
        if(l==-1){
            l=0,r=N;
            for(int i=d-1;i>=0;i--){
                int m=(l+r)>>1;
                if(k>>i&1) l=m+1;
                else r=m;
            }
            int m=(l+r)>>1;
            ord.push_back(m);
            int a=m-1,b=m+1;
            while(a>=l || b<r){
                if(a<l || (b<r && P[b]>=P[a])) ord.push_back(b++);
                else ord.push_back(a--);
            }
            s=t=m;
            //cout << "Bruno " << l << ' ' << r << ' ' << k << ' ' << d << '\n';
        }
        if(pos<sz){
            int a=t-s,b=r-l;
            int m=(a+b-1)>>1;
            //cout << "ReceiveB " << pos << ' ' << T[pos] << '\n';
            if(T[pos++]){
                if(ord[m]<=s) l=ord[m],r=l+m+1;
                else r=ord[m]+1,l=r-m-1;
            }
            else{
                if(ord[m]<=s) s=ord[m],t=s+m+1;
                else t=ord[m]+1,s=t-m-1;
            }
            //cout << "ReceiveB " << l << ' ' << r << ' ' << s << ' ' << t << '\n';
        }
        if(d<D && sz<Q && (s-l)+(r-t)>=2){
            int a=t-s,b=r-l;
            int m=(a+b-1)>>1;
            int p=ord[m]-(ord[m]>s)*m-l;
            for(int i=0;i<f(s-l+1);i++) SendB(p>>i&1);
            //cout << "SendB " << p << '\n';
        }
        else{
            int c=s;
            if(s<t){
                for(int i=s;i<t;i++) if(P[i]<P[c]) c=i;
                for(int i=0;i<f(t-s);i++) SendB((c-s)>>i&1);
            }
            vector<int> v;
            for(int i=l;i<s;i++) v.push_back(i);
            if(s<t) v.push_back(c);
            for(int i=t;i<r;i++) v.push_back(i);
            vector<int> st;
            st.push_back(v[0]);
            for(int i=1;i<(int)v.size();i++){
                int x=v[i];
                while(!st.empty() && P[st.back()]>P[x]) st.pop_back(),SendB(0);
                st.push_back(x);SendB(1);
            }
        }
    }
}

void InitB(int N, std::vector<int> P) {
    Bruno::N=N;Bruno::P=P;
    Bruno::InitB();
}
void ReceiveB(bool y){
    Bruno::ReceiveB(y);
}
