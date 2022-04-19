#include <iostream>
#include <vector>
#include <assert.h>
#include <set>

using namespace std;

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("telemetry.in", "r", stdin);
		freopen("telemetry.out", "w", stdout);
	#endif

	int n, k;
	cin >> n >> k;

	vector<string> ans;
	string tmp = "0";
	for (int i = 0; i < k; i++) {
		tmp[0] =  char(i + '0');
		ans.push_back(tmp);
	}

	for (int i = 1; i < n; i++) {
		vector<string> nxt;
		bool type = 0;
		for (int p = 0; p < k; p++) {
			if (p % 2 == 0) {
				for (int j = 0; j < (int) ans.size(); j++) {
					nxt.push_back(ans[j] + char(p + '0'));
				}
			} else {
				for (int j = (int) ans.size() - 1; j >= 0; j--) {
					nxt.push_back(ans[j] + char(p + '0'));
				}
			}
		}
		ans.swap(nxt);
	}

	for (auto cur : ans) {
		cout << cur << '\n';
	}
}
