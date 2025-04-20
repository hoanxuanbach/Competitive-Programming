#include "abc.h"
#include <bits/stdc++.h>
using namespace std;
#define mpp make_pair
#define pii pair<int,int>
#define se second
#define fi first
#define pb push_back
const int T = 1024;
// you may find the definitions useful
const int OP_ZERO    = 0;  // f(OP_ZERO,    x0, x1) = 0
const int OP_NOR     = 1;  // f(OP_NOR,     x0, x1) = !(x0 || x1)
const int OP_GREATER = 2;  // f(OP_GREATER, x0, x1) = (x0 > x1)
const int OP_NOT_X1  = 3;  // f(OP_NOT_X1,  x0, x1) = !x1
const int OP_LESS    = 4;  // f(OP_LESS,    x0, x1) = (x0 < x1)
const int OP_NOT_X0  = 5;  // f(OP_NOT_X0,  x0, x1) = !x0
const int OP_XOR     = 6;  // f(OP_XOR,     x0, x1) = (x0 ^ x1)
const int OP_NAND    = 7;  // f(OP_NAND,    x0, x1) = !(x0 && x1)
const int OP_AND     = 8;  // f(OP_AND,     x0, x1) = (x0 && x1)
const int OP_EQUAL   = 9;  // f(OP_EQUAL,   x0, x1) = (x0 == x1)
const int OP_X0      = 10; // f(OP_X0,      x0, x1) = x0
const int OP_GEQ     = 11; // f(OP_GEQ,     x0, x1) = (x0 >= x1)
const int OP_X1      = 12; // f(OP_X1,      x0, x1) = x1
const int OP_LEQ     = 13; // f(OP_LEQ,     x0, x1) = (x0 <= x1)
const int OP_OR      = 14; // f(OP_OR,      x0, x1) = (x0 || x1)
const int OP_ONE     = 15; // f(OP_ONE,     x0, x1) = 1

int encode(string s){
    int x=0,p=1;
    for(char c:s) x=x*26+(c-'a');
    for(int i=1;i<s.size();i++) x+=(p*=26);
    return x;
}

vector<int> get(vector<int> a){
    int n=a.size();
    if(n<=1) return {};
    //cout << n << endl;
    //for(int x:a) cout << x << ' ';
    //cout << endl;
    vector<int> al(a.begin(),a.begin()+n/2),ar(a.begin()+n/2,a.end());
    vector<int> p(n),s(n/2,-1),t(n/2,-1);
    vector<vector<pii>> adj(n);

    for(int i=0;i<n;i++) p[a[i]]=i;
    for(int i=0;i<n/2;i++){
        int x=p[i],y=p[i+n/2];
        if((n&1) && max(x,y)==n-1) continue;
        int u=(x<n/2?x:x-n/2);
        int v=(y<n/2?y:y-n/2);
        int w=(x<n/2)^(y<n/2)^1;
        adj[u].pb({v,w});
        adj[v].pb({u,w});
    }
    function<void(int)> dfs = [&](int u){
        for(auto [v,w]:adj[u]) if(s[v]==-1){
            s[v]=s[u]^w;
            return dfs(v);
        }
    };
    if((n&1) && p[n-1]!=n-1){
        int x=p[n-1];
        x=(x<n/2?x:x-n/2);
        s[x]=(x==p[n-1]);
        dfs(x);
    }
    for(int i=0;i<n/2;i++){
        //cout << "get " << i << endl;
        if(s[i]==-1) s[i]=0,dfs(i);
        if(s[i]) swap(al[i],ar[i]);
    }
    for(int i=0;i<n/2;i++){
        if(al[i]<n/2) t[al[i]]=0;
        else al[i]-=n/2,t[al[i]]=1;
    }
    for(int i=0;i<n-n/2;i++) if(ar[i]>=n/2) ar[i]-=n/2;
    //cout << "end" << endl;
    vector<int> sl=get(al),sr=get(ar);
    s.insert(s.end(),sl.begin(),sl.end());
    s.insert(s.end(),sr.begin(),sr.end());
    s.insert(s.end(),t.begin(),t.end());
    return s;
}
int cal(int n){
    return (n<=1?0:cal(n/2)+cal(n-n/2)+2*(n/2));
}

