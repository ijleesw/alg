class UnionFind {
public:
    UnionFind(int n) : arr_(n, -1) {}

    int root(int n) {
        if (arr_[n] < 0) {
            return n;
        } else {
            return arr_[n] = root(arr_[n]);
        }
    }

    bool merge(int a, int b) {
        int ra = root(a);
        int rb = root(b);
        if (ra == rb) {
            return false;
        }
        if (sz(ra) < sz(rb)) {
            swap(ra, rb);
        }
        // now sz(ra) >= sz(rb).
        arr_[ra] -= sz(rb);
        arr_[rb] = ra;
        return true;
    }

// private:
    int sz(int n) {
        return -arr_[root(n)];
    }

    // Positive: parent idx
    // Negative: -(subtree size)
    vector<int> arr_;
};
