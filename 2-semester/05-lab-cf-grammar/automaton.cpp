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
		freopen("automaton.in", "r", stdin);
		freopen("automaton.out", "w", stdout);
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

    map<string, vector<string>> single;
    map<string, vector<string>> double_;

    for (size_t i = 0; i != n; ++i) {
        string from, to;
        cin >> from >> to >> to;
        if (to.size() == 1) {
            single[from].push_back(to);
        } else {
            double_[from].push_back(to);
        }
    }

    size_t q;
    cin >> q;
    for (size_t i = 0; i != q; ++i) {
        string query;
        cin >> query;

        set<char> current;
        current.insert(start);
        for (size_t j = 0; j != query.size() - 1; ++j) {
            set<char> to;
            for (auto from : current) {
                string str_from = string(1, from);
                for (auto nxt : double_[str_from]) {
                    if (nxt[0] == query[j]) {
                        to.insert(nxt[1]);
                    }
                }
            }
            current.swap(to);
        }
        
        bool found = false;
        for (auto from : current) {
            string str_from = string(1, from);
            for (auto nxt : single[str_from]) {
                if (nxt[0] == query.back()) {
                    found = true;
                    break;
                }
            }
        }

        cout << (found ? "yes\n" : "no\n");
    }
}

