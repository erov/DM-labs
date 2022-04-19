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

struct big_integer
{
    big_integer();
    big_integer(big_integer const& other);
    big_integer(int a);
    big_integer(long a);
    big_integer(long long a);
    big_integer(unsigned a);
    big_integer(unsigned long a);
    big_integer(unsigned long long a);
    explicit big_integer(std::string const& str);

    ~big_integer();

    big_integer& operator=(big_integer const& other);

    big_integer& operator+=(big_integer const& rhs);
    big_integer& operator-=(big_integer const& rhs);
    big_integer& operator*=(big_integer const& rhs);
    big_integer& operator/=(big_integer const& rhs);
    big_integer& operator%=(big_integer const& rhs);

    big_integer& operator&=(big_integer const& rhs);
    big_integer& operator|=(big_integer const& rhs);
    big_integer& operator^=(big_integer const& rhs);

    big_integer& operator<<=(int rhs);
    big_integer& operator>>=(int rhs);

    big_integer operator+() const;
    big_integer operator-() const;
    big_integer operator~() const;

    big_integer& operator++();
    big_integer operator++(int);

    big_integer& operator--();
    big_integer operator--(int);

    friend bool operator==(big_integer const& a, big_integer const& b);
    friend bool operator!=(big_integer const& a, big_integer const& b);
    friend bool operator<(big_integer const& a, big_integer const& b);
    friend bool operator>(big_integer const& a, big_integer const& b);
    friend bool operator<=(big_integer const& a, big_integer const& b);
    friend bool operator>=(big_integer const& a, big_integer const& b);

    friend std::string to_string(big_integer const& a);

private:
    std::vector<uint32_t> data_;
    bool sign_;

    big_integer& bitwise_op(big_integer const& rhs, std::function<uint32_t (uint32_t, uint32_t)> func, uint32_t neutral);

    enum class comparison_result {
        LESS, EQUAL, GREATER
    };
    comparison_result compare_to(big_integer const& b) const;

    void set(size_t id, uint32_t value);
    uint32_t get_or_default(size_t id, uint32_t def) const;
    void delete_leading_zeroes();

    void to_twos_complement();
    void to_sign_bit();

    uint32_t divide(uint32_t b);
    void multiply(uint32_t b);
    void add(big_integer const& b, bool negated);
    void subtract(big_integer const& b, bool negated);
};

big_integer operator+(big_integer a, big_integer const& b);
big_integer operator-(big_integer a, big_integer const& b);
big_integer operator*(big_integer a, big_integer const& b);
big_integer operator/(big_integer a, big_integer const& b);
big_integer operator%(big_integer a, big_integer const& b);

big_integer operator&(big_integer a, big_integer const& b);
big_integer operator|(big_integer a, big_integer const& b);
big_integer operator^(big_integer a, big_integer const& b);

big_integer operator<<(big_integer a, int b);
big_integer operator>>(big_integer a, int b);

bool operator==(big_integer const& a, big_integer const& b);
bool operator!=(big_integer const& a, big_integer const& b);
bool operator<(big_integer const& a, big_integer const& b);
bool operator>(big_integer const& a, big_integer const& b);
bool operator<=(big_integer const& a, big_integer const& b);
bool operator>=(big_integer const& a, big_integer const& b);

std::string to_string(big_integer const& a);
std::ostream& operator<<(std::ostream& s, big_integer const& a);

