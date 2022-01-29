// #pragma GCC optimize("Ofast")
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
		freopen("problem5.in", "r", stdin);
		freopen("problem5.out", "w", stdout);
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

void tompson(vector<vector<pair<char, int>>> &g, vector<int> &term) {
	int const MAXN = 200;

	bitset<MAXN> old_term;
	for (int v : term) {
		old_term.set(v, 1);
	}
	bitset<MAXN> v;
	v.set(0, 1);

	vector<vector<pair<char, int>>> new_g(MAXN);
	unordered_map<bitset<MAXN>, int> get_id;
	get_id[v] = 0;
	queue<bitset<MAXN>> q;
	q.push(v);

	while (!q.empty()) {
		v = q.front();
		q.pop();
		
		int from = get_id[v];
		for (char ch = 'a'; ch <= 'z'; ++ch) {
			bitset<MAXN> nxt;
			for (int u = 0; u < MAXN; ++u) {
				if (!v[u]) {
					continue;
				}
				for (auto to : g[u]) {
					if (to.f == ch) {
						nxt.set(to.s);
					}
				}
			}

			if (!nxt.count()) {
				continue;
			}

			int id;
			if (get_id.count(nxt)) {
				id = get_id[nxt];
			} else {
				id = size(get_id);
				get_id[nxt] = id;
				q.push(nxt);
			}

			new_g[from].push_back({ch, id});
		}
	}

	g.swap(new_g);
	term.clear();
	for (auto it : get_id) {
		bool make_term = false;
		for (int j = 0; j < MAXN; ++j) {
			if (it.f[j]) {
				if (old_term[j]) {
					make_term = true;
				}
			}
		}
		if (make_term) {
			term.push_back(it.s);
		}
	}
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

	tompson(g, term);
	n = size(g);
	k = size(term);

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
