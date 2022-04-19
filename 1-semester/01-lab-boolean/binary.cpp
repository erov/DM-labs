#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

bool check_ref(vector<vector<short>> &a) {
	bool ans = true;
	for (int i = 0; i < size(a); i++) {
		ans &= a[i][i];
	}
	return ans;
}

bool check_antiref(vector<vector<short>> &a) {
	bool ans = true;
	for (int i = 0; i < size(a); i++) {
		ans &= (!a[i][i]);
	}
	return ans;
}

bool check_sim(vector<vector<short>> &a) {
	bool ans = true;
	for (int i = 0; i < size(a); i++) {
		for (int j = 0; j < size(a); j++) {
			if (a[i][j]) {
				ans &= a[j][i];
			}
		}
	}
	return ans;
}

bool check_antisim(vector<vector<short>> &a) {
	bool ans = true;
	for (int i = 0; i < size(a); i++) {
		for (int j = 0; j < size(a); j++) {
			if (i != j && a[i][j]) {
				ans &= (!a[j][i]);
			}
		}
	}
	return ans;
}

bool check_tran(vector<vector<short>> &a) {
	bool ans = true;
	for (int i = 0; i < size(a); i++) {
		for (int j = 0; j < size(a); j++) {
			for (int k = 0; k < size(a); k++) {
				if (a[i][k] && a[k][j]) {
					ans &= a[i][j];
				}
			}
		}
	}
	return ans;
}

int main() {
    #ifdef HOME
        freopen("home.in", "r", stdin);
        freopen("home.out", "w", stdout);
    #endif

    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<short>> a(n, vector<short> (n));
    vector<vector<short>> b(n, vector<short> (n));
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		cin >> a[i][j];
    	}
    }
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		cin >> b[i][j];
    	}
    }

    cout << check_ref(a) << ' ' << check_antiref(a) << ' ' << check_sim(a) << ' ' << check_antisim(a) << ' ' << check_tran(a) << '\n';
    cout << check_ref(b) << ' ' << check_antiref(b) << ' ' << check_sim(b) << ' ' << check_antisim(b) << ' ' << check_tran(b) << '\n';

    int c[n][n];
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		c[i][j] = 0;
    	}
    }
    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		for (int k = 0; k < n; k++) {
    			c[i][j] |= (a[i][k] & b[k][j]);
    		}
    	}
    }

    for (int i = 0; i < n; i++) {
    	for (int j = 0; j < n; j++) {
    		cout << c[i][j] << ' ';
    	}
    	cout << '\n';
    }
}