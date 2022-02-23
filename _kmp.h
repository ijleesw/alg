namespace {
// Computes fallback(=fail) array in kmp.
template <typename T>
vector<int> fallback(const T& s) {
    vector<int> fb(s.size() + 1, 0);
    for (int i = 1, j = 0; i < s.size(); ++i) {
        while (j > 0 && s[i] != s[j]) {
            j = fb[j];
        }
        if (s[i] == s[j]) {
            fb[i + 1] = j + 1;
            ++j;
        }
    }
    return fb;
}

// Returns start positions of matching in s (check t \in s).
template <typename T1, typename T2>
vector<int> kmp(const T1& s, const T2& t) {
    int slen = s.size();
    int tlen = t.size();

    vector<int> fb = fallback(t);
    vector<int> res;
    for (int i = 0, j = 0; i < slen; ++i) {
        while (j > 0 && s[i] != t[j]) {
            j = fb[j];
        }
        if (s[i] == t[j]) {
            ++j;
            if (j == tlen) {
                res.push_back(i - tlen + 1);
                // Add break here if only one match is needed.
                j = fb[j];
            }
        }
    }
    return res;
}
}   // anonymous namespace for kmp
