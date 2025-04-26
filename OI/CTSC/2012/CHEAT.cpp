#include<bits/stdc++.h>
using namespace std;
#define maxn 1100005
#define fi first
#define se second
const int inf = 1e9;

#ifdef LOCAL
#define DEBUG(...) debug(#__VA_ARGS__, __VA_ARGS__)
#else
#define DEBUG(...) 6
#endif

template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void debug(string s, T x) {cerr << "\033[1;35m" << s << "\033[0;32m = \033[33m" << x << "\033[0m\n";}
template<typename T, typename... Args> void debug(string s, T x, Args... args) {for (int i=0, b=0; i<(int)s.size(); i++) if (s[i] == '(' || s[i] == '{') b++; else
if (s[i] == ')' || s[i] == '}') b--; else if (s[i] == ',' && b == 0) {cerr << "\033[1;35m" << s.substr(0, i) << "\033[0;32m = \033[33m" << x << "\033[31m | "; debug(s.substr(s.find_first_not_of(' ', i + 1)), args...); break;}}

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

#define per(i, a, b) for (int i = (b) - 1; i >= a; i--)

const int N = 2200005;

string s;
int *h;

namespace SuffixArray {

const int N = 2200005;

int sa[N],rk[N],ht[N];
bool t[N<<1];

bool islms(const int i,const bool *t) { /// start-hash
	return i>0&&t[i]&&!t[i - 1];
} /// end-hash

template<class T>
inline void sort(T s,int *sa,const int len,const int sz,const int sigma,
					bool *t,int *b,int *cb,int *p) { /// start-hash
	memset(b,0,sizeof(int)*sigma);
	memset(sa,-1,sizeof(int)*len);
	rep(i,0,len) b[(int)s[i]]++;
	cb[0]=b[0];
	rep(i,1,sigma) cb[i]=cb[i-1]+b[i];
	per(i,0,sz) sa[--cb[(int)s[p[i]]]]=p[i];
	rep(i,1,sigma) cb[i]=cb[i-1]+b[i-1];
	rep(i,0,len) if (sa[i]>0&&!t[sa[i]-1]) sa[cb[(int)s[sa[i]-1]]++]=sa[i]-1;
	cb[0]=b[0];
	rep(i,1,sigma) cb[i]=cb[i-1]+b[i];
	per(i,0,len) if (sa[i]>0&&t[sa[i]-1]) sa[--cb[(int)s[sa[i]-1]]]=sa[i]-1;
} /// end-hash

template<class T>
inline void sais(T s,int *sa,const int len,bool *t,int *b,int *b1,
				const int sigma) { /// start-hash
	int p=-1,*cb=b+sigma;
	t[len-1]=1;
	per(i,0,len-1) t[i]=s[i]<s[i+1]||(s[i]==s[i+1]&&t[i+1]);
	int sz=0,cnt=0;
	rep(i,1,len) if (t[i]&&!t[i-1]) b1[sz++]=i;
	sort(s,sa,len,sz,sigma,t,b,cb,b1);
	sz=0;
	rep(i,0,len) if (islms(sa[i],t)) sa[sz++]=sa[i];
	rep(i,sz,len) sa[i]=-1;
	rep(i,0,sz) {
		int x=sa[i];
		rep(j,0,len) {
			if (p==-1||s[x+j]!=s[p+j]||t[x+j]!=t[p+j]) {
				cnt++; p=x;
				break;
			} else if (j>0&&(islms(x+j,t)||islms(p+j,t))) {
				break;
			}
		}
		sa[sz+(x>>=1)]=cnt-1;
	}
	for (int i=len-1,j=len-1;i>=sz;i--) if (sa[i]>=0) sa[j--]=sa[i];
	int *s1=sa+len-sz,*b2=b1+sz;
	if (cnt<sz) sais(s1,sa,sz,t+len,b,b1+sz,cnt);
	else rep(i,0,sz) sa[s1[i]]=i;
	rep(i,0,sz) b2[i]=b1[sa[i]];
	sort(s,sa,len,sz,sigma,t,b,cb,b2);
} /// end-hash

template<class T>
inline void getHeight(T s,int n) { /// start-hash
	rep(i,1,n+1) rk[sa[i]]=i;
	int j=0,k=0;
	for (int i=0;i<n;ht[rk[i++]]=k)
		for (k?k--:0,j=sa[rk[i]-1];s[i+k]==s[j+k];k++);
} /// end-hash

template<class T>
inline void init(T s,const int len,const int sigma) { /// start-hash
	sais(s,sa,len,t,rk,ht,sigma);
} /// end-hash

inline void solve(string s,int len) {
	init(s,len+1,124);
	getHeight(s,len);
}
} // namespace SuffixArray


