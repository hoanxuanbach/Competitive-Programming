#include<bits/stdc++.h>
using namespace std;
#define int long long 
const int mod = 998244353;
const int root = 3;
int power(int a,int n){
    int res=1;
    while(n){
        if(n&1) res=res*a%mod;
        a=a*a%mod;n>>=1;
    }
    return res;
}
const int iroot = power(3,mod-2);

void fft(vector<int> &a,bool invert){
    int n=(int)a.size();
    for(int i=1,j=0;i<n;i++){
        int bit=n>>1;
        while(j&bit){j^=bit;bit>>=1;}
        j^=bit;
        if(i<j) swap(a[i],a[j]);
    }
    for(int len=2;len<=n;len<<=1){
        int wn=power((invert?iroot:root),(mod-1)/len);
        for(int i=0;i<n;i+=len){
            int w=1;
            for(int j=0;j<len/2;j++){
                int u=a[i+j],v=a[i+j+len/2]*w%mod;
                a[i+j]=(u+v)%mod;
                a[i+j+len/2]=(u-v+mod)%mod;
                w=w*wn%mod;
            }
        }
    }
    if(invert){
        int dd=power(n,mod-2);
        for(int i=0;i<n;i++) a[i]=a[i]*dd%mod;
    }
    return;
}
 
vector<int> mul(vector<int> a,vector<int> b){
    int n=(int)a.size()+(int)b.size(),sz=1;
    while(sz<n) sz<<=1;
    a.resize(sz);b.resize(sz);
    fft(a,false);fft(b,false);
    for(int i=0;i<sz;i++) a[i]=a[i]*b[i]%mod;
    fft(a,true);
    return a;
}

void solve(){
    string L,R,X;cin >> L >> R >> X;
    reverse(L.begin(),L.end());
    reverse(R.begin(),R.end());
    reverse(X.begin(),X.end());

    int S=(int)R.size();
    while((int)L.size()<S) L+='0';

    while(!L.empty() && L.back()==R.back()) L.pop_back(),R.pop_back();
    S=(int)R.size();

    while((int)X.size()<S) X+='0';
    while((int)X.size()>S) X.pop_back();

    if(R.empty()){
        cout << 0 << '\n';
        return;
    }

    vector<int> cnt(2*S);

    int carry=0;
    for(int i=0;i<S;i++){
        int d=(i==(S-1))-(L[i]-'0')-carry;
        carry=0;
        if(d<0) carry=1,d=(d+2)&1;
        L[i]=char('0'+d);
    }

    R.back()='0';
    carry=1;
    for(int i=0;i<S;i++){
        int d=(R[i]-'0')+carry;
        carry=0;
        if(d>=2) carry=1,d=0;
        R[i]=char('0'+d);
    }

    //cout << L << ' ' << R << ' ' << X << '\n';

    if(X.back()=='1'){
        vector<int> a(S),b(S);
        for(int i=0;i<S;i++) a[i]=L[i]-'0',b[i]=R[i]-'0';
        a=mul(a,b);
        for(int i=0;i<2*S;i++) cnt[i]+=a[i];
    }

    auto add = [&](vector<int> &a,vector<int> &b,int k){
        function<void(int,int)> dnc = [&](int l,int r){
            //cout << l << ' ' << r << endl;                             
            if(l==r) return;
            int mid=(l+r)>>1;
            dnc(l,mid);dnc(mid+1,r);
            vector<int> x(mid-l+1),y(r-mid);
            //cout << "cal " << l << ' ' << r << endl;
            for(int i=l;i<=mid;i++) x[i-l]=b[i];
            for(int i=mid+1;i<=r;i++) y[i-mid-1]=a[i];
            x=mul(x,y);
            for(int i=0;i<r-l;i++) cnt[i+l+mid+1-k]+=x[i];
            //cout << "end " << l << ' ' << r << endl;
        };
        dnc(0,S-1);
    };

    auto cal = [&](string T){
        vector<int> a(S),b(S);
        for(int i=0;i<S;i++) a[i]=(T[i]-'0')&(X[i]-'0'),b[i]=T[i]-'0';
        add(a,b,0);
    };
    cal(L);cal(R);

    vector<int> a(S),b(S);
    for(int i=0;i<S;i++) a[i]=(L[i]-'0')+(R[i]-'0'),b[i]=X[i]-'0';
    add(a,b,1);


    for(int i=1;i<2*S;i++) cnt[i]+=cnt[i-1]/2,cnt[i-1]&=1;

    string res;
    for(int i=0;i<2*S;i++) res+=char('0'+cnt[i]);
    while((int)res.size()>1 && res.back()=='0') res.pop_back();
    reverse(res.begin(),res.end());

    cout << res << '\n';
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test;cin >> test;
    while(test--) solve();
}