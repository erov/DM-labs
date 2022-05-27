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
		freopen("isomorphism.in", "r", stdin);
		freopen("isomorphism.out", "w", stdout);
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


int const MAXN = 100'000;
struct DFA {
	int n, k;
	bitset<MAXN> term;
	vector<vector<pair<char, int>>> g;
};

string check_isomorphism(DFA &a, DFA &b) {
	if (a.n != b.n || a.k != b.k) {
		return "NO";
	}
	vector<bool> used(a.n, false);
	used[0] = true;
	queue<pair<int, int>> q;
	q.push({0, 0});

	while (!q.empty()) {
		auto [v, u] = q.front();
		q.pop();

		if (a.term[v] ^ b.term[u]) {
			return "NO";
		}

		if (size(a.g[v]) != size(b.g[u])) {
			return "NO";
		}
		sort(all(a.g[v]));
		sort(all(b.g[u]));
		for (int i = 0; i < size(a.g[v]); ++i) {
			if (a.g[v][i].f != b.g[u][i].f) {
				return "NO";
			}
			if (!used[a.g[v][i].s]) {
				used[a.g[v][i].s] = true;
				q.push({a.g[v][i].s, b.g[u][i].s});
			}
		}
	}

	return "YES";
}

void solve() {
	DFA a, b;
	int m;
	cin >> a.n >> m >> a.k;

	for (int i = 0; i < a.k; ++i) {
		int v;
		cin >> v;
		a.term.set(--v, 1);
	}

	a.g.resize(a.n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		a.g[--u].push_back({c, --v});
	}

	cin >> b.n >> m >> b.k;

	for (int i = 0; i < b.k; ++i) {
		int v;
		cin >> v;
		b.term.set(--v, 1);
	}

	b.g.resize(b.n);
	for (int i = 0; i < m; ++i) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		b.g[--u].push_back({c, --v});
	}

	cout << check_isomorphism(a, b);
}
