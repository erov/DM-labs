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
     freopen("rainbow.in", "r", stdin);
     freopen("rainbow.out", "w", stdout);
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
        uint32_t color;
    };

    vector<edge_t> edge(m);
    for (size_t i = 0; i != m; ++i) {
        size_t u, v;
        uint32_t color;
        cin >> u >> v >> color;
        --u, --v;
        edge[i] = {u, v, color};
    }


    constexpr size_t INF = numeric_limits<size_t>::max();

    // M1 - rainbow

    constexpr size_t COLOR = 200;
    vector<size_t> color_cnt(COLOR, 0);

    auto rainbow_independent = [&](size_t id) -> bool {
        return color_cnt[edge[id].color] == 0;
    };

    auto rainbow_add = [&](size_t id) -> void {
        ++color_cnt[edge[id].color];
    };

    auto rainbow_rm = [&](size_t id) -> void {
        assert(color_cnt[edge[id].color] != 0);
        --color_cnt[edge[id].color];
    };


    // M2 - graph

    vector<vector<pair<size_t, size_t>>> g(n); // to, edge_id
    size_t banned_id = INF;
    // vector<size_t> used(n, 0);

    // auto dfs_cycle_check = [&](auto& self, size_t v, size_t id) -> bool {
    //     used[v] = 1;
    //     for (auto [to, to_id] : g[v]) {
    //         if (to_id == id || banned_id == to_id) {
    //             continue;
    //         }
    //         if (used[to] == 1) {
    //             return false;
    //         }
    //         if (used[to] == 0 && !self(self, to, to_id)) {
    //             return false;
    //         }
    //     }
    //     used[v] = 2;
    //     return true;
    // };

    // auto graph_independent = [&](size_t id) -> bool {
    //     size_t u = edge[id].u;
    //     size_t v = edge[id].v;

    //     // auto gv_iter = g[v].insert({u, id});
    //     // auto gu_iter = g[u].insert({v, id});
    //     g[v].push_back({u, id});
    //     g[u].push_back({v, id});
    //     used.assign(n, 0);

    //     // only 1 possible cycle
    //     bool result = dfs_cycle_check(dfs_cycle_check, v, m * 2);

    //     // g[u].erase({v, id});
    //     // g[v].erase({u, id});
    //     assert(g[u].back() == make_pair(v, id));
    //     g[u].pop_back();
    //     assert(g[v].back() == make_pair(u, id));
    //     g[v].pop_back();

    //     return result;
    // };

    vector<size_t> graph_color(n);
    size_t current_color;
    vector<size_t> last_painted;

    auto dfs_paint = [&](auto& self, size_t v, size_t id, bool log = false) -> void {
        graph_color[v] = current_color;
        if (log) {
            last_painted.push_back(v);
        }
        for (auto [to, to_id] : g[v]) {
            if (to_id == id || banned_id == to_id) {
                continue;
            }
            self(self, to, to_id, log);
        }
    };

    auto paint_graph = [&](size_t banned) -> void {
        graph_color.assign(n, 0);
        current_color = 1;
        banned_id = banned;
        for (size_t v = 0; v != n; ++v) {
            dfs_paint(dfs_paint, v, m * 2);
            ++current_color;
        }
        banned_id = INF;
    };

    auto paint_comp = [&](size_t id) -> void {
        banned_id = id;
        last_painted.clear();
        dfs_paint(dfs_paint, edge[id].v, id, true);
        banned_id = INF;
    };

    auto repaint_comp = [&](size_t id) -> void {
        for (size_t v : last_painted) {
            graph_color[v] = graph_color[edge[id].u];
        }
        last_painted.clear();
    };

    auto graph_independent = [&](size_t id) -> bool {
        size_t u = edge[id].u;
        size_t v = edge[id].v;

        return graph_color[u] != graph_color[v];
    };


    // bfs
    vector<size_t> dist(m, INF);
    vector<size_t> prev(m, INF);
    queue<size_t> que;

    auto bfs = [&](vector<size_t>& s, vector<vector<size_t>>& replaced_g) -> void {
        dist.assign(m, INF);
        prev.assign(m, INF);

        for (size_t start : s) {
            dist[start] = 0;
            que.push(start);
        }

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


    vector<bool> in_base(m, false);
    vector<size_t> base;
    vector<size_t> non_base;

    for (size_t x = 0; x != m; ++x) {
        non_base.push_back(x);
    }

    for (;;) {
        for (size_t i = 0; i != n; ++i) {
            g[i].clear();
        }
        color_cnt.assign(COLOR, 0);
        for (size_t id : base) {
            size_t u = edge[id].u;
            size_t v = edge[id].v;
            g[u].push_back({v, id});
            g[v].push_back({u, id});
            rainbow_add(id);
        }
        paint_graph(INF);

        vector<vector<size_t>> replaced_g(m);

        for (size_t y : base) {
            size_t u = edge[y].u;
            size_t v = edge[y].v;

            rainbow_rm(y);
            paint_comp(y);

            for (size_t x : non_base) {
                // rainbow:
                if (rainbow_independent(x)) {
                    replaced_g[y].push_back(x);
                }
                
                // graph:
                if (graph_independent(x)) {
                    replaced_g[x].push_back(y);
                }
            }

            repaint_comp(y);
            rainbow_add(y);
        }


        vector<size_t> s;
        vector<size_t> t;

        // paint_graph(INF);

        for (size_t x : non_base) {
            if (rainbow_independent(x)) {
                s.push_back(x);
            }
            if (graph_independent(x)) {
                t.push_back(x);
            }
        }

        bfs(s, replaced_g);

        size_t best_v = INF;
        size_t best_dist = INF;

        for (size_t to : t) {
            if (best_dist > dist[to]) {
                best_dist = dist[to];
                best_v = to;
            }
        }

        if (best_dist == INF) {
            break;
        }

        for (;;) {
            if (!in_base[best_v]) {
                in_base[best_v] = true;
            } else {
                in_base[best_v] = false;
            }
            if (dist[best_v] == 0) {
                break;
            }
            best_v = prev[best_v];
        }

        base.clear();
        non_base.clear();

        for (size_t i = 0; i != m; ++i) {
            if (in_base[i]) {
                base.push_back(i);
            } else {
                non_base.push_back(i);
            }
        }
    }

    cout << base.size() << '\n';
    for (size_t id : base) {
        cout << ++id << ' ';
    }
}
