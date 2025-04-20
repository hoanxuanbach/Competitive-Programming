#include<bits/stdc++.h>
using namespace std;
#define int long long
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> pp(0.0,1.0);
const int TL = 500000;

int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}

double rnd(){
    return pp(rng);
}

struct point{
    int x,y;
    point(int x=-1,int y=-1):x(x),y(y){}
    friend point operator-(point a,point b){
        return point(a.x-b.x,a.y-b.y);
    };
    friend int operator*(point a,point b){
        return a.x*b.y-a.y*b.x;
    };
};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=4;test<=4;test++){
        string S="0"+to_string(test);
        string inp=S+".txt";
        string out=S+"-out.txt";
        ifstream cin(inp);//fin(pout);
        int N,M,L;cin >> N >> M;

        vector<pair<int,int>> E(M);
        vector<vector<int>> adj(N);
        for(int i=0;i<M;i++){
            int u,v;cin >> u >> v;u--;v--;
            E[i]={u,v};
            adj[u].push_back(i);
            adj[v].push_back(i);
        }

        cin >> L;
        vector<point> P(L);
        for(int i=0;i<L;i++) cin >> P[i].x >> P[i].y;

        int mn=0;
        vector<int> ans;

        int cnt=0;
        vector<int> p(L,-1),f(N);
        auto g = [&](int a,int b,int c,int d){
            point X=P[b]-P[a],Y=P[c]-P[a],Z=P[d]-P[a];
            return (int)((X*Y<0) != (X*Z<0));
        };
        auto cal = [&](int i,int j){
            auto [a,b]=E[i];
            auto [c,d]=E[j];
            a=f[a],b=f[b],c=f[c],d=f[d];
            if(a==c || a==d || b==c || b==d) return 0LL;
            if(a<0 || b<0 || c<0 || d<0) return 0LL;
            return (int)(g(a,b,c,d)&g(c,d,a,b));
        };
        auto get = [&](int x){
            if(p[x]==-1) return 0LL;
            int total=0;
            for(int i:adj[p[x]]) for(int j=0;j<M;j++) total+=cal(i,j);
            return total;
        };
        //for(int i=0;i<N;i++){fin >> f[i];f[i]--;p[f[i]]=i;}
        for(int i=0;i<N;i++) p[i]=f[i]=i;
        for(int i=0;i<M;i++) for(int j=0;j<i;j++) cnt+=cal(i,j);
        mn=cnt,ans=f;


        int it=0,cur=M*M;
        for(long double T=1000000000;true;T*=0.99999){
            if(it%10000000==0){
                ofstream cout(out);
                for(int i=0;i<N;i++) cout << ans[i]+1 << '\n';
            }
            int x=-1,y=-1;
            do{
                x=rand_int(0,L-1);
                y=rand_int(0,L-1);
            }while(x==y || (p[x]==-1 && p[y]==-1));
            int pre=cnt;
            if(p[x]!=-1){
                cnt-=get(x);
                f[p[x]]=-1;
            }
            if(p[y]!=-1){
                cnt-=get(y);
                f[p[y]]=-1;
            }
            swap(p[x],p[y]);
            if(p[x]!=-1){
                f[p[x]]=x;
                cnt+=get(x);
            }
            if(p[y]!=-1){
                f[p[y]]=y;
                cnt+=get(y);
            }
            it++;
            if(cnt<mn){
                mn=cnt,ans=f;
                cerr << mn << ' ' << T << endl;
            }
            if(cnt>pre && exp((pre-cnt)/T)>=rnd()){
                cnt=pre;
                swap(p[x],p[y]);
                if(p[x]!=-1) f[p[x]]=x;
                if(p[y]!=-1) f[p[y]]=y;
            }
        }
    }
}
