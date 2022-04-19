#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cmath>
#include <cstddef>
#include <functional>
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

vector<int64_t> multiply(vector<int64_t>& p, vector<int64_t>& q, int64_t const MOD, size_t trim_to = 0) {
    if (trim_to == 0) {
        trim_to = p.size() * q.size() + 1;
    }
    vector<int64_t> mul(trim_to, 0);
    for (size_t i = 0; i != p.size(); ++i) {
        for (size_t j = 0; j != q.size() && i + j < trim_to; ++j) {
            mul[i + j] = modulo(mul[i + j] + modulo(p[i] * q[j], MOD), MOD);
        }
    }
    // if (trim_to != 0) {
    //     trim(mul, trim_to);
    // }
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

void apply_minus_t(vector<int64_t>& p, int64_t const MOD) {
    for (size_t i = 0; i != p.size(); ++i) {
        if (i % 2 == 1) {
            p[i] = modulo(MOD - p[i], MOD);
        }
    }
}


vector<int64_t> shrink(vector<int64_t> p, size_t start) {
    vector<int64_t> result;

    // result.push_back(p[0]);

    for (size_t i = start /*+ (start == 0 ? 2 : 0)*/; i < p.size(); i += 2) {
        result.push_back(p[i]);
    }

    return result;
}


void solve() {
    uint64_t k, n;
    cin >> k >> n;

    constexpr int64_t MOD = 104'857'601;

    vector<int64_t> a(k);
    for (uint64_t i = 0; i != k; ++i) {
        cin >> a[i];
    }

    vector<int64_t> c(k + 1);
    for (uint64_t i = 1; i != k + 1; ++i) {
        cin >> c[i];
    }

    vector<int64_t> q = c;
    q[0] = 1;
    for (size_t i = 1; i != q.size(); ++i) {
        q[i] = modulo(MOD - q[i], MOD);
    }

    vector<int64_t> p = a;
    p = multiply(p, q, MOD);
    trim(p, k);
    // trim(p);

    // vector<int64_t> temp = divide(p, q, n, MOD);
    // print(temp);

    vector<int64_t> q_minus;
    --n;
    while (n > k) {
        q_minus = q;
        apply_minus_t(q_minus, MOD);

        p = multiply(p, q_minus, MOD, 2 * (k + 1));
        q = multiply(q, q_minus, MOD, 2 * (k + 1));

        // print(q);

        p = shrink(p, n % 2);
        q = shrink(q, 0);

        // trim(p, k + 1);
        // trim(q, k + 1);

        n /= 2;
    }

    p = divide(p, q, n + 1, MOD);
    // print(p);

    cout << p[n];
}

