#include <iostream>
#include <vector>
#include <climits>
#include <assert.h>

using namespace std;

#define size(a) (int) a.size()

int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("nextbrackets.in", "r", stdin);
		freopen("nextbrackets.out", "w", stdout);
	#endif

	string s;
	cin >> s;

	int n = size(s);
	int m = n / 2;
	int opened = m, closed = m;

	bool found = false;
	int i;
	for (i = n - 1; i >= 0; i--) {
		if (s[i] == '(') {
			opened--;
			if (opened >= closed + 1) {
				found = true;
				s[i] = ')';
				closed++;
				break;
			}
		} else {
			closed--;
		}
	}

	if (!found) {
		cout << '-';
	} else {
		cout << s.substr(0, i + 1);
		while (opened < m) {
			opened++;
			cout << '(';
		}
		while (closed < m) {
			closed++;
			cout << ')';
		}
	}
}
