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
     freopen("cycles.in", "r", stdin);
     freopen("cycles.out", "w", stdout);
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

    struct item {
        uint32_t w;
        size_t id;
    };

    vector<item> elem(n);
    for (size_t i = 0; i != n; ++i) {
        uint32_t w;
        cin >> w;
        elem[i] = {w, i};
    }

    sort(elem.begin(), elem.end(), [](item& a, item& b) -> bool {
        return a.w > b.w;
    });

    set<uint32_t> cycles;
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

        // cout << value << '\n';

        cycles.insert(value);
    }

    uint32_t base = 0;
    uint32_t base_weight = 0;

    for (auto [w, id] : elem) {
        uint32_t try_base = (base | (1 << id));
        bool found = false;
        for (uint32_t c : cycles) {
            if ((try_base & c) == c) {
                found = true;
            }
        }
        if (!found) {
            base_weight += w;
            base |= (1 << id);
        }
    }

    cout << base_weight;
}
