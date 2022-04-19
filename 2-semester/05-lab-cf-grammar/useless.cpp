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
		freopen("useless.in", "r", stdin);
		freopen("useless.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
	#endif
}

void dfs(map<string, vector<string>> &g, set<string> &generating, map<string, bool> &used, string v) {
    used[v] = true;
    for (auto to : g[v]) {
        for (auto item : to) {
            if ('A' <= item && item <= 'Z' && !used[string(1, item)]) {
                dfs(g, generating, used, string(1, item));
            }
        }
    }
}

void solve() {
	size_t n;
    char start;
    cin >> n >> start;

    set<string> noterm;
    noterm.insert(string(1, start));

    map<string, vector<string>> g;
    for (size_t i = 0; i != n; ++i) {
        string from, to;
        cin >> from;
        getline(cin, to);

        noterm.insert(from);
        while (isspace(to.back())) {
            to.pop_back();
        }
        if (to.size() <= 4) {
            g[from].push_back("");
        } else {
            to = to.substr(4);
            g[from].push_back(to);
            for (auto it : to) {
                if ('A' <= it && it <= 'Z') {
                    noterm.insert(string(1, it));
                }
            }
        }
    }

    set<string> generating;
    for (auto [from, list_to] : g) {
        for (auto to : list_to) {
            bool valid = true;
            for (auto item : to) {
                if ('a' <= item && item <= 'z') {
                    ;
                } else {
                    valid = false;
                }
            }
            if (valid) {
                generating.insert(from);
            }
        }
    }

    while (true) {
        bool found_new = false;
        for (auto [from, list_to] : g) {
            if (generating.count(from)) {
                continue;
            }
            for (auto to : list_to) {
                bool valid = true;
                for (auto item : to) {
                    if ('A' <= item && item <= 'Z') {
                        if (!generating.count(string(1, item))) {
                            valid = false;
                            break;
                        }
                    }
                }
                if (valid) {
                    generating.insert(from);
                    found_new = true;
                    break;
                }
            }
        }
        if (!found_new) {
            break;
        }
    }

    {
        map<string, vector<string>> new_g;
        for (auto [from, list_to] : g) {
            if (generating.count(from)) {
                for (auto to : list_to) {
                    bool valid = true;
                    for (auto item : to) {
                        if ('A' <= item && item <= 'Z' && !generating.count(string(1, item))) {
                            valid = false;
                        }
                    }
                    if (valid) {
                        new_g[from].push_back(to);
                    }
                }
            }
        }
        g.swap(new_g);
    }

    map<string, bool> used;
    if (generating.count(string(1, start))) {
        dfs(g, generating, used, string(1, start));
    }
    
    set<string> useless;
    for (auto it : noterm) {
        if (!used[it]) {
            useless.insert(it);
        }
    }

    for (auto it : useless) {
        cout << it << ' ';
    }
}

