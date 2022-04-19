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
		freopen("chaincode.in", "r", stdin);
		freopen("chaincode.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	string last = "";
	for (int i = 0; i < n; i++) {
		last += "0";
	}

	vector<string> ans;
	set<string> s;
	ans.push_back(last);
	s.insert(last);

	while (true) {
		bool found = false;
		string check = ans.back().substr(1) + "1";

		if (!s.count(check)) {
			ans.push_back(check);
			s.insert(check);
		} else {
			found = false;
			check = ans.back().substr(1) + "0";
			if (!s.count(check)) {
				ans.push_back(check);
				s.insert(check);
			} else {
				break;
			}
		}
	}

	for (auto cur : ans) {
		cout << cur << '\n';
	}
}
