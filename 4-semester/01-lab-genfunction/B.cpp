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


void trim(vector<int64_t>& coeffs) {
    while (!coeffs.empty() && coeffs.back() == 0) {
        coeffs.pop_back();
    }
}

void trim(vector<int64_t>& coeffs, size_t size) {
    coeffs.resize(size);
}

void print(vector<int64_t>& coeffs, bool print_size = true) {
    if (print_size) {
        cout << coeffs.size() - (coeffs.empty() ? 0 : 1) << '\n';
    }
    for (int64_t coeff : coeffs) {
        cout << coeff << ' ';
    }
    cout << '\n';
}

int64_t modulo(int64_t value, int64_t const MOD) {
    return value >= MOD ? (value % MOD) : value;
}

vector<int64_t> add(vector<int64_t>& p, vector<int64_t>& q, int64_t const MOD) {
    vector<int64_t> sum(max(p.size(), q.size()), 0);
    for (size_t i = 0; i != p.size(); ++i) {
        sum[i] = p[i];
    }

    for (size_t i = 0; i != q.size(); ++i) {
        sum[i] = modulo(sum[i] + q[i], MOD);
    }

    trim(sum);
    return sum;
}

vector<int64_t> multiply(vector<int64_t>& p, vector<int64_t>& q, int64_t const MOD) {
    vector<int64_t> mul(p.size() * q.size() + 1, 0);
    for (size_t i = 0; i != p.size(); ++i) {
        for (size_t j = 0; j != q.size(); ++j) {
            mul[i + j] = modulo(mul[i + j] + modulo(p[i] * q[j], MOD), MOD);
        }
    }

    trim(mul);
    return mul;
}

vector<int64_t> multiply(vector<int64_t>& p, int64_t lambda, int64_t const MOD) {
    vector<int64_t> result(p.size(), 0);
    for (size_t i = 0; i != p.size(); ++i) {
        result[i] = modulo(p[i] * lambda, MOD);
    }
    return result;
}

int64_t bin_pow(int64_t a, int64_t deg, int64_t const MOD) {
    int64_t result = 1;
    while (deg != 0) {
        if (deg % 2 != 0) {
            result = modulo(result * a, MOD);
        }
        a = modulo(a * a, MOD);
        deg /= 2;
    }
    return result;
}

int64_t modulo_divide(int64_t p, int64_t q, int64_t const MOD) {
    return modulo(p * bin_pow(q, MOD - 2, MOD), MOD);
}

vector<int64_t> divide(vector<int64_t>& p, vector<int64_t>& q, size_t const COEFFS, int64_t const MOD) {
    assert(!p.empty());
    assert(!q.empty());

    vector<int64_t> div(COEFFS, 0);
    
    if (div.size() > 0) {
        div[0] = modulo_divide(p[0], q[0], MOD);
        
        for (size_t i = 1; i != div.size(); ++i) {
            div[i] = (i < p.size() ? p[i] : 0);
            int64_t value = 0;
            for (size_t j = 0; j != i; ++j) {
                value = modulo(value + modulo(div[j] * (i - j < q.size() ? q[i - j] : 0), MOD), MOD);
            }
            div[i] = modulo(div[i] + MOD - value, MOD);
            div[i] = modulo_divide(div[i], q[0], MOD);
        }
    }

    return div;
}

vector<int64_t> expand_taylor(vector<int64_t>& result_t, vector<int64_t>& p, int64_t const MOD) {
    vector<int64_t> result(result_t.size(), 0);
    vector<int64_t> p_powed = p;

    result[0] = result_t[0];
    for (size_t n = 1; n != result.size(); ++n) {
        vector<int64_t> temp =  multiply(p_powed, result_t[n], MOD);
        result = add(result, temp, MOD);
        trim(result, result_t.size());
        p_powed = multiply(p_powed, p, MOD);
        trim(p_powed, result_t.size());
    }

    return result;
}

// sqrt(1 + p(t))
vector<int64_t> sqrt(vector<int64_t>& p, size_t const COEFFS, int64_t const MOD) {
    vector<int64_t> result_t(COEFFS, 0);
    if (result_t.size() > 0) {
        result_t[0] = 1;
        for (size_t n = 1; n != result_t.size(); ++n) {
            int64_t num = (n % 2 == 1 ? MOD - 1 : 1);
            int64_t denom = modulo(1 + MOD - 2 * static_cast<int64_t>(n), MOD);
            int64_t fact = 1;
            for (size_t i = 1; i != n + 1; ++i) {
                fact = modulo(fact * static_cast<int64_t>(i), MOD);
            }
            denom = modulo(denom * bin_pow(fact, 2, MOD), MOD);
            num = modulo(num * fact, MOD);
            for (size_t i = n + 1; i != 2 * n + 1; ++i) {
                num = modulo(num * static_cast<int64_t>(i), MOD);
            }

            denom = modulo(denom * bin_pow(4, n, MOD), MOD);
            result_t[n] = modulo_divide(num, denom, MOD);
        }        
    }

    return expand_taylor(result_t, p, MOD);
}

// e^p(t)
vector<int64_t> exp(vector<int64_t>& p, size_t const COEFFS, int64_t const MOD) {
    vector<int64_t> result_t(COEFFS, 0);
    if (result_t.size() > 0) {
        result_t[0] = 1;
        for (size_t n = 1; n != result_t.size(); ++n) {
            result_t[n] = modulo_divide(result_t[n - 1], static_cast<int64_t>(n), MOD);
        }
    }

    return expand_taylor(result_t, p, MOD);
}

// ln(1 + p(t))
vector<int64_t> ln(vector<int64_t>& p, size_t const COEFFS, int64_t const MOD) {
    vector<int64_t> result_t(COEFFS, 0);
    if (result_t.size() > 0) {
        for (size_t n = 1; n != result_t.size(); ++n) {
            result_t[n] = modulo_divide((n % 2 == 1 ? 1 : MOD - 1), static_cast<int64_t>(n), MOD);
        }
    }

    return expand_taylor(result_t, p, MOD);
}

// DEBUG
bool check_equality_of_gfs(vector<int64_t> lhs, vector<int64_t> rhs) {
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

    vector<int64_t> p(n + 1);
    for (size_t i = 0; i != n + 1; ++i) {
        cin >> p[i];
    }

    constexpr int64_t MOD = 998'244'353;

    vector<int64_t> sqrt_coeffs = sqrt(p, m, MOD);
    vector<int64_t> exp_coeffs = exp(p, m, MOD);
    vector<int64_t> ln_coeffs = ln(p, m, MOD);

    print(sqrt_coeffs, false);
    print(exp_coeffs, false);
    print(ln_coeffs, false);
}

