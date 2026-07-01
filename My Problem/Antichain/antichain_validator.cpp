#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxT = 10;
const ll maxN = 1e18;

void testcase(int test){
    setTestCase(test);
    ll n=inf.readLong(1,maxN,"n");inf.readEoln();
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);
    int test = inf.readInt(1,maxT,"test");inf.readEoln();
    for (int t = 1; t <= test; t++) {
        testcase(t);
    }
    inf.readEof();
}