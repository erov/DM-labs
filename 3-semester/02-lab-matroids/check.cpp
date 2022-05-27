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
     freopen("check.in", "r", stdin);
     freopen("check.out", "w", stdout);
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

    set<uint32_t> independent;
    for (size_t i = 0; i != m; ++i) {
        size_t k;
        cin >> k;

        uint32_t value = 0;
        for (size_t j = 0; j != k; ++j) {
            size_t id;
            cin >> id;
            --id;
            value |= (1 << id);
        }

        independent.insert(value);
    }

    if (!independent.count(0)) {
        cout << "NO";
        return;
    }

    for (uint32_t a : independent) {
        for (uint32_t b = 0; b != (1 << n); ++b) {
            if ((a & b) == b) {
                if (!independent.count(b)) {
                    cout << "NO";
                    return;
                }
            }
        }
    }

    for (uint32_t a : independent) {
        for (uint32_t b : independent) {
            if (a == b || __builtin_popcount(a) <= __builtin_popcount(b)) {
                continue;
            }
            bool found = false;
            for (size_t i = 0; i != n; ++i) {
                if ((a & (1 << i)) != 0 && (b & (1 << i)) == 0) {
                    if (independent.count(b | (1 << i))) {
                        found = true;
                    }
                }
            }

            if (!found) {
                cout << "NO";
                return;
            }
        }
    }

    cout << "YES";
}
