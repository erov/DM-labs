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
    size_t n, m;
    cin >> n >> m;

    vector<vector<size_t>> g(n);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u, --v;

        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<size_t> order(n);
    for (size_t i = 0; i != n; ++i) {
        order[i] = i;
    }

    sort(order.begin(), order.end(), [&](size_t a, size_t b) {
        return g[a].size() > g[b].size();
    });

    size_t k = g[order[0]].size();
    if (k % 2 == 0) {
        ++k;
    }
    vector<size_t> color(n, 0);
    vector<bool> used(n, false);
    
    auto make_coloring = [&](auto& self, size_t v) -> void {
        used[v] = true;
        set<size_t> neighbours;
        for (size_t to : g[v]) {
            neighbours.insert(color[to]);
        }
        color[v] = 1;
        while (neighbours.count(color[v])) {
            ++color[v];
        }
        for (size_t to : g[v]) {
            if (!used[to]) {
                self(self, to);
            }
        }
    };
    
    make_coloring(make_coloring, 0);

    fill(used.begin(), used.end(), false);
    auto check_coloring = [&](auto& self, size_t v) {
        used[v] = true;
        if (color[v] == 0) {
            return false;
        }
        bool back = true;
        for (size_t to : g[v]) {
            if (color[to] == color[v]) {
                return false;
            }
            if (!used[to]) {
                back &= self(self, to);
            }
        }
        return back;
    };

    assert(check_coloring(check_coloring, 0));

    cout << k << '\n';
    for (size_t col : color) {
        cout << col << '\n';
    }
}