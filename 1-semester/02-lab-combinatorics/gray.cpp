#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;


int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("gray.in", "r", stdin);
		freopen("gray.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<string> code(2);
	code[0] = "0";
	code[1] = "1";

	for (int i = 2; i <= n; i++) {
		vector<string> nxt;
		for (int j = 0; j < (int) code.size(); j++) {
			nxt.push_back("0" + code[j]);
		}
		for (int j = 0; j < (int) code.size(); j++) {
			nxt.push_back("1" + code[(int) code.size() - 1 - j]);
		}
		code.swap(nxt);
	}

	for (auto cur : code) {
		cout << cur << '\n';
	}
}
