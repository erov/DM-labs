#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int depth(vector<vector<int>> &a, int v) {
	if (a[v].empty()) {
		return 0;
	}
	int mx = 0;
	for (int u : a[v]) {
		mx = max(mx, depth(a, u));
	}
	return mx + 1;
}

bool bf(vector<vector<int>> &a, map<int, vector<bool>> &values, vector<bool> &calc, int v) {
	if (a[v].empty()) {
		return calc[v];
	}
	int pos = 0;
	for (int u : a[v]) {
		pos = pos * 2 + bf(a, values, calc, u);
	}
	return values[v][pos];
}

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<int>> a(n);
    map<int, vector<bool>> values;
    vector<int> leaf;
    for (int i = 0; i < n; i++) {
    	int m;
    	cin >> m;
    	if (!m) {
    		leaf.push_back(i);
    	} else {
	    	for (int j = 0; j < m; j++) {
	    		int x;
	    		cin >> x;
	    		a[i].push_back(--x);
	    	}
	    	vector<bool> f(1 << m);
	    	for (int j = 0; j < (1 << m); j++) {
	    		int x;
	    		cin >> x;
	    		f[j] = (bool)x;
	    	}
	    	values[i] = f;
	    }
    }

    vector<bool> from(n, false);
    for (int i = 0; i < n; i++) {
    	for (auto j : a[i]) {
    		from[j] = 1;
    	}
    }

    int out;
    for (int i = 0; i < n; i++) {
    	if (!from[i]) {
    		out = i;
    	}
    }

    vector<bool> calc(n);

    cout << depth(a, out) << '\n';
    for (int mask = 0; mask < (1 << size(leaf)); mask++) {
    	for (int i = 0; i < size(leaf); i++) {
    		calc[leaf[size(leaf) - 1 - i]] = ((mask >> i) & 1);
    	}
    	cout << bf(a, values, calc, out);
    }
}