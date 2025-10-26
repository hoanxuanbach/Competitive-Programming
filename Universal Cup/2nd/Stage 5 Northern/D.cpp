#include<bits/stdc++.h>
using namespace std;
#define REP(x,n) for(int x=0;x<n;x++)

using ULL = unsigned  long  long ;

unsigned mul_table[ 256 ][ 256 ];
unsigned sqrt_table[ 256 ];
unsigned inverse_table[ 256 ];
unsigned quadratic_equation_b1_table[ 128 ]; // even solutions;

bool _auto_init() {
    mul_table[ 1 ][ 1 ] = 1 ;
     for ( int t= 1 ; t<= 4 ; t+=t) {
    REP (xh, 1 <<t) REP (yh, 1 <<t) {
         unsigned xhyhH = mul_table[ 1 <<(t- 1 )][mul_table[xh][yh]];
        REP (xl, 1 <<t) REP (yl, 1 <<t) {
        mul_table[xh<<t|xl][yh<<t|yl] =
            (mul_table[xh^xl][yh^yl]^mul_table[xl][yl])<<t ^ mul_table[xl][yl] ^ xhyhH;
        }
    }
    }
    REP (x, 256 ) sqrt_table[mul_table[x][x]] = x;
    REP (x, 256 ) REP (y, 256 ) if (mul_table[x][y] == 1u ) inverse_table[x] = y;
     for ( int x= 0 ; x< 256 ; x+= 2 ) quadratic_equation_b1_table[mul_table [x][x] ^ x] = x;
     return  true ;
}
bool _auto_init_done = _auto_init();

int middle(ULL x) {
     if ((x>> 8 ) == 0 ) return  4 ;
     if ((x>> 16 ) == 0 ) return  8 ;
     if ((x>> 32 ) == 0 ) return  16 ;
     return  32 ;
}

ULL mulp2(ULL x, ULL y) {
    assert(y && (y&(y- 1u )) == 0 ); // assert y = 2^i;
    int p = middle(x|y);
     if (p == 4 ) return mul_table[x][y ];
    ULL mask = ~ 0u >>( 32 -p);
    ULL xh = x >> p;
    ULL xl = x & mask;
    ULL yh = y >> p;
    ULL yl = y & mask;
    if (yh) {
     return (mulp2(xh^xl, yh)<<p) ^ mulp2(mulp2(xh, yh), 1u <<(p- 1 ));
    } else {
     return (mulp2(xh, yl)<<p) ^ mulp2(xl, yl);
    }
}

ULL mul(ULL x, ULL y) {
    int p = middle(x|y);
     if (p == 4 ) return mul_table[x][y];
    ULL mask = ~ 0u >>( 32 -p);
    ULL xh = x >> p;
    ULL xl = x & mask;
    ULL yh = y >> p;
    ULL yl = y & mask;
    ULL z0 = mul(xl, yl);
    ULL z1 = mul(xh^xl, yh^yl);
    ULL z2 = mul(xh, yh);
    ULL z3 = mulp2(z2, 1u <<(p- 1 ));
     return ((z0^z1)<<p) ^ z3 ^ z0;
}

ULL sq(ULL x) {
    int p = middle(x);
     if (p == 4 ) return mul_table[x][x];
    ULL mask = ~ 0u >>( 32 -p);
    ULL xh = x >> p;
    ULL xl = x & mask;
    ULL z = sq(xh);
    return (z<<p) ^ mulp2(z, 1u <<(p- 1 )) ^ sq(xl);
}

ULL sqrt(ULL x) {
    int p = middle(x);
     if (p == 4 ) return sqrt_table[x];
    ULL mask = ~ 0u >>( 32 -p);
    ULL xh = x >> p;
    ULL xl = x & mask;
    return (sqrt(xh)<<p) ^ sqrt(mulp2(xh, 1u <<(p- 1 )) ^ xl);
}

ULL power(ULL x, ULL y) {
    ULL ret = (y& 1 ? x: 1 );
     for (y>>= 1 ; y; y>>= 1 ) {
    x = sq(x);
    if (y& 1 ) ret = mul(ret, x);
    }
    return ret;
}

ULL slow_inverse(ULL x) {
    if (x>> 32 ) return power(x, - 2ULL );
     return power(x, ( 1ULL << 32 )- 2ULL );
}

ULL inverse(ULL x) {
    int p = middle(x);
     if (p == 4 ) return inverse_table[x];
    ULL mask = ~ 0u >>( 32 -p);
    ULL xh = x >> p;
    ULL xl = x & mask;
    ULL det = mul(xl, xh^xl) ^ mulp2(sq(xh), 1u <<(p- 1 ));
    ULL inv_det = inverse(det);
    return (mul(inv_det, xh)<<p) ^ mul(inv_det, xh^xl);
}

// find x: xx + x = c;
// answer: x, x+1;
ULL quadratic_equation_b1(ULL c) {
    assert(~c>> 63 & 1 ); // assert c < 2^{63};
    int p = middle(c<< 1 );
     if (p == 4 ) return quadratic_equation_b1_table[c];
    ULL mask = ~ 0u >>( 32 -p);
    ULL H = 1u <<(p- 1 );
    ULL ch = c >> p;
    ULL cl = c & mask;
    ULL xh = quadratic_equation_b1(ch);
    ULL z = mulp2(sq(xh), H);
    if ((z ^ cl) & H) { xh ^= 1 ; z ^= H; }
    ULL xl = quadratic_equation_b1(z ^ cl);
    return (xh<<p) ^ xl;
}

// find x: xx + bx = c;
// answer: x, x+b;
ULL quadratic_equation(ULL b, ULL c) {
    if (b == 0 ) return sqrt(c);
    ULL d = (b == 1 ? c: mul(c, inverse(sq(b))));
    assert(~d>> 63 & 1 ); // assert c/(b^2) < 2^{63};
    ULL x = quadratic_equation_b1(d);
    return (b == 1 ? x: mul(b, x));
}


void solve(){
    int t,n;cin >> t >> n;
    if(t==1){
        ULL x=0,x3=0;
        for(int i=1;i<=n;i++){
            ULL a;cin >> a;
            x^=a;x3^=mul(a,mul(a,a));
        }
        cout << x << ' ' << x3 << '\n';
    }
    else{
        ULL x,x3;cin >> x >> x3;
        for(int i=1;i<=n;i++){
            ULL a;cin >> a;
            x^=a;x3^=mul(a,mul(a,a));
        }
        x3=mul(x3,inverse(x));
        x3=mul(x,x)^x3;
        ULL a=quadratic_equation(x,x3);
        ULL b=x^a;
        cout << a << ' ' << b << '\n';
    }

}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);cout.tie(NULL);
    int test=1;//cin >> test;
    while(test--) solve();
}