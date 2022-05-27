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

    set<size_t> valid;
    for (size_t i = 1; i != n + 1; ++i) {
        valid.insert(i);
    }

    vector<size_t> p(n - 2);
    vector<size_t> cnt(n + 1, 0);
    for (size_t i = 0; i != n - 2; ++i) {
        cin >> p[i];
        ++cnt[p[i]];
        if (valid.count(p[i])) {
            valid.erase(p[i]);
        }
    }

    for (size_t ans : p) {
        cout << ans << ' ' << *valid.begin() << '\n';
        valid.erase(valid.begin());
        --cnt[ans];
        if (cnt[ans] == 0) {
            valid.insert(ans);
        }
    }

    cout << *valid.begin() << ' ' << *std::next(valid.begin());
}