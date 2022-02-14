template <typename Sum = int, typename Add = Sum>
class SegmentTree {
public:
    SegmentTree(int size) : N2(upper2(size)), seg_(N2 * 2, kDefaultSum) {}

    void add(const int pos, const Add val) {
        int idx = N2 + pos;
        while (idx > 0) {
            seg_[idx] = addOp(seg_[idx], val);
            idx /= 2;
        }
    }

    Sum sum(const int l, const int r) {  // right exclusive
        return sumHelper(0, N2, 1, l, r);
    }

// protected:
// Modify this part as needed.
    Sum addOp(const Sum& lhs, const Add& rhs) {
        return lhs + rhs.
    }

    Sum sumOp(const Sum& lhs, const Sum& rhs) {
        return lhs + rhs;
    }

    static constexpr Sum kDefaultSum = 0;

// private:
    Sum sumHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r) {
        if (r <= seg_l || seg_r <= l) {
            return kDefaultSum;
        } else if (l <= seg_l && seg_r <= r) {
            return seg_[idx];
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            return sumOp(sumHelper(seg_l, seg_m, idx * 2, l, r), sumHelper(seg_m, seg_r, idx * 2 + 1, l, r));
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

    const int N2;
    vector<Sum> seg_;
};



template <typename Sum = int, typename Lazy = Sum>
class LazyPropagationSegmentTree {
public:
    LazyPropagationSegmentTree(int size) :
        startidx_(upper2(size)), seg_(startidx_ * 2, kDefaultSum), lazy_(startidx_ * 2, kDefaultLazy) {}

    void add(const int l, const int r, const Lazy& lazy) {  // r: right exclusive.
        addHelper(0, startidx_, 1, l, r, lazy);
    }

    Sum sum(const int l, const int r) {  // r: right exclusive.
        return sumHelper(0, startidx_, 1, l, r);
    }

// protected:
// Modify this part as needed.
    void applyLazy(Sum& seg, const int seg_l, const int seg_r, const Lazy& lazy) {
        seg += lazy * (seg_r - seg_l);
    }

    void addLazy(Lazy& lazy, const Lazy& new_lazy) {
        lazy += new_lazy;
    }

    Sum sumOp(const Sum& lhs, const Sum& rhs) {
        return lhs + rhs;
    }

    static constexpr Sum kDefaultSum = 0;
    static constexpr Lazy kDefaultLazy = 0;

// private:
    void propagate(const int seg_l, const int seg_r, const int idx) {
        const auto lazy = lazy_[idx];
        if (lazy == kDefaultLazy) {
            return;
        }
        applyLazy(seg_[idx], seg_l, seg_r, lazy);
        if (idx < startidx_) {
            addLazy(lazy_[idx * 2], lazy);
            addLazy(lazy_[idx * 2 + 1], lazy);
        }
        lazy_[idx] = kDefaultLazy;
    }

    void addHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r, const Lazy& lazy) {
        // Propagate at every node if possible.
        propagate(seg_l, seg_r, idx);

        if (r <= seg_l || seg_r <= l) {
            ; /* No-op */
        } else if (l <= seg_l && seg_r <= r) {
            addLazy(lazy_[idx], lazy);
            // Propagate once.
            propagate(seg_l, seg_r, idx);
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            addHelper(seg_l, seg_m, idx * 2, l, r, lazy);
            addHelper(seg_m, seg_r, idx * 2 + 1, l, r, lazy);
            seg_[idx] = sumOp(seg_[idx * 2], seg_[idx * 2 + 1]);
        }
    }

    Sum sumHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r) {
        // Propagate at every node if possible.
        propagate(seg_l, seg_r, idx);

        if (r <= seg_l || seg_r <= l) {
            return kDefaultSum;
        } else if (l <= seg_l && seg_r <= r) {
            return seg_[idx];
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            return sumOp(sumHelper(seg_l, seg_m, idx * 2, l, r), sumHelper(seg_m, seg_r, idx * 2 + 1, l, r));
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
    vector<Sum> seg_;
    vector<Lazy> lazy_;
};