constexpr uint32_t BASE = 32;
constexpr std::array<uint32_t, 9> TEN_POWER = {10, 100, 1'000, 10'000, 100'000,
                                                          1'000'000, 10'000'000, 100'000'000, 1'000'000'000};
uint32_t get_low32(uint64_t x) {
    return static_cast<uint32_t>(x & UINT32_MAX);
}

uint32_t get_high32(uint64_t x) {
    return static_cast<uint32_t>(x >> BASE);
}

unsigned long long get_abs(long long value) {
    if (value == INT64_MIN) {
        return (1ULL << 63);
    }
    return static_cast<unsigned long long>((value < 0) ? -value : value);
}

big_integer::big_integer() : data_(1), sign_(false) {}

big_integer::big_integer(big_integer const& other) = default;

big_integer::big_integer(int a) : big_integer(static_cast<long long>(a)) {}

big_integer::big_integer(long a) : big_integer(static_cast<long long>(a)) {}

big_integer::big_integer(long long a) : big_integer(get_abs(a)) {
    sign_ = (a < 0);
}

big_integer::big_integer(unsigned a) : big_integer(static_cast<unsigned long long>(a)) {}

big_integer::big_integer(unsigned long a) : big_integer(static_cast<unsigned long long>(a)) {}

big_integer::big_integer(unsigned long long a) : data_(), sign_(false) {
    if (a == 0) {
        set(0, 0);
    } else {
        set(0, get_low32(a));
        uint32_t b = get_high32(a);
        if (b != 0) {
            set(1, get_high32(a));
        }
    }
}

const big_integer ZERO = big_integer(0);
const big_integer ONE = big_integer(1);

big_integer::big_integer(std::string const& str) : big_integer() {
    if (str.empty()) {
        throw std::invalid_argument("non-empty str expected");
    }
    if (str == "-" || str == "+") {
        throw std::invalid_argument("big_integer cannot consist only of unary symbol");
    }
    for (size_t i = (str[0] == '-' || str[0] == '+') ? 1 : 0; i != str.size(); ++i) {
        if (!('0' <= str[i] && str[i] <= '9')) {
            throw std::invalid_argument("invalid big_integer value");
        }
    }
    for (size_t i = (str[0] == '-' || str[0] == '+') ? 1 : 0; i < str.size(); i += 9) {
        uint32_t current = 0;
        for (size_t j = 0; j < 9 && i + j < str.size(); ++j) {
            current = current * 10 + (str[i + j] - '0');
        }
        multiply(TEN_POWER[std::min(str.size() - i - 1, static_cast<size_t>(8))]);
        operator+=(current);
    }
    sign_ = (str[0] == '-' && *this != ZERO);
}

big_integer::~big_integer() = default;

big_integer& big_integer::operator=(big_integer const& other) = default;

big_integer& big_integer::operator+=(big_integer const& rhs) {
    if (sign_ && !rhs.sign_) {
        sign_ = false;
        subtract(rhs, false);
        if (*this != ZERO) {
            sign_ ^= 1;
        }
    } else {
        if (!sign_ && rhs.sign_) {
            subtract(rhs, true);
        } else {
            add(rhs, false);
        }
    }
    return *this;
}

big_integer& big_integer::operator-=(big_integer const& rhs) {
    if (sign_ && !rhs.sign_) {
        sign_ = false;
        add(rhs, false);
        sign_ = true;
    } else {
        if (!sign_ && rhs.sign_) {
            add(rhs, true);
        } else {
            subtract(rhs, false);
        }
    }
    return *this;
}

big_integer& big_integer::operator*=(big_integer const& rhs) {
    big_integer result;
    result.data_.resize(data_.size() + rhs.data_.size());
    for (size_t i = 0; i != data_.size(); ++i) {
        uint32_t c = 0;
        for (size_t j = 0; j < rhs.data_.size() || c > 0; ++j) {
            uint64_t res = static_cast<uint64_t>(data_[i]) * rhs.get_or_default(j, 0) +
                           c + result.get_or_default(i + j, 0);
            result.data_[i + j] = get_low32(res);
            c = get_high32(res);
        }
    }
    result.sign_ = (sign_ ^ rhs.sign_ && result != ZERO);
    result.delete_leading_zeroes();
    return *this = result;
}

big_integer& big_integer::operator/=(big_integer const& rhs) {
    if (data_.size() < rhs.data_.size()) {
        return *this = ZERO;
    }

    if (rhs.data_.size() == 1) {
        divide(rhs.data_[0]);
        sign_ = (sign_ ^ rhs.sign_);
        return *this;
    }

    uint64_t d = rhs.data_.back();
    uint32_t f = static_cast<uint32_t>((1ULL << BASE) / (d + 1));
    big_integer c(rhs);
    multiply(f);
    c.multiply(f);
    d = c.data_.back();
    size_t len = c.data_.size();

    big_integer ans;
    ans.sign_ = (sign_ ^ rhs.sign_);
    size_t ans_len = data_.size() - len + 1;
    ans.data_.resize(ans_len);

    sign_ = false;
    c.sign_ = false;
    c <<= (ans_len - 1) * BASE;
    for (size_t i = ans_len; i != 0; --i) {
        uint64_t q = ((static_cast<uint64_t>(get_or_default(i - 1 + len, 0)) << BASE) +
                      get_or_default(i - 1 + len - 1, 0)) / d;
        operator-=(c * q);
        while (*this < ZERO) {
            operator+=(c);
            --q;
        }
        ans.data_[i - 1] = q;
        c >>= BASE;
    }
    ans.delete_leading_zeroes();
    return *this = ans;
}

big_integer& big_integer::operator%=(big_integer const& rhs) {
    return *this -= (*this / rhs) * rhs;
}

big_integer& big_integer::operator&=(big_integer const& rhs) {
    return bitwise_op(rhs, [&](uint32_t x, uint32_t y) {return x & y;}, UINT32_MAX);
}

big_integer& big_integer::operator|=(big_integer const& rhs) {
    return bitwise_op(rhs, [&](uint32_t x, uint32_t y) {return x | y;}, 0);
}

big_integer& big_integer::operator^=(big_integer const& rhs) {
    return bitwise_op(rhs, [&](uint32_t x, uint32_t y) {return x ^ y;}, UINT32_MAX);
}

big_integer& big_integer::operator<<=(int rhs) {
    size_t zeroes = static_cast<size_t>(rhs) / BASE;
    if (zeroes != 0) {
        data_.resize(data_.size() + zeroes);
        for (size_t i = data_.size() - zeroes; i != 0; --i) {
            std::swap(data_[i - 1], data_[i + zeroes - 1]);
        }
    }
    multiply(1U << (rhs % BASE));
    return *this;
}

big_integer& big_integer::operator>>=(int rhs) {
    size_t del = static_cast<size_t>(rhs) / BASE;
    if (del >= data_.size()) {
        return *this = ZERO;
    }
    if (del != 0) {
        for (size_t i = 0; i + del < data_.size(); ++i) {
            std::swap(data_[i], data_[i + del]);
        }
        for (size_t i = 0; i != del; ++i) {
            data_.pop_back();
        }
    }
    divide(1U << (rhs % BASE));
    if (sign_) {
        --(*this);
    }
    return *this;
}

big_integer big_integer::operator+() const {
    return *this;
}

big_integer big_integer::operator-() const {
    if (*this == ZERO) {
        return *this;
    }
    big_integer result(*this);
    result.sign_ = !result.sign_;
    return result;
}

big_integer big_integer::operator~() const {
    big_integer result(*this);
    result.add(ONE, false);
    if (result != ZERO) {
        result.sign_ ^= 1;
    }
    return result;
}

big_integer& big_integer::operator++() {
    return (*this += ONE);
}

big_integer big_integer::operator++(int) {
    big_integer old(*this);
    *this += ONE;
    return old;
}

big_integer& big_integer::operator--() {
    return (*this -= ONE);
}

big_integer big_integer::operator--(int) {
    big_integer old(*this);
    *this -= ONE;
    return old;
}

big_integer operator+(big_integer a, big_integer const& b) {
    return a += b;
}

big_integer operator-(big_integer a, big_integer const& b) {
    return a -= b;
}

big_integer operator*(big_integer a, big_integer const& b) {
    return a *= b;
}

big_integer operator/(big_integer a, big_integer const& b) {
    return a /= b;
}

big_integer operator%(big_integer a, big_integer const& b) {
    return a %= b;
}

big_integer operator&(big_integer a, big_integer const& b) {
    return a &= b;
}

big_integer operator|(big_integer a, big_integer const& b) {
    return a |= b;
}

big_integer operator^(big_integer a, big_integer const& b) {
    return a ^= b;
}

big_integer operator<<(big_integer a, int b) {
    return a <<= b;
}

big_integer operator>>(big_integer a, int b) {
    return a >>= b;
}

bool operator==(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) == big_integer::comparison_result::EQUAL;
}

