#include <algorithm>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    #ifdef HOME
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        clock_t start_clock = clock();
    #else
     freopen("matching.in", "r", stdin);
     freopen("matching.out", "w", stdout);
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

    struct vertex {
        uint32_t w;
        size_t id;
    };

    vector<vertex> left(n);
    for (size_t i = 0; i != n; ++i) {
        uint32_t w;
        cin >> w;
        left[i] = {w, i};
    }

    sort(left.begin(), left.end(), [](vertex& a, vertex& b) -> bool {
        return a.w > b.w;
    });

    vector<vector<size_t>> g(n);
    for (size_t i = 0; i != n; ++i) {
        size_t k;
        cin >> k;
        for (size_t j = 0; j != k; ++j) {
            size_t to;
            cin >> to;
            g[i].push_back(--to);
        }
    }

    vector<bool> used(n);
    vector<size_t> matching(n, n);

    auto kuhn = [&](auto& self, size_t v) -> bool {
        if (used[v] == true) {
            return false;
        }
        used[v] = true;
        for (size_t to : g[v]) {
            if (matching[to] == n || self(self, matching[to]) == true) {
                matching[to] = v;
                return true;
            }
        }
        return false;
    };

    size_t taken = 0;
    for (auto [w, id] : left) {
        used.assign(n, false);
        auto matching_copy = matching;
        
        kuhn(kuhn, id);
        
        size_t matching_size = 0;
        for (size_t v = 0; v != n; ++v) {
            matching_size += (matching[v] != n ? 1 : 0);
        }
        if (matching_size != taken + 1) {
            matching.swap(matching_copy);
        } else { 
            ++taken;    
        }
    }

    vector<size_t> ans(n, 0);
    for (size_t v = 0; v != n; ++v) {
        if (matching[v] != n) {
            ans[matching[v]] = v + 1;
        }
    }

    for (size_t id : ans) {
        cout << id << ' ';
    }
}