// Alice
int // returns la
alice(
    /*  in */ const int n,
    /*  in */ const char names[][5],
    /*  in */ const unsigned short numbers[],
    /* out */ bool outputs_alice[]
) {
    vector<pii> p(n);
    for(int i=0;i<n;i++) p[i]={encode(names[i]),i};
    sort(p.begin(),p.end());
    vector<int> a(n);
    for(int i=0;i<n;i++){
        int id=p[i].se;
        for(int j=0;j<19;j++) outputs_alice[i*35+j]=p[i].fi>>j&1;
        for(int j=0;j<16;j++) outputs_alice[i*35+19+j]=numbers[id]>>j&1;
        a[i]=id;
    }
    a=get(a);
    int sz=a.size();
    for(int i=0;i<sz;i++) outputs_alice[n*35+i]=a[i];
    return n*35+sz;
}


// Bob
int // returns lb
bob(
    /*  in */ const int m,
    /*  in */ const char senders[][5],
    /*  in */ const char recipients[][5],
    /* out */ bool outputs_bob[]
) {
    vector<pii> p(m),pp(m);
    for(int i=0;i<m;i++) p[i]={encode(recipients[i]),encode(senders[i])};
    sort(p.begin(),p.end());
    for(int i=0;i<m;i++) pp[i]={p[i].se,i};
    sort(pp.begin(),pp.end());
    vector<int> a(m);
    for(int i=0;i<m;i++){
        int id=pp[i].se;
        for(int j=0;j<19;j++) outputs_bob[i*38+j]=pp[i].fi>>j&1;
        for(int j=0;j<19;j++) outputs_bob[i*38+19+j]=p[id].fi>>j&1;
        a[i]=id;
    }
    a=get(a);
    int sz=(int)a.size();
    for(int i=0;i<sz;i++) outputs_bob[m*38+i]=a[i];
    return m*38+sz;
}

int *operations;
int (*operands)[2];
int ZERO,ONE,S;
int gate(int op,int x,int y){
    operations[S]=op;
    operands[S][0]=x;
    operands[S][1]=y;
    return S++;
}

struct event{
    int t;
    bool f=true;
    vector<int> x,y,v;
    event():t(-1),f(true){}
};
event e[2*T+5];
vector<int> flag;
vector<pii> sw;

void build(int l,int r){
    int n=r-l;
    if(n<=1) return;
    for(int i=0;i<n/2;i++) sw.pb({l+i,l+n/2+i});
    build(l,l+n/2);
    build(l+n/2,r);
    for(int i=0;i<n/2;i++) sw.pb({l+i,l+n/2+i});
}

void swap(int &x,int &y,int t){
    int z=gate(OP_AND,gate(OP_XOR,x,y),t);
    x=gate(OP_XOR,x,z);
    y=gate(OP_XOR,y,z);
}
int cmp(int x,int y){
    if(e[y].f) return ZERO;
    if(e[x].f) return ONE;
    int eq=ONE,res=ZERO;
    for(int i=18;i>=0;i--){
        res=gate(OP_OR,res,gate(OP_AND,eq,gate(OP_GREATER,e[x].x[i],e[y].x[i])));
        eq=gate(OP_AND,eq,gate(OP_EQUAL,e[x].x[i],e[y].x[i]));
    }
    return gate(OP_OR,res,gate(OP_AND,eq,gate(OP_GREATER,e[x].t,e[y].t)));
}

void shuffle(){
    int sz=sw.size();
    for(int i=0;i<sz;i++){
        auto [x,y]=sw[i];
        if(flag[i]==-1) flag[i]=cmp(x,y);
        if(flag[i]==ZERO) continue;
        if(flag[i]==ONE){
            swap(e[x],e[y]);
            continue;
        }
        for(int j=0;j<19;j++){
            swap(e[x].x[j],e[y].x[j],flag[i]);
            swap(e[x].y[j],e[y].y[j],flag[i]);
        }
        for(int j=0;j<16;j++) swap(e[x].v[j],e[y].v[j],flag[i]);
        swap(e[x].t,e[y].t,flag[i]);
    }
}

