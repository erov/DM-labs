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
		freopen("minimization.in", "r", stdin);
		freopen("minimization.out", "w", stdout);
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
struct DFA {
	int n, k;
	bitset<MAXN> term;
	vector<vector<vector<int>>> g;
};

void make(vector<vector<pair<char, int>>> &g, DFA &a) {
 	int n = size(g);
    // vector<vector<pair<char, int>>> g(n);
    vector<vector<int>> rg(n);
    // for (int i = 0; i < m; ++i) {
    //     int u, v;
    //     char c;
    //     cin >> u >> v >> c;
    //     g[--u].push_back({c, --v});
    //     rg[v].push_back(u);
    // }
    for (int i = 0; i < n; ++i) {
    	for (auto [ch, to] : g[i]) {
    		rg[to].push_back(i);
    	}
    }
 
    vector<int> used(n, 0);
    queue<int> q;
 
    for (int v = 0; v < a.n; ++v) {
    	if (!a.term[v]) {
    		continue;
    	}
        q.push(v);
        used[v] = 1;
    }

    q.push(0);
    used[0] = true;
 
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : rg[v]) {
             if (!used[to]) {
                used[to] = 1;
                q.push(to);
            }
        }
    }
 
    vector<vector<pair<char, int>>> new_g(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            continue;
        }
        for (auto to : g[i]) {
            if (used[to.s]) {
                new_g[i].push_back(to);
            }
        }
    }
    swap(g, new_g);
}

void make2(vector<vector<pair<char, int>>> &g, DFA &a) {
 	int n = size(g);
    // vector<vector<pair<char, int>>> g(n);
    // vector<vector<int>> rg(n);
    // for (int i = 0; i < m; ++i) {
    //     int u, v;
    //     char c;
    //     cin >> u >> v >> c;
    //     g[--u].push_back({c, --v});
    //     rg[v].push_back(u);
    // }
    // for (int i = 0; i < n; ++i) {
    // 	for (auto [ch, to] : g[i]) {
    // 		rg[to].push_back(i);
    // 	}
    // }
 
    vector<int> used(n, 0);
    queue<int> q;
 
    // for (int v = 0; v < a.n; ++v) {
    // 	if (!a.term[v]) {
    // 		continue;
    // 	}
    //     q.push(v);
    //     used[v] = 1;
    // }

    q.push(0);
    used[0] = true;
 
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [ch, to] : g[v]) {  // for (int to : rg[v])
             if (!used[to]) {
                used[to] = 1;
                q.push(to);
            }
        }
    }
 
    vector<vector<pair<char, int>>> new_g(n);
    for (int i = 0; i < n; i++) {
        if (!used[i]) {
            a.term.set(i, 0);
            continue;
        }
        for (auto to : g[i]) {
            if (used[to.s]) {
                new_g[i].push_back(to);
            }
        }
    }

    swap(g, new_g);
}

void solve() {
	DFA a;
	int m;
	cin >> a.n >> m >> a.k;

	for (int i = 0; i < a.k; ++i) {
		int v;
		cin >> v;
		a.term.set(--v, 1);
	}

	vector<vector<pair<char, int>>> g(a.n);
	a.g.resize(a.n, vector<vector<int>> (26));
	for (int i = 0; i < m; ++i) {
		int u, v;
		char c;
		cin >> u >> v >> c;
		g[--u].push_back({c, --v});
		// a.g[--v][c - 'a'].push_back(--u);
	}


	make2(g, a);
	make(g, a);

	for (int i = 0; i < a.n; i++) {
		for (auto [ch, to] : g[i]) {
			a.g[to][ch - 'a'].push_back(i);
		}
	}

	vector<unordered_set<int>> storage(2);
	vector<int> ids(MAXN);
	for (int v = 0; v < a.n; ++v) {
		storage[a.term[v]].insert(v);
		ids[v] = a.term[v];
	}

	// for (int i = 0; i < size(storage); ++i) {
	// 	cout << "i=" << i << "\n";
	// 	for (auto it : storage[i]) {
	// 		cout << it << ' ';
	// 	}
	// 	cout << '\n';
	// }
	// cout << '\n';

	queue<pair<int, int>> q;
	for (int ch = 0; ch < 26; ++ch) {
		q.push({1, ch});
	}
	for (int ch = 0; ch < 26; ++ch) {
		q.push({0, ch});
	}

	while (!q.empty()) {
		auto [class_id, ch] = q.front();
		q.pop();

		// cout << class_id << ' ' << ch << ": ";
		unordered_map<int, vector<int>> from;
		for (int i : storage[class_id]) {
			for (int j : a.g[i][ch]) {
				from[ids[j]].push_back(j);
				// cout << ids[j] << ' ';
			}
		}
		// cout << '\n';

		for (auto [i, to_change] : from) {
			if (size(to_change) < size(storage[i])) {
				storage.push_back(unordered_set<int>());
				for (int v : to_change) {
					storage[i].erase(v);
					storage.back().insert(v);
				}
				if (size(storage.back()) > size(storage[i])) {
					storage.back().swap(storage[i]);
				}
				for (int v : storage.back()) {
					ids[v] = size(storage) - 1;
				}
				for (int c = 0; c < 26; c++) {
					q.push({size(storage) - 1, c});
				}
			}
		}
	}

	// for (int i = 0; i < size(storage); ++i) {
	// 	cout << "i=" << i << "\n";
	// 	for (auto it : storage[i]) {
	// 		cout << it << ' ';
	// 	}
	// 	cout << '\n';
	// }

	// vector<int> coords;

	// for (int i = 0; i < size(storage); ++i) {
	// 	if (size(storage[i]) > 0 && i != ids[0]) {
	// 		coords.push_back(i);
	// 	}
	// }

	// unordered_map<int, int> original_class;

	// original_class[ids[0]] = 0;

	// for (int i = 0; i < size(coords); ++i) {
	// 	original_class[coords[i]] = i + 1;
	// }


	// set<int> new_term;
	// for (int i = 0; i < a.n; i++) {
	// 	if (a.term[i] && original_class.count(ids[i])) {
	// 		new_term.insert(original_class[ids[i]]);
	// 	}
	// }


	set<pair<pair<int, int>, char>> already, edges;

	for (int i = 0; i < a.n; i++) {
		for (int c = 0; c < 26; ++c) {
			for (auto from : a.g[i][c]) {
				already.insert({{ids[from], ids[i]}, char(c + 'a')});
			}
		}
	}

	vector<int> original_class(size(storage), -1);
	int current = 1;
	original_class[ids[0]] = 0;

	for (auto it : already) {
		if (original_class[it.f.f] == -1) {
			original_class[it.f.f] = current++;
		}
		if (original_class[it.f.s] == -1) {
			original_class[it.f.s] = current++;
		}
		edges.insert({{original_class[it.f.f], original_class[it.f.s]}, it.s});
	}


	set<int> new_term;
	for (int i = 0; i < a.n; i++) {
		if (a.term[i]) {
			new_term.insert(original_class[ids[i]]);
		}
	}

	cout << current << ' ' << size(edges) << ' ' << size(new_term) << '\n';

	for (auto t : new_term) {
		cout << ++t << ' ';
	}
	cout << '\n';

	for (auto it : edges) {
		cout << ++it.f.f << ' ' << ++it.f.s << ' ' << it.s << '\n';
	}
}

/*
3 2 1
3
1 2 a
2 3 a

4 8 2
1 4
1 2 a
2 1 a
1 3 b
3 1 b
2 4 b
4 2 b
3 4 a
4 3 a
*/