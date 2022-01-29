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
     freopen("destroy.in", "r", stdin);
     freopen("destroy.out", "w", stdout);
    #endif
    
    solve();

    #ifdef HOME
        // system("pause");
        printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
    #endif
}

void solve() {
    size_t n, m;
    int64_t max_cost;
    cin >> n >> m >> max_cost;
 
    struct edge {
        size_t u;
        size_t v;
        int64_t w;
        size_t id;
    };
 
    vector<edge> g(m);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        int64_t w;
        cin >> u >> v >> w;
        --u, --v;
        g[i] = {u, v, w, i};
    }
 
    sort(g.begin(), g.end(), [](edge& a, edge& b) {
        return a.w > b.w;
    });
 
    vector<size_t> p(n);
    vector<size_t> r(n);
 
    auto get = [&](auto& self, size_t v) -> size_t {
        return (v == p[v] ? v : p[v] = self(self, p[v]));
    };
 
    auto unite = [&](size_t a, size_t b) -> bool {
        a = get(get, a);
        b = get(get, b);
 
        if (a == b) {
            return false;
        }
 
        if (r[a] < r[b]) {
            swap(a, b);
        }
        p[b] = a;
        if (r[a] == r[b]) {
            ++r[a];
        }
 
        return true;
    }; 
 
    constexpr int64_t INF = numeric_limits<int64_t>::max();
    int64_t ans = INF;

    for (size_t i = 0; i != n; ++i) {
        p[i] = i;
        r[i] = 0;
    }

    vector<edge> no_used;
    for (size_t j = 0; j != m; ++j) {
        if (unite(g[j].u, g[j].v)) {
            // became connected
        } else {
            no_used.push_back(g[j]);
        }
    }

    bool connected = true;
    for (size_t i = 0; i != n; ++i) {
        if (get(get, 0) != get(get, i)) {
            connected = false;
            break;
        }
    }

    if (!connected) {
        cout << 0;
        return;
    }

    sort(no_used.begin(), no_used.end(), [](edge& a, edge& b) -> bool {
        return a.w < b.w;
    });

    vector<size_t> deleted_ids;
    for (edge& e : no_used) {
        if (max_cost >= e.w) {
            max_cost -= e.w;
            deleted_ids.push_back(e.id);
        }
    }

    cout << deleted_ids.size() << '\n';
    sort(deleted_ids.begin(), deleted_ids.end());
    for (size_t id : deleted_ids) {
        cout << ++id << ' ';
    }
}