void merge(int x,int y,int d){
    if(x+d==y){
        sw.pb({x,y});
        return;
    }
    merge(x,y,d*2);
    merge(x+d,y+d,d*2);
    for(int i=x+d;i+d<2*T;i+=d*2) sw.pb({i,i+d});
}
vector<int> Xor(vector<int> a,vector<int> b){
    for(int i=0;i<16;i++) a[i]=gate(OP_XOR,a[i],b[i]);
    return a;
}
vector<int> fmul(vector<int> a,int t){
    for(int i=0;i<16;i++) a[i]=gate(OP_GREATER,a[i],t);
    return a;
}
vector<int> mul(vector<int> a,int t){
    for(int i=0;i<16;i++) a[i]=gate(OP_AND,a[i],t);
    return a;
}

pii add2(int a,int b,int c){
    tie(a,b)=mpp(gate(OP_XOR,a,b),gate(OP_AND,a,b));
    tie(a,c)=mpp(gate(OP_XOR,a,c),gate(OP_AND,a,c));
    return {a,gate(OP_OR,b,c)};
};
vector<int> add(vector<int> a,vector<int> b){
    int c=ZERO;
    for(int i=0;i<16;i++) tie(a[i],c)=add2(a[i],b[i],c);
    return a;
};

// Circuit
int // returns l
circuit(
    /*  in */ const int la,
    /*  in */ const int lb,
    /* out */ int _operations[],
    /* out */ int _operands[][2],
    /* out */ int outputs_circuit[][16]
) {
    S=la+lb;
    operations=_operations;
    operands=_operands;
    ZERO=gate(OP_ZERO,0,0);
    ONE=gate(OP_ONE,0,0);

    int n=0,m=0;
    while(n*35+cal(n)<la) n++;
    while(m*38+cal(m)<lb) m++;
    for(int i=0;i<n;i++){
        for(int j=0;j<19;j++) e[i].x.pb(i*35+j);
        e[i].y=e[i].x;
        for(int j=0;j<16;j++) e[i].v.pb(i*35+19+j);
        e[i].t=ZERO,e[i].f=false;
    }
    for(int i=0;i<m;i++){
        for(int j=0;j<19;j++){
            e[T+i].x.pb(la+i*38+j);
            e[T+i].y.pb(la+i*38+19+j);
        }
        e[T+i].v.assign(16,ZERO);
        e[T+i].t=ONE,e[T+i].f=false;
    }

    merge(0,T,1);
    flag.assign(sw.size(),-1);
    shuffle();
    vector<int> cur(16,ZERO);
    for(int i=0;i<n+m;i++){
        cur=Xor(cur,fmul(Xor(cur,e[i].v),e[i].t));
        swap(e[i].x,e[i].y),e[i].v=cur;
    }
    reverse(sw.begin(),sw.end());
    reverse(flag.begin(),flag.end());
    shuffle();
    sw.clear();flag.clear();

    build(T,T+m);
    for(int i=0;i<sw.size();i++) flag.pb(la+m*38+i);
    shuffle();
    sw.clear();flag.clear();
    merge(0,T,1);
    flag.assign(sw.size(),-1);
    shuffle();
    cur.assign(16,ZERO);
    for(int i=n+m-1;i>=0;i--){
        swap(cur,e[i].v);
        cur=mul(add(cur,e[i].v),e[i].t);
    }
    reverse(sw.begin(),sw.end());
    reverse(flag.begin(),flag.end());
    shuffle();
    sw.clear();flag.clear();
    build(0,n);
    for(int i=0;i<sw.size();i++) flag.pb(n*35+i);
    shuffle();
    for(int i=0;i<n;i++) for(int j=0;j<16;j++) outputs_circuit[i][j]=e[i].v[j];
    return S;
}
