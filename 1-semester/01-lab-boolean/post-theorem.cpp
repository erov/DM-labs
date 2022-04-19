#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<int> zheg_poly(string &s) {
	vector<int> poly, row;
	for (auto i : s) {
		row.push_back(i - '0');
	}
	poly.push_back(row[0]);
	while (size(row) > 1) {
		vector<int> nxt;
		for (int i = 1; i < size(row); i++) {
			nxt.push_back(row[i] ^ row[i - 1]);
		}
		row.swap(nxt);
		poly.push_back(row[0]);
	}
	return poly;
}

void add(vector<bool> &ans, int n, string &s) {
	ans[0] = ans[0] | (s[0] != '0');
	ans[1] = ans[1] | (s.back() != '1');

	vector<int> poly = zheg_poly(s);
	int deg = 0;
	for (int i = 0; i < size(s); i++) {
		if (poly[i]) {
			deg = max(deg, __builtin_popcount(i));
		}
	}
	ans[2] = ans[2] | (deg > 1);

	for (int i = 0; i < size(s); i++) {
		for (int j = 0; j < i; j++) {
			bool more = true;
			for (int k = 0; k < n; k++) {
				more &= (((j >> k) & 1) <= ((i >> k) & 1));
			}
			if (more) {
				if (s[j] == '1' && s[i] == '0') {
					ans[3] = true;
				}
			}
		}
	}

	for (int i = 0; i < size(s); i++) {
		ans[4] = ans[4] | (s[i] == s[size(s) - 1 - i]);
	}
}

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

	vector<bool> ans(5, false);
    while (n--) {
    	int m;
    	string s;
    	cin >> m >> s;
    	add(ans, m, s);
    }

    cout << (ans[0] & ans[1] & ans[2] & ans[3] & ans[4] ? "YES" : "NO");
}