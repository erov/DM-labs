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

void solve() {
    size_t n;
    cin >> n;

    vector<vector<bool>> g(n, vector<bool>(n, false));
    for (size_t i = 0; i != n; ++i) {
        string to;
        getline(cin, to);
        if (i == 0) {
            getline(cin, to);
        }

        for (size_t j = 0; j != to.size(); ++j) {
            if (to[j] == '1') {
                g[i][j] = true;
            } else {
                g[j][i] = true;
            }
        }
    }

    if (n == 1) {
        cout << 1;
        return;
    }
    
    vector<size_t> path = {0};

    for (size_t v = 1; v != n; ++v) {
        size_t i;
        for (i = 0; i != path.size() && g[path[i]][v]; ++i)
            ;
        path.insert(path.begin() + i, v);
    }

    for (size_t v = 0; v != path.size() - 1; ++v) {
        assert(g[path[v]][path[v + 1]]);
    }

    vector<size_t> cycle;
    size_t head;

    for (head = n - 1; head != 1; --head) {
        if (g[path[head]][path[0]]) {
            break;
        }
    }

    ++head;
    for (size_t i = 0; i != head; ++i) {
        cycle.push_back(path[i]);
    }

    for (; head != n;) {
        vector<size_t> to_add;

        for (; head != n;) {
            to_add.push_back(path[head]);
            ++head;

            for (size_t i = 0; i != cycle.size(); ++i) {
                if (g[to_add.back()][cycle[i]]) {
                    vector<size_t> new_cycle;
                    for (size_t it = 0; it != i; ++it) {
                        new_cycle.push_back(cycle[it]);
                    }
                    for (auto v : to_add) {
                        new_cycle.push_back(v);
                    }
                    for (size_t it = i; it != cycle.size(); ++it) {
                        new_cycle.push_back(cycle[it]);
                    }
                    to_add.clear();
                    cycle.swap(new_cycle);
                    break;
                }
            }
            // ++head;
            if (to_add.empty()) {
                break;
            }
        }

    }

    // assert(cycle.size() == n);

    // for (size_t v = 0; v != cycle.size(); ++v) {
    //     assert(g[cycle[v]][cycle[(v + 1) % n]]);
    // }

    for (auto v : cycle) {
        cout << ++v << ' ';
    }
}
