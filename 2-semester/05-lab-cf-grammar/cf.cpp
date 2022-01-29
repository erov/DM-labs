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
		freopen("cf.in", "r", stdin);
		freopen("cf.out", "w", stdout);
	#endif

	ios_base::sync_with_stdio(false);
	cin.tie(0);
	solve();

	#ifdef HOME
		cout <<  "\n\n\nTIME: " << float(clock() - start) / CLOCKS_PER_SEC << endl;
	#endif
}

constexpr size_t MAXN = 310;

void dfs(vector<vector<uint32_t>> &single, vector<bool> &used, uint32_t v) {
	used[v] = true;
	for (auto to : single[v]) {
		if (!used[to]) {
			dfs(single, used, to);
		}
	}
}

void solve() {
	size_t n;
    char start;
    cin >> n >> start;

    vector<vector<uint32_t>> single(MAXN);
    vector<vector<char>> to_term(MAXN);
    vector<set<pair<uint32_t, uint32_t>>> g(MAXN);

    uint32_t additional = 26;
    vector<uint32_t> noterm_by_term(26, 0);

    vector<bool> eps(MAXN, false);

    for (size_t i = 0; i != n; ++i) {
        string str_from, to;
        cin >> str_from;
        getline(cin, to);

        uint32_t from = str_from[0] - 'A';
 
        if (to.size() <= 4) {
            eps[from] = true;
        } else {
            to = to.substr(4);
            if (to.size() == 1) {
            	if ('a' <= to[0] && to[0] <= 'z') {
            		to_term[from].push_back(to[0]);
            	} else {
            		single[from].push_back(to[0] - 'A');
            	}
            } else {
            	vector<uint32_t> current;
            	for (auto it : to) {
            		if ('a' <= it && it <= 'z') {
            			if (noterm_by_term[it - 'a'] == 0) {
            				uint32_t new_noterm = additional++;
		            		noterm_by_term[it - 'a'] = new_noterm;
		            		to_term[new_noterm].push_back(it);
		            	}
            			current.push_back(noterm_by_term[it - 'a']);
            		} else {
            			current.push_back(it - 'A');
            		}
            	}
            	// g[from].push_back(current);
            	if (current.size() > 2) {
            		uint32_t prev = from;
            		for (size_t j = 0; j != current.size() - 2; ++j) {
            			uint32_t nxt = additional++;
            			g[prev].insert({current[j], nxt});
            			// cout << prev << "->" << current[i] << ", " << nxt << '\n';
            			prev = nxt;
            		}
            		g[prev].insert({current[current.size() - 2], current.back()});
            		// cout << prev << "->" << current[current.size() - 2] << ", " << current.back() << '\n';
            	} else {
            		g[from].insert({current[0], current[1]});
            		// cout << from << "->" << current[0] << ", " << current[1] << '\n';
            	}
            }
        }
    }


 //    cout << "without long rules:\n";
	// for (auto [from, list_to] : g) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> ";
 //    		for (auto item : to) {
 //    			cout << item << ' ';
 //    		}
 //    		cout << '\n';
 //    	}
 //    }

 //    for (auto [from, list_to] : single) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> " << to;
 //    		cout << '\n';
 //    	}
 //    }

 //    for (auto [from, list_to] : to_term) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> " << to;
 //    		cout << '\n';
 //    	}
 //    }
 //    cout << "==============\n";

    while (true) {
        bool found_eps = false;
        for (size_t from = 0; from != MAXN; ++from) {
            if (eps[from]) {
                continue;
            }
            for (auto to : g[from]) {
                bool to_eps = true;
                if (!eps[to.first]) {
                    to_eps = false;
                }
                if (!eps[to.second]) {
                    to_eps = false;
                }
                if (to_eps) {
                    found_eps = true;
                    eps[from] = true;
                }
            }
        }
   		for (size_t from = 0; from != MAXN; ++from) {
        	if (eps[from]) {
        		continue;
        	}
        	for (auto to : single[from]) {
	        	if (eps[to]) {
	        		found_eps = true;
	        		eps[from] = true;;
	        	}
	        }
        }
        if (!found_eps) {
            break;
        }
    }


    // cout << "eps-product: ";
    // for (auto it : eps) {
    // 	cout << it << " ";
    // }
    // cout << '\n';


	// unordered_map<string, vector<vector<string>>> new_g;
	for (size_t from = 0; from != MAXN; ++from) {
		for (auto to : g[from]) {
			if (eps[to.first]) {
				single[from].push_back({to.second});
			}
			if (eps[to.second]) {
				single[from].push_back({to.first});
			}
		}
	}

	// g.swap(new_g);


 //    cout << "without eps-product rules:\n";
 //    for (auto [from, list_to] : g) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> ";
 //    		for (auto item : to) {
 //    			cout << item << ' ';
 //    		}
 //    		cout << '\n';
 //    	}
 //    }
	// cout << '\n';
 //    for (auto [from, list_to] : single) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> " << to;
 //    		cout << '\n';
 //    	}
 //    }
 //    cout << '\n';
 //    for (auto [from, list_to] : to_term) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> " << to;
 //    		cout << '\n';
 //    	}
 //    }
 //    cout << "==============\n";

	vector<vector<uint32_t>> new_single(MAXN);
    for (size_t from = 0; from != additional; ++from) {
    	// cout << "from " << from << "\n";
    	vector<bool> used(additional, false);
    	// cout << single.size() << '\n';
    	dfs(single, used, from);
    	// cout << single.size() << '\n';
    	for (size_t to = 0; to != additional; ++to) {
    		if (!used[to]) {
    			continue;
    		}
    		if (to != from) {
    			new_single[from].push_back(to);
    		}
    	}
    }
    single.swap(new_single);

	// cout << "transitive closure:\n";
	// for (auto [from, list_to] : single) {
	// 	for (auto to : list_to) {
	// 		cout << from << " -> " << to << '\n';
	// 	}
	// }

	vector<pair<uint32_t, uint32_t>> append;
	for (size_t from = 0; from != MAXN; ++from) {
		for (auto to : single[from]) {
			for (auto term : to_term[to]) {
				append.push_back({from, term});
			}
			for (auto noterm : g[to]) {
				g[from].insert(noterm);
			}
		}
	}

	for (auto [from, to] : append) {
		to_term[from].push_back(to);
	}

	// cout << "without cycle rules:\n";
 //    for (auto [from, list_to] : g) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> ";
 //    		for (auto item : to) {
 //    			cout << item << ' ';
 //    		}
 //    		cout << '\n';
 //    	}
 //    }

 //    for (auto [from, list_to] : single) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> " << to;
 //    		cout << '\n';
 //    	}
 //    }

 //    for (auto [from, list_to] : to_term) {
 //    	for (auto to : list_to) {
 //    		cout << from << " -> " << to;
 //    		cout << '\n';
 //    	}
 //    }
 //    cout << "==============\n";


    string w;
    cin >> w;

    size_t m = w.size();

    vector<vector<vector<bool>>> dp(MAXN);
    for (size_t it = 0; it != MAXN; ++it) {
        dp[it].resize(m + 1, vector<bool>(m + 1, false));
    }

    // for (auto [from, to_list] : to_term) {
    for (size_t from = 0; from != MAXN; ++from) {
        for (auto to : to_term[from]) {
            for (size_t l = 0; l != m; ++l) {
                dp[from][l][l + 1] = (w[l] == to);
            }
        }
    }

    vector<uint32_t> ids;
    for (size_t i = 0; i != MAXN; ++i) {
    	if (!g[i].empty()) {
    		ids.push_back(i);
    	}
    }

    for (size_t len = 2; len != m + 1; ++len) {
        for (size_t l = 0; l != m && l + len <= m; ++l) {
            size_t r = l + len;
            for (size_t k = l + 1; k < r; ++k) {
                for (uint32_t current : ids) {
                    for (auto to : g[current]) {
                        dp[current][l][r] = dp[current][l][r] | (dp[to.first][l][k] & dp[to.second][k][r]);
                    }
                }
            }
        }
    }
    cout << (dp[start - 'A'][0][m] ? "yes" : "no");
}