int n;

int stk[N],top,a[N],l[N],r[N],sz[N],par[N];

void build() { /// start-hash
	int top=0;
	h=SuffixArray::ht+1;
	rep(i,1,n) l[i]=r[i]=par[i]=0;
	rep(i,1,n) {
		int k=top;
		while (k>0&&h[stk[k-1]]>h[i]) --k;
		if (k) r[stk[k-1]]=i;
		if (k<top) l[i]=stk[k];
		stk[k++]=i;
		top=k;
	}
	int t=0,rt=stk[0];
	int *q=stk;
	q[t++]=rt;
	rep(i,0,t) {
		int u=q[i]; sz[u]=1;
		if (l[u]) q[t++]=l[u],par[l[u]]=u;
		if (r[u]) q[t++]=r[u],par[r[u]]=u;
	}
}/// end-hash

int m,q,lcp[2*maxn],c[2*maxn],bl[2*maxn],len[2*maxn];
int ss[maxn],dp[maxn];
string S[maxn];
vector<int> nxt[maxn];

void build_suffix_array(){
    n=(int)s.length();
    SuffixArray::solve(s,n);
    for(int i=0;i<=n;i++){
        lcp[i]=SuffixArray::ht[i+1];
        c[i]=SuffixArray::sa[i];
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    cin >> q >> m;
    for(int i=1;i<=m;i++){
        string a;cin >> a;
        int cc=(int)s.length(),sz=(int)a.length();
        for(int j=0;j<sz;j++){
            bl[cc+j]=i;
            len[cc+j]=sz-j;
        }
        s+=a;s+='#';
    }
    for(int i=1;i<=q;i++){
        cin >> S[i];
        ss[i]=(int)S[i].length();
        nxt[i].assign(ss[i],0);
        int cc=(int)s.length();
        for(int j=0;j<ss[i];j++){
            bl[cc+j]=-i;
            len[cc+j]=ss[i]-j;
        }
        s+=S[i];s+='#';
    }
    build_suffix_array();
    int cc=-inf;
    for(int i=0;i<=n;i++){
        int u=c[i],id=bl[u];
        if(id>0) cc=inf;
        else if(id<0) id=-id,nxt[id][ss[id]-len[u]]=max(nxt[id][ss[id]-len[u]],min(cc,len[u]));
        cc=min(cc,lcp[i]);
    }
    cc=-inf;
    for(int i=n;i>=0;i--){
        int u=c[i],id=bl[u];
        if(id>0) cc=inf;
        else if(id<0) id=-id,nxt[id][ss[id]-len[u]]=max(nxt[id][ss[id]-len[u]],min(cc,len[u]));
        if(i) cc=min(cc,lcp[i-1]);
    }
    for(int i=1;i<=q;i++){
        auto check = [&](int L){
            deque<int> dq;
            dp[ss[i]]=0;
            for(int j=ss[i]-1;j>=0;j--){
                if(j+L<=ss[i]){
                    while(!dq.empty() && dp[dq.back()]+dq.back()<=dp[j+L]+(j+L)) dq.pop_back();
                    dq.push_back(j+L);
                }
                while(!dq.empty() && dq.front()>j+nxt[i][j]) dq.pop_front();
                dp[j]=dp[j+1];
                if(!dq.empty()) dp[j]=max(dp[j],dp[dq.front()]+dq.front()-j);
            }
            return dp[0]*10>=ss[i]*9;
        };
        int l=1,r=ss[i],res=0;
        while(l<=r){
            int mid=(l+r)>>1;
            if(check(mid)) res=mid,l=mid+1;
            else r=mid-1;
        }
        cout << res << '\n';
    }
}
