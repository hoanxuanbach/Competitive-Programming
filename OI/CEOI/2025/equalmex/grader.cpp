#include <iostream>
#include <vector>
#include <utility>
#include "equalmex.h"

using namespace std;

int main() {
    // Initialize input/output streams
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, q;
    cin >> n >> q;
    
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    
    vector<pair<int, int>> queries(q);
    for (int i = 0; i < q; i++) {
        cin >> queries[i].first >> queries[i].second;
    }
    
    // Call the solve function
    vector<int> results = solve(n, v, q, queries);
    
    // Output the results
    for (int i = 0; i < q; i++) {
        cout << results[i] << "\n";
    }
    
    return 0;
}
