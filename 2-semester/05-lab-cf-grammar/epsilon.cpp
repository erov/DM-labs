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
		freopen("epsilon.in", "r", stdin);
		freopen("epsilon.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
	#endif
}

bool in_upper_case(string &str) {
    for (auto ch : str) {
        if ('a' <= ch && ch <= 'z') {
            return false;
        }
    }
    return true;
}

void solve() {
	size_t n;
    char start;
    cin >> n >> start;


    map<string, vector<string>> g;
    set<string> eps;
    for (size_t i = 0; i != n; ++i) {
        string from, to;
        cin >> from;
        getline(cin, to);

        if (to.size() <= 4) {
            eps.insert(from);
        } else {
            to = to.substr(4);
            if (in_upper_case(to)) {
                g[from].push_back(to);
            }
        }
    }

    while (true) {
        bool found_eps = false;
        for (auto [from, list_to] : g) {
            if (eps.count(from)) {
                continue;
            }
            for (auto to : list_to) {
                bool to_eps = true;
                for (auto item : to) {
                    if (!eps.count(string(1, item))) {
                        to_eps = false;
                    }
                }
                if (to_eps) {
                    found_eps = true;
                    eps.insert(from);
                }
            }
        }
        if (!found_eps) {
            break;
        }
    }

    for (auto it : eps) {
        cout << it << '\n';
    }
}

