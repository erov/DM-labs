#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <random>
#include <deque>
#include <queue>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>
#include <bitset>
#include <stack>
#include <climits>
#include <cstddef>

using namespace std;
using ll = long long;

const double PI = acos(-1);
const ll oo = LLONG_MAX;

#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define mp(a, b) make_pair(a, b)
#define size(a) (int)a.size()
#define f first
#define s second

void solve();

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("problem4.in", "r", stdin);
		freopen("problem4.out", "w", stdout);
	#endif
	ios_base::sync_with_stdio(false);
	#ifdef HOME
		clock_t start = clock();
	#endif

	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
		// system("pause");
	#endif

	exit(0);
}

void dfs(vector<vector<pair<char, int>>> &g, vector<int> &used, vector<int> &ts, bool &acyclic, int v) {
	used[v] = 1;
	for (auto to : g[v]) {
		if (used[to.s] == 1) {
			acyclic = false;
		}
		if (!used[to.s]) {
			dfs(g, used, ts, acyclic, to.s);
		}
	}
	used[v] = 2;
	ts.push_back(v);
}

void solve() {
	int n, m, k, l;
	cin >> n >> m >> k >> l;

	vector<int> term(k);
	for (int i = 0; i < k; ++i) {
		cin >> term[i];
		--term[i];
	}

	vector<vector<pair<char, int>>> g(n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		g[--u].push_back({c, --v});
	}

	vector<int> dp(n, 0);
	dp[0] = 1;
	int const MOD = (int) 1e9 + 7;

	while (l--) {
		vector<int> nxt(n, 0);
		for (int i = 0; i < n; i++) {
			if (!dp[i]) {
				continue;
			}
			for (auto to : g[i]) {
				nxt[to.s] += dp[i];
				nxt[to.s] %= MOD;
			}
		}
		dp.swap(nxt);
	}

	int ans = 0;
	for (int v : term) {
		ans += dp[v];
		ans %= MOD;
	}
	cout << ans;
}
