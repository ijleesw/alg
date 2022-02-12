template <typename Integer = int>
class LazyPropagationSegmentTree {
public:
    LazyPropagationSegmentTree(int size) : startidx_(upper2(size)), seg_(startidx_ * 2, 0), lazy_(startidx_ * 2, 0) {}

    void add(const int l, const int r, const Integer val) {  // r: right exclusive.
        addHelper(0, startidx_, 1, l, r, val);
    }

    Integer sum(const int l, const int r) {  // r: right exclusive.
        return sumHelper(0, startidx_, 1, l, r);
    }

// private:
    void propagate(const int seg_l, const int seg_r, const int idx) {
        const auto lazy = lazy_[idx];
        if (lazy == 0) {
            return;
        }
        seg_[idx] += lazy * (seg_r - seg_l);
        if (idx < startidx_) {
            lazy_[idx * 2] += lazy;
            lazy_[idx * 2 + 1] += lazy;
        }
        lazy_[idx] = 0;
    }

    void addHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r, const Integer val) {
        if (r <= seg_l || seg_r <= l) {
            ; /* No-op */
        } else if (l <= seg_l && seg_r <= r) {
            lazy_[idx] += val;
            // Propagate once.
            propagate(seg_l, seg_r, idx);
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            addHelper(seg_l, seg_m, idx * 2, l, r, val);
            addHelper(seg_m, seg_r, idx * 2 + 1, l, r, val);
            seg_[idx] += val * (min(seg_r, r) - max(seg_l, l));
        }
    }

    Integer sumHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r) {
        // Propagate at every node if possible.
        propagate(seg_l, seg_r, idx);

        if (r <= seg_l || seg_r <= l) {
            return 0;
        } else if (l <= seg_l && seg_r <= r) {
            return seg_[idx];
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            return sumHelper(seg_l, seg_m, idx * 2, l, r) + sumHelper(seg_m, seg_r, idx * 2 + 1, l, r);
        }
    }

    int upper2(int n) {
        int res = 1;
        while (n > 0) {
            res *= 2;
            n /= 2;
        }
        return res;
    }

    const int startidx_;
    vector<Integer> seg_;
    vector<Integer> lazy_;
};

/**
 * 테트리스용 lazy propagation segment tree
 * Ref) https://www.acmicpc.net/problem/18407
 */
template <typename Integer = int>
class LazyPropagationSegmentTree {
public:
    LazyPropagationSegmentTree(int size) : startidx_(upper2(size)), seg_(startidx_ * 2, 0), lazy_(startidx_ * 2, 0) {}

    void set(const int l, const int r, const Integer val) {  // r: right exclusive.
        setHelper(0, startidx_, 1, l, r, val);
    }

    Integer max(const int l, const int r) {  // r: right exclusive.
        return maxHelper(0, startidx_, 1, l, r);
    }

// private:
    void propagate(const int seg_l, const int seg_r, const int idx) {
        const auto lazy = lazy_[idx];
        if (lazy == 0) {
            return;
        }
        seg_[idx] = std::max(seg_[idx], lazy);
        if (idx < startidx_) {
            lazy_[idx * 2] = lazy;
            lazy_[idx * 2 + 1] = lazy;
        }
        lazy_[idx] = 0;
    }

    void setHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r, const Integer val) {
        if (r <= seg_l || seg_r <= l) {
            ; /* No-op */
        } else if (l <= seg_l && seg_r <= r) {
            lazy_[idx] = val;
            // Propagate once.
            propagate(seg_l, seg_r, idx);
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            setHelper(seg_l, seg_m, idx * 2, l, r, val);
            setHelper(seg_m, seg_r, idx * 2 + 1, l, r, val);
            seg_[idx] = std::max(seg_[idx], val);
            lazy_[idx] = 0;
        }
    }

    Integer maxHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r) {
        // Propagate at every node if possible.
        propagate(seg_l, seg_r, idx);

        if (r <= seg_l || seg_r <= l) {
            return 0;
        } else if (l <= seg_l && seg_r <= r) {
            return seg_[idx];
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            return std::max(maxHelper(seg_l, seg_m, idx * 2, l, r), maxHelper(seg_m, seg_r, idx * 2 + 1, l, r));
        }
    }

    int upper2(int n) {
        int res = 1;
        while (n > 0) {
            res *= 2;
            n /= 2;
        }
        return res;
    }

    const int startidx_;
    vector<Integer> seg_;
    vector<Integer> lazy_;
};

