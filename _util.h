template <typename T>
unordered_map<int, int> zipIndex(const T& arr) {
    int N = arr.size();
    vector<int> v(N);
    for (int i = 0; i < N; ++i) {
        v[i] = arr[i];
    }
    sort(begin(v), end(v));
    v.resize(unique(begin(v), end(v)) - begin(v));

    unordered_map<int, int> mm;
    FOR(i, N) {
        mm[v[i]] = i;
    }
    return mm;
}