bool operator!=(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) != big_integer::comparison_result::EQUAL;
}

bool operator<(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) == big_integer::comparison_result::LESS;
}

bool operator>(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) == big_integer::comparison_result::GREATER;
}

bool operator<=(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) != big_integer::comparison_result::GREATER;
}

bool operator>=(big_integer const& a, big_integer const& b) {
    return a.compare_to(b) != big_integer::comparison_result::LESS;
}

std::string to_string(big_integer const& a) {
    if (a == ZERO) {
        return "0";
    }
    std::string result;
    big_integer tmp(a);
    while (tmp != ZERO) {
        uint32_t remainder = tmp.divide(1'000'000'000);
        bool leading_zeroes = (tmp != ZERO);
        for (size_t i = 0; (leading_zeroes == true && i < 9) || remainder != 0; ++i) {
            result += ('0' + remainder % 10);
            remainder /= 10;
        }
    }
    if (a.sign_) {
        result += "-";
    }
    std::reverse(result.begin(), result.end());
    return result;
}

std::ostream& operator<<(std::ostream& s, big_integer const& a) {
    return s << to_string(a);
}

big_integer& big_integer::bitwise_op(big_integer const& rhs,
                       std::function<uint32_t (uint32_t, uint32_t)> func, uint32_t neutral) {
    to_twos_complement();
    big_integer tmp(rhs);
    tmp.to_twos_complement();
    for (size_t i = 0; i < std::max(data_.size(), tmp.data_.size()); ++i) {
        set(i, func(get_or_default(i, neutral), tmp.get_or_default(i, neutral)));
    }
    sign_ = func(sign_, tmp.sign_);
    to_sign_bit();
    return *this;
}

big_integer::comparison_result big_integer::compare_to(big_integer const& b) const {
    if (sign_ && !b.sign_) {
        return comparison_result::LESS;
    }
    if (!sign_ && b.sign_) {
        return comparison_result::GREATER;
    }
    if (data_.size() < b.data_.size()) {
        return sign_ ? comparison_result::GREATER : comparison_result::LESS;
    }
    if (data_.size() > b.data_.size()) {
        return sign_ ? comparison_result::LESS : comparison_result::GREATER;
    }
    for (size_t i = data_.size(); i != 0; --i) {
        if (data_[i - 1] < b.data_[i - 1]) {
            return sign_ ? comparison_result::GREATER : comparison_result::LESS;
        }
        if (data_[i - 1] > b.data_[i - 1]) {
            return sign_ ? comparison_result::LESS : comparison_result::GREATER;
        }
    }
    return comparison_result::EQUAL;
}

void big_integer::set(size_t id, uint32_t value) {
    if (id >= data_.size()) {
        data_.resize(id + 1);
    }
    data_[id] = value;
}

uint32_t big_integer::get_or_default(size_t id, uint32_t def) const {
    return (id < data_.size()) ? data_[id] : def;
}

void big_integer::delete_leading_zeroes() {
    while (!data_.empty() && data_.back() == 0) {
        data_.pop_back();
    }
    if (data_.empty()) {
        sign_ = false;
        data_.push_back(0U);
    }
}

void big_integer::to_twos_complement() {
    if (sign_) {
        sign_ = false;
        --(*this);
        for (uint32_t &digit : data_) {
            digit = ~digit;
        }
        sign_ = true;
    }
}

void big_integer::to_sign_bit() {
    if (sign_) {
        sign_ = false;
        for (uint32_t &digit : data_) {
            digit = ~digit;
        }
        operator++();
        sign_ = true;
    }
}

uint32_t big_integer::divide(uint32_t rhs) {
    uint64_t c = 0;
    for (size_t i = data_.size(); i != 0; --i) {
        c = (c << BASE) + data_[i - 1];
        data_[i - 1] = get_low32(c / rhs);
        c %= rhs;
    }
    delete_leading_zeroes();
    return c;
}

void big_integer::multiply(uint32_t rhs) {
    uint64_t c = 0;
    for (size_t i = 0; i != data_.size(); ++i) {
        c += static_cast<uint64_t>(data_[i]) * rhs;
        data_[i] = get_low32(c);
        c = get_high32(c);
    }
    if (c != 0) {
        data_.push_back(c);
    } else {
        delete_leading_zeroes();
    }
}

// this and rhs must have same signs (may be using negated = true)
void big_integer::add(big_integer const& rhs, bool negated) {
    sign_ = (sign_ && (rhs.sign_ ^ negated));
    uint32_t c = 0;
    for (size_t i = 0; i < std::max(data_.size(), rhs.data_.size()); ++i) {
        uint64_t res = static_cast<uint64_t>(get_or_default(i, 0)) + rhs.get_or_default(i, 0) + c;
        set(i, get_low32(res));
        c = get_high32(res);
    }
    if (c != 0) {
        data_.push_back(c);
    }
}

// this and rhs must have same signs (may be using negated = true)
void big_integer::subtract(big_integer const& rhs, bool negated) {
    if (negated) {
        sign_ ^= 1;
    }
    bool swapped = ((sign_ && rhs.sign_ && *this > rhs) || (!sign_ && !rhs.sign_ && *this < rhs));
    if (negated) {
        sign_ ^= 1;
    }
    uint32_t c = 0;
    for (size_t i = 0; i != (swapped ? rhs.data_.size() : data_.size()); ++i) {
        uint64_t res;
        if (swapped) {
            res = static_cast<uint64_t>(rhs.data_[i]) - get_or_default(i, 0) - c;
        } else {
            res = static_cast<uint64_t>(data_[i]) - rhs.get_or_default(i, 0) - c;
        }
        c = static_cast<bool>(res >> 63U);
        set(i, get_low32(res));
    }
    sign_ ^= swapped;
    delete_leading_zeroes();
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

vector<int64_t> multiply(vector<int64_t>& p, vector<int64_t>& q) {
    vector<int64_t> mul(p.size() * q.size() + 1, 0);
    for (size_t i = 0; i != p.size(); ++i) {
        for (size_t j = 0; j != q.size(); ++j) {
            mul[i + j] = mul[i + j] + p[i] * q[j];
        }
    }

    trim(mul);
    return mul;
}

struct fract_t {
    fract_t(int64_t num, int64_t denom) 
        : num(big_integer(num)), denom(big_integer(denom))
    {}

    fract_t(int64_t num, big_integer denom) 
        : num(big_integer(num)), denom(denom)
    {}
    
    fract_t(big_integer num, int64_t denom) 
        : num(num), denom(big_integer(denom))
    {}

    fract_t(big_integer num, big_integer denom) 
        : num(num), denom(denom)
    {}

    big_integer num;
    big_integer denom;
};

big_integer gcd(big_integer lhs, big_integer rhs) {
    return rhs != 0 ? gcd(rhs, lhs % rhs) : lhs;
}

fract_t fix(fract_t value) {
    big_integer c = gcd(value.num, value.denom);
    value.num /= c;
    value.denom /= c;
    if (value.denom < 0) {
        value.num *= -1;
        value.denom *= -1;
    }
    return value;
}

fract_t add(fract_t lhs, fract_t rhs) {
    lhs.num *= rhs.denom;
    rhs.num *= lhs.denom;
    lhs.num += rhs.num;
    lhs.denom *= rhs.denom;
    return fix(lhs);
}

fract_t mul(fract_t lhs, fract_t rhs) {
    lhs.num *= rhs.num;
    lhs.denom *= rhs.denom;
    return fix(lhs);
}

void solve() {
    uint64_t r;
    size_t k;
    cin >> r >> k;

    vector<int64_t> p(k + 1);
    for (size_t i = 0; i != p.size(); ++i) {
        cin >> p[i];
    }

    int64_t k_fact = 1;
    for (size_t i = 1; i != k + 1; ++i) {
        k_fact *= i;
    }

    vector<fract_t> result(k + 1, {0, 1});

    big_integer denom_multiplier = {1};
    for (size_t n = 0; n != p.size(); ++n) {
        vector<int64_t> impact = {1};
        vector<int64_t> temp = {1 - static_cast<int64_t>(n), 1};
        for (size_t i = 0; i != k; ++i) {
            impact = multiply(impact, temp);
            ++temp[0];
        }
        
        for (size_t i = 0; i != impact.size(); ++i) {
            fract_t delta_i = {p[n], k_fact};
            delta_i = mul(delta_i, {impact[i], 1});
            delta_i = mul(delta_i, {1, denom_multiplier});
            result[i] = add(result[i], delta_i);
        }
        denom_multiplier *= r;
    }

    for (size_t i = 0; i != result.size(); ++i) {
        cout << result[i].num << '/' << result[i].denom << ' ';
    }
}

