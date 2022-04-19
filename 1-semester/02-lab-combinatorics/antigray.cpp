#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

void gen(vector<string> &code, string cur, int sz, int pos) {
	if (pos == sz) {
		code.push_back(cur);
		return;
	}
	cur = cur + "0";
	for (char i = '0'; i <= '2'; i++) {
		cur.back() = i;
		gen(code, cur, sz, pos + 1);
	}
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("antigray.in", "r", stdin);
		freopen("antigray.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	vector<string> code;
	gen(code, "", n, 0);

	for (int i = 0; i < size(code) / 3; i++) {
		cout << code[i] << '\n';
		for (int j = 0; j < 2; j++) {
			for (int k = 0; k < n; k++) {
				code[i][k]++;
				if (code[i][k] == '3') {
					code[i][k] = '0';
				}
			}
			cout << code[i] << '\n';
		}
	}
}
