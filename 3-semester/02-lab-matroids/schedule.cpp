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
     freopen("schedule.in", "r", stdin);
     freopen("schedule.out", "w", stdout);
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

    vector<pair<int32_t, uint32_t>> action(n);
    for (size_t i = 0; i != n; ++i) {
        cin >> action[i].first >> action[i].second;
    }

    sort(action.begin(), action.end(), [](pair<int32_t, uint32_t>& a, pair<int32_t, uint32_t>& b) -> bool {
        return a.second > b.second;
    });

    uint64_t ans = 0;
    unordered_map<int32_t, int32_t> prev;

    auto find_time = [&](auto& self, int32_t t) -> uint64_t {
        if (!prev.count(t)) {
            return prev[t] = t - 1;
        }
        if (prev[t] == -1) {
            return -1;
        }
        return prev[t] = self(self, prev[t]);
    };

    for (auto [t, w] : action) {
        int32_t t_real = find_time(find_time, t);
        if (t_real == -1) {
            ans += w;
        }
    }

    cout << ans;
}
