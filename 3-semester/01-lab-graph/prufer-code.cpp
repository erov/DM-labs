#include <iostream>
#include <climits>
#include <cstddef>
#include <cmath>
#include <vector>
#include <iomanip>
#include <cassert>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    #ifdef HOME
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        clock_t start_clock = clock();
    // #else
    //  freopen(".in", "r", stdin);
    //  freopen(".out", "w", stdout);
    #endif
    
    solve();

    #ifdef HOME
        // system("pause");
        printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
    #endif
}

void solve() {
    size_t n;
    cin >> n;

    vector<set<size_t>> g(n);
    for (size_t i = 0; i != n - 1; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u, --v;
        g[u].insert(v);
        g[v].insert(u);
    }

    set<size_t> leaves;
    for (size_t v = 0; v != n; ++v) {
        if (g[v].size() == 1) {
            leaves.insert(v);
        }
    }

    for (size_t iter = 0; iter != n - 2; ++iter) {
        size_t v = *leaves.begin();
        leaves.erase(leaves.begin());

        size_t to = *g[v].begin();
        g[v].clear();

        cout << to + 1 << ' ';

        g[to].erase(v);
        if (g[to].size() == 1) {
            leaves.insert(to);
        }
    }
}