#include <iostream>
#include <vector>
#include <assert.h>
#include <algorithm>

using namespace std;

string prev(string s) {
	int i = (int) s.size() - 1;
	while (i >= 0 && s[i] == '0') {
		s[i] = '1';
		i--;
	}
	cerr << i << '\n';
	if (i >= 0) {
		s[i] = '0';
		return s;
	}
	return "-";
}

string nxt(string s) {
	int i = (int) s.size() - 1;
	while (i >= 0 && s[i] == '1') {
		s[i] = '0';
		i--;
	}
	if (i >= 0) {
		s[i] = '1';
		return s;
	}
	return "-";
}

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("nextvector.in", "r", stdin);
		freopen("nextvector.out", "w", stdout);
	#endif

	string s;
	cin >> s;

	cout << prev(s) << '\n' << nxt(s);
}
