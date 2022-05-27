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
     freopen("multispan.in", "r", stdin);
     freopen("multispan.out", "w", stdout);
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

    struct edge_t {
        size_t u, v;
    };

    vector<edge_t> edge(m);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        cin >> u >> v;
        --u, --v;
        edge[i] = {u, v};
    }

    if (m == 0) {
        cout << 0;
        return;
    }


    constexpr size_t INF = numeric_limits<size_t>::max();
    constexpr size_t MAX_M = 2'000 + 47;
    
    vector<vector<size_t>> p(MAX_M, vector<size_t>(n));
    vector<vector<size_t>> r(MAX_M, vector<size_t>(n));
    vector<vector<set<pair<size_t, size_t>>>> g(MAX_M, vector<set<pair<size_t, size_t>>>(n));  // g[matroid_id][v] = {to, edge_id}
    vector<vector<pair<size_t, size_t>>> prev(MAX_M, vector<pair<size_t, size_t>>(n, {INF, INF}));  // {to, edge_id}
    vector<set<size_t>> base(MAX_M);
    vector<size_t> base_id(m, INF);
 
    auto get = [&](auto& self, size_t matroid_id, size_t v) -> size_t {
        return (v == p[matroid_id][v] ? v : p[matroid_id][v] = self(self, matroid_id, p[matroid_id][v]));
    };
 
    auto unite = [&](size_t matroid_id, size_t a, size_t b) -> bool {
        a = get(get, matroid_id, a);
        b = get(get, matroid_id, b);
 
        if (a == b) {
            return false;
        }
 
        if (r[matroid_id][a] < r[matroid_id][b]) {
            swap(a, b);
        }
        p[matroid_id][b] = a;
        if (r[matroid_id][a] == r[matroid_id][b]) {
            ++r[matroid_id][a];
        }
 
        return true;
    };

    auto dfs_mark_prev = [&](auto& self, size_t matroid_id, size_t v) -> void {
        for (auto [to, edge_id] : g[matroid_id][v]) {
            if (prev[matroid_id][to] == make_pair(INF, INF)) {
                prev[matroid_id][to] = {v, edge_id};
                self(self, matroid_id, to);
            }
        }
    };

    auto mark_graph = [&](size_t matroid_id, size_t item) {
        prev[matroid_id].assign(n, {INF, INF});
        prev[matroid_id][edge[item].u] = {edge[item].u, INF};
        dfs_mark_prev(dfs_mark_prev, matroid_id, edge[item].u);
    };


    auto add_in_ith_base = [&](size_t i, size_t id) -> void {
        base[i].insert(id);
        g[i][edge[id].u].insert({edge[id].v, id});
        g[i][edge[id].v].insert({edge[id].u, id});
    };

    auto rm_from_ith_base = [&](size_t i, size_t id) -> void {
        base[i].erase(id);
        g[i][edge[id].u].erase({edge[id].v, id});
        g[i][edge[id].v].erase({edge[id].u, id});
    };


    for (size_t id = 0; id != MAX_M; ++id) {
        for (size_t i = 0; i != n; ++i) {
            p[id][i] = i;
            r[id][i] = 0;
        }
    }


    for (size_t item = 0; item != m; ++item) {
        vector<size_t> swap_with(m);
        queue<size_t> que;
        que.push(item);

        size_t available_bases = 1;

        for (size_t matroid_id = 0; matroid_id != base.size(); ++matroid_id) {
            mark_graph(matroid_id, item);
            if (base[matroid_id].size() == n - 1) {
                ++available_bases;
            }
        }

        for (;;) {
            swap_with.assign(m, INF);
            bool swap_seq_found = false;
            size_t edge_id;
            size_t matroid_id;

            while (!que.empty()) {
                edge_id = que.front();
                matroid_id = (base_id[edge_id] == INF ? 0 : base_id[edge_id] + 1) % available_bases;

                que.pop();

                if (get(get, matroid_id, edge[edge_id].u) != get(get, matroid_id, edge[edge_id].v)) {
                    swap_seq_found = true;
                    break;
                }
                
                size_t vert = (edge[edge_id].u != edge[item].u && swap_with[prev[matroid_id][edge[edge_id].u].second] == INF 
                    ? edge[edge_id].u : edge[edge_id].v);

                vector<size_t> swappable;
                while (vert != edge[item].u && swap_with[prev[matroid_id][vert].second] == INF) {
                    swappable.push_back(prev[matroid_id][vert].second);
                    vert = prev[matroid_id][vert].first;
                }

                reverse(swappable.begin(), swappable.end());

                for (size_t v : swappable) {
                    swap_with[v] = edge_id;
                    que.push(v);
                }
            }

            if (!swap_seq_found) {  // dependent :( => need more base
                que.push(item);
                ++available_bases;
                continue;
            }

            unite(matroid_id, edge[edge_id].u, edge[edge_id].v);

            while (swap_with[edge_id] != INF) {
                add_in_ith_base(matroid_id, edge_id);
                rm_from_ith_base(base_id[edge_id], edge_id);
                swap(base_id[edge_id], matroid_id);
                edge_id = swap_with[edge_id];
                
            }
            add_in_ith_base(matroid_id, edge_id);
            base_id[edge_id] = matroid_id;

            break;
        }
    }

    size_t mst_counter = 0;
    for (size_t id = 0; id != base.size(); ++id) {
        if (base[id].size() == n - 1) {
            ++mst_counter;
        }
    }

    cout << mst_counter << '\n';
    for (size_t id = 0; id != mst_counter; ++id) {
        for (size_t edge_id : base[id]) {
            cout << edge_id + 1 << ' ';
        }
        cout << '\n';
    }
}
