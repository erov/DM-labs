#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<bool> zheg_poly(vector<bool> row) {
	vector<bool> poly;

	poly.push_back(row[0]);
	while (size(row) > 1) {
		vector<bool> nxt;
		for (int i = 1; i < size(row); i++) {
			nxt.push_back(row[i] ^ row[i - 1]);
		}
		row.swap(nxt);
		poly.push_back(row[0]);
	}
	return poly;
}

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<bool> f(1 << n);
    for (int i = 0; i < (1 << n); i++) {
    	string s;
    	int val;
    	cin >> s >> val;
    	f[i] = (bool) val;
    }

    f = zheg_poly(f);
    for (int i = 0; i < (1 << n); i++) {
    	for (int j = n - 1; j >= 0; j--) {
    		cout << ((i >> j) & 1);
    	}
    	cout << ' ' << f[i] << '\n';
    }
}