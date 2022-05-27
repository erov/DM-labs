#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

void solve();

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    #ifdef HOME
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
        clock_t start_clock = clock();
    #else
     // freopen(".in", "r", stdin);
     // freopen(".out", "w", stdout);
    #endif
    
    solve();

    #ifdef HOME
        printf("\n\nfinished in %.3f sec", static_cast<float>(clock() - start_clock) / CLOCKS_PER_SEC);
        // system("pause");
    #endif
}


void trim(vector<uint64_t>& coeffs) {
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

void print(vector<uint64_t>& coeffs) {
    cout << coeffs.size() - (coeffs.empty() ? 0 : 1) << '\n';
    for (uint64_t coeff : coeffs) {
        cout << coeff << ' ';
    }
    cout << '\n';
}

uint64_t modulo(uint64_t value, uint64_t const MOD) {
    return value >= MOD ? (value % MOD) : value;
}

vector<uint64_t> add(vector<uint64_t>& p, vector<uint64_t>& q, uint64_t const MOD) {
    vector<uint64_t> sum(max(p.size(), q.size()), 0);
    for (size_t i = 0; i != p.size(); ++i) {
        sum[i] = p[i];
    }

    for (size_t i = 0; i != q.size(); ++i) {
        sum[i] = modulo(sum[i] + q[i], MOD);
    }

    trim(sum);
    return sum;
}

vector<uint64_t> multiply(vector<uint64_t>& p, vector<uint64_t>& q, uint64_t const MOD) {
    vector<uint64_t> mul(p.size() * q.size() + 1, 0);
    for (size_t i = 0; i != p.size(); ++i) {
        for (size_t j = 0; j != q.size(); ++j) {
            mul[i + j] = modulo(mul[i + j] + modulo(p[i] * q[j], MOD), MOD);
        }
    }

    trim(mul);
    return mul;
}

uint64_t bin_pow(uint64_t a, uint64_t deg, uint64_t const MOD) {
    uint64_t result = 1;
    while (deg != 0) {
        if (deg % 2 != 0) {
            result = modulo(result * a, MOD);
        }
        a = modulo(a * a, MOD);
        deg /= 2;
    }
    return result;
}

uint64_t modulo_divide(uint64_t p, uint64_t q, uint64_t const MOD) {
    return modulo(p * bin_pow(q, MOD - 2, MOD), MOD);
}

vector<uint64_t> divide(vector<uint64_t>& p, vector<uint64_t>& q, size_t const COEFFS, uint64_t const MOD) {
    assert(!p.empty());
    assert(!q.empty());

    vector<uint64_t> div(COEFFS, 0);
    
    if (div.size() > 0) {
        div[0] = modulo_divide(p[0], q[0], MOD);
        
        for (size_t i = 1; i != div.size(); ++i) {
            div[i] = (i < p.size() ? p[i] : 0);
            uint64_t value = 0;
            for (size_t j = 0; j != i; ++j) {
                value = modulo(value + modulo(div[j] * (i - j < q.size() ? q[i - j] : 0), MOD), MOD);
            }
            div[i] = modulo(div[i] + MOD - value, MOD);
            div[i] = modulo_divide(div[i], q[0], MOD);
        }
    }

    return div;
}

bool check_equality_of_gfs(vector<uint64_t> lhs, vector<uint64_t> rhs) {
    trim(lhs);
    trim(rhs);
    cout << lhs.size() << ' ' << rhs.size() << '\n';
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i != lhs.size(); ++i) {
        if (lhs[i] != rhs[i]) {
            return false;
        }
    }
    return true;
}

void solve() {
    size_t n, m;
    cin >> n >> m;

    vector<uint64_t> p(n + 1), q(m + 1);
    for (size_t i = 0; i != n + 1; ++i) {
        cin >> p[i];
    }

    for (size_t i = 0; i != m + 1; ++i) {
        cin >> q[i];
    }

    constexpr uint64_t MOD = 998'244'353;
    
    vector<uint64_t> sum = add(p, q, MOD);
    vector<uint64_t> mul = multiply(p, q, MOD);
    vector<uint64_t> div = divide(p, q, 1'000, MOD);

    print(sum);
    print(mul);
    for (uint64_t coeff : div) {
        cout << coeff << ' ';
    }
}

