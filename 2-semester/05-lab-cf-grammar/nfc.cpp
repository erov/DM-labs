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

using namespace std;

const double PI = acos(-1);
const long long INF = LLONG_MAX;

void solve();

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
		clock_t start = clock();
	#else
		freopen("nfc.in", "r", stdin);
		freopen("nfc.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
	#endif
}

void solve() {
	size_t n;
    char start;
    cin >> n >> start;

    unordered_map<string, vector<string>> single;
    unordered_map<string, vector<string>> double_;

    unordered_set<string> noterm;
    noterm.insert(string(1, start));

    for (size_t i = 0; i != n; ++i) {
        string from, to;
        cin >> from >> to >> to;

        noterm.insert(from);
        if (to.size() == 1) {
            single[from].push_back(to);
        } else {
            double_[from].push_back(to);
            noterm.insert(string(1, to[0]));
            noterm.insert(string(1, to[1]));
        }
    }

    string w;
    cin >> w;

    size_t m = w.size();

    unordered_map<string, vector<vector<uint64_t>>> dp;
    for (auto it : noterm) {
        dp[it].resize(m + 1, vector<uint64_t>(m + 1, 0));
    }

    for (auto [from, to_list] : single) {
        for (auto to : to_list) {
            for (size_t l = 0; l != m; ++l) {
                dp[from][l][l + 1] += (w[l] == to[0] ? 1 : 0);
            }
        }
    }

    const uint64_t MOD = 1'000'000'007;
    for (size_t len = 2; len != m + 1; ++len) {
        for (size_t l = 0; l != m && l + len <= m; ++l) {
            size_t r = l + len;
            for (size_t k = l + 1; k < r; ++k) {
                for (auto current : noterm) {
                    for (auto to : double_[current]) {
                        dp[current][l][r] += dp[string(1, to[0])][l][k] * dp[string(1, to[1])][k][r] % MOD;
                        dp[current][l][r] %= MOD;
                    }
                }
            }
        }
    }
    cout << dp[string(1, start)][0][m];
}

