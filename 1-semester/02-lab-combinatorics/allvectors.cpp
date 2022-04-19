#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;


int main() {
	#ifdef HOME
		freopen("home.in", "r", stdin);
		freopen("home.out", "w", stdout);
	#else
		freopen("allvectors.in", "r", stdin);
		freopen("allvectors.out", "w", stdout);
	#endif

	int n;
	cin >> n;

	for (int mask = 0; mask < (1 << n); mask++){ 
		for (int i = n - 1; i >= 0; i--) {
			cout << ((mask >> i) & 1);
		}
		cout << '\n';
	}
}
