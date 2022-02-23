template <typename Func>
unordered_multimap<ll, int> hashify(const string& s, const int sz, const ll power, const Func& val) {
    auto mod = [](auto x) {
        static constexpr ll MOD = 1e9 + 7;
        return x >= 0 ? x % MOD : ((-x / MOD + 1) * MOD + x) % MOD;
    };

    unordered_multimap<ll, int> umm;
    ll hash = 0;
    ll mul = 1;

    for (int i = 0; i < sz - 1; ++i) {
        hash = mod(hash * power + val(s[i]));
        mul = mod(mul * power);
    }

    for (int i = sz - 1; i < len(s); ++i) {
        hash = mod(hash * power + val(s[i]));
        umm.emplace(hash, i - sz + 1);

        hash = mod(hash - mod(val(s[i - sz + 1]) * mul));
    }
    return umm;
}

