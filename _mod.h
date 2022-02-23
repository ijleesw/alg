constexpr int MOD = 1e9 + 7;

auto mod = [](auto x) {
    return x >= 0 ? x % MOD : ((long long)(-x / MOD + 1) * MOD + x) % MOD;
};

struct mi {
    int v;
    explicit operator int() const { return v; }
	mi() { v = 0; }
	mi(long long _v) : v(_v % MOD) { v += (v < 0) * MOD; }
};
mi& operator+=(mi& a, mi b) {
    if ((a.v += b.v) >= MOD) a.v -= MOD;
    return a;
}
mi& operator-=(mi& a, mi b) {
    if ((a.v -= b.v) < 0) a.v += MOD;
    return a;
}
mi& operator*=(mi& a, mi b) {
    return a = mi((long long)a.v * b.v);
}
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return a *= b; }

std::ostream& operator<< (std::ostream& out, const mi& m) {
    out << m.v;
    return out;
}

