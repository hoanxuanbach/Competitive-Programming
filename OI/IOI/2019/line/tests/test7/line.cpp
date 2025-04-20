#include<bits/stdc++.h>
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_real_distribution<double> pp(0.0,1.0);
const int maxn = 1e5+5;
const double E = 0.16;

int rand_int(int l,int r){
    return l+(int)(rng()%(r-l+1));
}
double rnd(){
    return pp(rng);
}

int n,x[maxn],y[maxn];

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    for(int test=7;test<=7;test++){
        if(test==1 || test==4 || test==3 || test==6 || test==10) continue;
        string ss=to_string(test);
        if(test<=9) ss="0"+ss;
        string inp=ss+".in";
        string out=ss+".out.txt";
        ifstream cin(inp);
        ofstream cout(out);

        cin >> n;
        for(int i=1;i<=n;i++) cin >> x[i] >> y[i];
        int mx=-1,cc=-1;
        vector<int> res;

        for(int k=1;k>=0;k--){
            cerr << "S" << endl;
            int cnt=0;
            vector<int> p(n);
            iota(p.begin(),p.end(),1);

            auto f = [&](int a){
                if(a<0 || a>=n-2) return 0;
                int t=k^(a&1);
                int b=p[a+1],c=p[a+2];a=p[a];
                if(t) return (int)((x[a]<x[b])==(x[b]<x[c]));
                else return (int)((y[a]<y[b])==(y[b]<y[c]));
            };
            for(int i=0;i<n-2;i++) cnt+=f(i);
            if(cnt>mx) mx=cnt,res=p,cc=k;

            auto g = [&](int i,int t){
                cnt-=f(i)+f(i-1)+f(i-2);p[i]=t;
                cnt+=f(i)+f(i-1)+f(i-2);
            };
            long long M=(k?10000000000:10000000000);
            int Max=-1;
            for(double T=1000000;M;M--,T*=0.999999){
                int a=-1,b=-1;
                do{
                    a=rand_int(0,n-1);
                    b=rand_int(0,n-1);
                }while(a==b);

                int pa=p[a],pb=p[b],cur=cnt;
                g(a,pb),g(b,pa);
                int nw=cnt;
                if(nw>mx) mx=nw,res=p,cc=k;
                if(nw>Max){
                    Max=nw;
                    cerr << n-Max << endl;
                }
                if(nw<cur && exp((nw-cur)*T)>=rnd()) g(a,pa),g(b,pb);
            }
        }
        vector<pair<int,int>> ans;
        ans.push_back({0,0});
        if(!cc) ans.push_back({0,y[res[0]]});
        else ans.push_back({x[res[0]],0});
        if(ans.back()==make_pair(0,0)) ans.pop_back();

        for(int i=0;i<n;i++){
            int t=(i^cc)&1,id=res[i];
            auto [cx,cy]=ans.back();
            if(i==n-1){
                if(cx!=x[id] && cy!=y[id]) ans.push_back({x[id],cy});
                ans.push_back({x[id],y[id]});
            }
            else{
                int nid=res[i+1];
                if(!t){
                    if(cy!=y[id]) ans.push_back({cx,y[id]});
                    if(x[id]<min(cx,x[nid]) || x[id]>max(cx,x[nid])) ans.push_back({x[id],y[id]});
                    ans.push_back({x[nid],y[id]});
                }
                else{
                    if(cx!=x[id]) ans.push_back({x[id],cy});
                    if(y[id]<min(cy,y[nid]) || y[id]>max(cy,y[nid])) ans.push_back({x[id],y[id]});
                    ans.push_back({x[id],y[nid]});
                }
            }
        }
        cout << (int)ans.size()-1 << '\n';
        for(int i=1;i<(int)ans.size();i++) cout << ans[i].first << ' ' << ans[i].second << '\n';
        cerr << n-mx << ' ' << cc << endl;
    }
}
