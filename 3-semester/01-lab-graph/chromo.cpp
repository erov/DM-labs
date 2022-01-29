// #pragma GCC optimize("Ofast")
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

vector<int32_t> calculate_chromo(size_t n, vector<pair<size_t, size_t>> edge) {
    vector<int32_t> result(n + 1, 0);
    
    if (edge.empty()) {
        result[n] = 1;
        return result;
    }

    auto e = edge.back();
    edge.pop_back();
    auto without_edge = calculate_chromo(n, edge);

    set<pair<size_t, size_t>> new_edge;
    for (auto &[u, v] : edge) {
        if (u == e.first) {
            u = e.second;
        }
        if (v == e.first) {
            v = e.second;
        }

        if (u > v) {
            swap(u, v);
        }
        if (u != v && !new_edge.count({u, v})) {
            new_edge.insert({u, v});
        }
    }

    vector<pair<size_t, size_t>> slim_edge;
    for (auto it : new_edge) {
        slim_edge.push_back(it);
    }

    auto slim = calculate_chromo(n - 1, slim_edge);

    for (size_t i = 0; i != without_edge.size(); ++i) {
        result[i] += without_edge[i];
    }
    for (size_t i = 0; i != slim.size(); ++i) {
        result[i] -= slim[i];
    }
    return result;
}

void solve() {
    size_t n, m;
    cin >> n >> m;

    vector<pair<size_t, size_t>> edge(m);
    for (size_t i = 0; i != m; ++i) {
        cin >> edge[i].first >> edge[i].second;
    }

    auto ans = calculate_chromo(n, edge);

    cout << ans.size() - 1 << '\n';
    for (size_t i = ans.size(); i != 0; --i) {
        cout << ans[i - 1] << ' ';
    }
}