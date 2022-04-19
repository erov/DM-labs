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
		freopen("problem2.in", "r", stdin);
		freopen("problem2.out", "w", stdout);
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

void solve() {
	string str;
	cin >> str;

	int n, m, k;
	cin >> n >> m >> k;

	int const MAXN = 100;
	bitset<MAXN> term;

	for (int i = 0; i < k; i++) {
		int v;
		cin >> v;
		term.set(--v);
	}

	vector<vector<pair<char, int>>> g(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		g[--u].push_back({c, --v});
	}

	bitset<MAXN> cur;
	cur.set(0, 1);
	for (char c : str) {
		bool ok = false;
		bitset<MAXN> nxt;
		for (int i = 0; i < MAXN; ++i) {
			if (!cur[i]) {
				continue;
			}
			for (auto to : g[i]) {
				if (to.f == c) {
					nxt.set(to.s, 1);
					ok = true;
				}
			}
		}
		swap(cur, nxt);
		if (!ok) {
			cout << "Rejects";
			return;
		}
	}

	cur &= term;
	cout << (cur.count() ? "Accepts" : "Rejects");
}
