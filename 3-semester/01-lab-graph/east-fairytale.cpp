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
        // freopen("input.txt", "r", stdin);
        // freopen("output.txt", "w", stdout);
        clock_t start_clock = clock();
    // #else
    //  freopen(".in", "r", stdin);
    //  freopen(".out", "w", stdout);
    #endif
    
    solve();

    #ifdef HOME
        system("pause");
        printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
    #endif
}

constexpr size_t MAXN = 1'000;
size_t questions = 10'000;
vector<vector<size_t>> g(MAXN);

bool ask(size_t a, size_t b) {
    assert(questions > 0);
    --questions;

    cout << 1 << ' ' << a << ' ' << b << endl;
    string ans;
    cin >> ans;
    
    if (ans == "YES") {
        g[--a].push_back(--b);
    } else {
        g[--b].push_back(--a);
    }
    return ans == "YES";
}

void dfs(vector<size_t>& used, size_t v) {
    used[v] = 1;

    for (size_t to : g[v]) {
        if (used[to] == 1) {
            cout << 0;
            for (size_t i = 0; i != used.size(); ++i) {
                cout << ' ' << 0;
            }
            cout << endl;
            exit(0);
        }

        if (used[to] == 0) {
            dfs(used, to);
        }
    }

    used[v] = 2;
}

void solve() {
    size_t n;
    cin >> n;

    if (n == 1) {
        cout << 0 << ' ' << 1 << endl;
        return;
    }

    vector<size_t> ans;
    if (ask(1, 2)) {
        ans = {1, 2};
    } else {
        ans = {2, 1};
    }
    for (size_t i = 3; i != n + 1; ++i) {
        size_t l = 0, r = i - 1;
        while (r - l > 1) {
            size_t mid = (l + r) / 2;
            if (ask(ans[mid], i) == 0) {
                r = mid;
            } else {
                l = mid;
            }
        }

        if (ask(ans[l], i)) {
            ans.insert(ans.begin() + l + 1, i);
        } else {
            ans.insert(ans.begin() + l, i);
        }
    }

    bool ok = true;
    vector<size_t> used(n, 0);

    for (size_t v = 0; v != n; ++v) {
        if (!used[v]) {
            dfs(used, v);
        }
    }

    cout << 0;
    for (size_t i = 0; i != n; ++i) {
        cout << ' ' << ans[i];
    }
    cout << endl;
}
