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
		freopen("equivalence.in", "r", stdin);
		freopen("equivalence.out", "w", stdout);
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


int const MAXN = 1047;
int const LAST = 1000;
struct DFA {
	int n, k;
	bitset<MAXN> term;
	vector<vector<int>> g;
};

string check_equivalence(DFA &a, DFA &b) {
	vector<vector<bool>> used(MAXN, vector<bool> (MAXN, false));
	used[0][0] = true;
	queue<pair<int, int>> q;
	q.push({0, 0});

	while (!q.empty()) {
		auto [v, u] = q.front();
		q.pop();

		if (a.term[v] ^ b.term[u]) {
			return "NO";
		}

		for (int c = 0; c < 26; ++c) {
			int a_to = a.g[v][c], b_to = b.g[u][c];
			if (!used[a_to][b_to]) {
				used[a_to][b_to] = true;
				q.push({a_to, b_to});
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

	a.g.resize(MAXN, vector<int> (26, LAST));
	for (int i = 0; i < m; ++i) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		a.g[--u][c - 'a'] = --v;
	}

	cin >> b.n >> m >> b.k;

	for (int i = 0; i < b.k; ++i) {
		int v;
		cin >> v;
		b.term.set(--v, 1);
	}

	b.g.resize(MAXN, vector<int> (26, LAST));
	for (int i = 0; i < m; ++i) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		b.g[--u][c - 'a'] = --v;
	}

	cout << check_equivalence(a, b);
}
