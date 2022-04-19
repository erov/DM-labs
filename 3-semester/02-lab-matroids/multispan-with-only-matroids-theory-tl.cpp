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


    // graph matoids
    constexpr size_t INF = numeric_limits<size_t>::max();
    constexpr size_t MATROID = 2'000 + 1;

    vector<vector<vector<pair<size_t, size_t>>>> g(MATROID, vector<vector<pair<size_t, size_t>>>(n));  // g[v] = {to, edge_id}
    vector<vector<size_t>> graph_color(MATROID, vector<size_t>(n));
    size_t current_color;
    vector<size_t> last_painted;
    size_t banned_id = INF;

    auto dfs_paint = [&](auto& self, size_t matroid_id, size_t v, size_t id, bool log = false) -> void {
        graph_color[matroid_id][v] = current_color;
        if (log) {
            last_painted.push_back(v);
        }
        for (auto [to, to_id] : g[matroid_id][v]) {
            if (to_id == id || banned_id == to_id) {
                continue;
            }
            self(self, matroid_id, to, to_id, log);
        }
    };

    auto paint_graph = [&](size_t matroid_id, size_t banned) -> void {
        graph_color[matroid_id].assign(n, 0);
        current_color = 1;
        banned_id = banned;
        for (size_t v = 0; v != n; ++v) {
            dfs_paint(dfs_paint, matroid_id, v, m * 2);
            ++current_color;
        }
        banned_id = INF;
    };

    auto paint_comp = [&](size_t matroid_id, size_t id) -> void {
        banned_id = id;
        last_painted.clear();
        dfs_paint(dfs_paint, matroid_id, edge[id].v, id, true);
        banned_id = INF;
    };

    auto repaint_comp = [&](size_t matroid_id, size_t id) -> void {
        for (size_t v : last_painted) {
            graph_color[matroid_id][v] = graph_color[matroid_id][edge[id].u];
        }
        last_painted.clear();
    };

    auto graph_independent = [&](size_t matroid_id, size_t id) -> bool {
        size_t u = edge[id].u;
        size_t v = edge[id].v;

        return graph_color[matroid_id][u] != graph_color[matroid_id][v];
    };

    // bfs
    vector<vector<size_t>> replaced_g(m);  // now reverse edges

    vector<size_t> dist(m, INF);
    vector<size_t> prev(m, INF);
    queue<size_t> que;

    auto bfs = [&](size_t start) -> void {
        dist.assign(m, INF);
        prev.assign(m, INF);

        // for (size_t start : s) {
        //     dist[start] = 0;
        //     que.push(start);
        // }
        dist[start] = 0;
        que.push(start);

        while (!que.empty()) {
            size_t v = que.front();
            que.pop();

            for (size_t to : replaced_g[v]) {
                if (dist[to] == INF) {
                    dist[to] = dist[v] + 1;
                    prev[to] = v;
                    que.push(to);
                }
            }
        }
    };

    vector<size_t> base_id(m, INF);
    vector<set<size_t>> base(1);

    base_id[0] = 0;
    base[0].insert(0);

    for (size_t item = 1; item != m; ++item) {
        // cerr << item << '\n';

        for (size_t e = 0; e != m; ++e) {
            replaced_g[e].clear();
        }

        vector<set<size_t>> s(MATROID);
        // vector<size_t> in_s(m, INF);

        for (size_t matroid_id = 0; matroid_id != base.size(); ++matroid_id) {

            for (size_t v = 0; v != n; ++v) {
                g[matroid_id][v].clear();
            }

            for (size_t id : base[matroid_id]) {
                size_t u = edge[id].u;
                size_t v = edge[id].v;
                g[matroid_id][u].push_back({v, id});
                g[matroid_id][v].push_back({u, id});
            }
            
            paint_graph(matroid_id, INF);

            for (size_t y : base[matroid_id]) {
                size_t u = edge[y].u;
                size_t v = edge[y].v;
                
                paint_comp(matroid_id, y);

                for (size_t x = 0; x != item; ++x) {
                    if (base[matroid_id].count(x)) {
                        continue;
                    }
                    if (graph_independent(matroid_id, x)) {
                        // replaced_g[y].push_back(x);
                        replaced_g[x].push_back(y);
                    }
                }

                if (graph_independent(matroid_id, item)) {
                    // replaced_g[y].push_back(item);
                    replaced_g[item].push_back(y);
                }

                repaint_comp(matroid_id, y);
            }

            for (size_t x = 0; x != item; ++x) {
                if (base[matroid_id].count(x)) {
                    continue;
                }
                if (graph_independent(matroid_id, x)) {
                    // s.push_back(x);
                    // in_s[x] = matroid_id;
                    s[matroid_id].insert(x);
                }
            }

            if (graph_independent(matroid_id, item)) {
                s[matroid_id].insert(item);
            }
        }

        bfs(item);

        bool found = false;
        for (size_t matroid_id = 0; matroid_id != base.size(); ++matroid_id) {

            size_t best_v = INF;
            size_t best_dist = INF;

            for (size_t from : s[matroid_id]) {
                if (dist[from] < best_dist) {
                    best_dist = dist[from];
                    best_v = from;
                }
            }

            if (best_dist == INF) {
                continue;
            }

            vector<size_t> path;
            for (;;) {
                path.push_back(best_v);
                if (dist[best_v] == 0) {
                    break;
                }
                best_v = prev[best_v];
            }

            reverse(path.begin(), path.end());

            // size_t x = item;

            for (size_t i = 0; i != path.size(); ++i) {
                size_t x = path[i];
                if (i != path.size() - 1) {
                    size_t prev_x = path[i + 1];
                    size_t prev_x_base = base_id[prev_x];
                    base[prev_x_base].erase(prev_x);
                    base_id[prev_x] = INF;
                    base[prev_x_base].insert(x);
                    base_id[x] = prev_x_base;
                } else {
                    base[matroid_id].insert(x);
                    base_id[x] = matroid_id;
                }
            }


            found = true;
            break;
        }

        if (!found) {
            base.push_back({item});
            base_id[item] = base.size() - 1;
        }
    }

    vector<size_t> span;
    for (size_t matroid_id = 0; matroid_id != base.size(); ++matroid_id) {
        if (base[matroid_id].size() == n - 1) {
            span.push_back(matroid_id);
        }
    }

    cout << span.size() << '\n';
    for (auto matroid_id : span) {
        for (size_t id : base[matroid_id]) {
            cout << id + 1 << ' ';
        }
        cout << '\n';
    }
}
