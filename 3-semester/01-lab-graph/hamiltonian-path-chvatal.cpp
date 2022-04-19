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

    vector<vector<bool>> g(n, vector<bool> (n, false));
    for (size_t i = 0; i != n; ++i) {
        string to;
        getline(cin, to);
        if (i == 0) {
            getline(cin, to);
        }
        for (size_t j = 0; j != to.size(); ++j) {
            if (to[j] == '1') {
                g[i][j] = g[j][i] = true;
            }
        }
    }

    for (;;) {
        vector<size_t> order(n);
        for (size_t i = 0; i != n; ++i) {
            order[i] = i;
        }
        random_shuffle(order.begin(), order.end());

        bool ok = true;
        size_t head;
        for (head = 0; head != n * n; ++head) {
            size_t v = order[head];
            size_t u = order[head + 1];
            if (g[v][u] == false) {
                size_t i;
                for (i = head + 2; i != order.size() && (!g[v][order[i]] || !g[order[i + 1]][u]); ++i)
                    ;

                if (i == order.size()) {
                    for (i = head + 2; i != order.size() && !g[v][order[i]]; ++i)
                        ;
                }

                if (i == order.size()) {
                    ok = false;
                    break;
                }
                for (size_t j = head + 1; j < i; ++j, --i) {
                    swap(order[j], order[i]);
                }
            }
            order.push_back(order[head]);
        }

        if (!ok) {
            continue;
        }

        for (size_t i = head; i != head + n - 1 && ok; ++i) {
            if (!g[order[i]][order[i + 1]]) {
                ok = false;
            }
        }
        if (!g[order.back()][order[head]]) {
            ok = false;
        }

        if (!ok) {
            continue;
        }

        for (size_t i = head; i != head + n; ++i) {
            cout << ++order[i] << ' ';
        }
        break;
    }

}