#include <iostream>
#include <vector>
#include <assert.h>
#include <set>

using namespace std;

void gen(vector<string> &ans, int sz, int pos, string str) {
	if (sz == pos) {
		ans.push_back(str);
		return;
	}
	gen(ans, sz, pos + 1, str + "0");
	if (str.empty() || str.back() != '1') {
		gen(ans, sz, pos + 1, str + "1");
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("vectors.in", "r", stdin);
		freopen("vectors.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<string> ans;
	gen(ans, n, 0, "");

	cout << (int) ans.size() << '\n';
	for (auto cur : ans) {
		cout << cur << '\n';
	}
}
