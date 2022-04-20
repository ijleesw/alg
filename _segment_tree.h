///////////////////////////////////////////////////////////////////
// BASIC SEGMENT TREE
///////////////////////////////////////////////////////////////////

template <typename Sum = int, typename Add = Sum>
class SegmentTree {
public:
    SegmentTree(int size) : N2_(upper2(size)), seg_(N2_ * 2, kDefaultSum) {}

    void add(const int pos, const Add val) {
        int idx = N2_ + pos;
        while (idx > 0) {
            seg_[idx] = addOp(seg_[idx], val);
            idx /= 2;
        }
    }

    Sum sum(const int l, const int r) {  // right exclusive
        return sumHelper(0, N2_, 1, l, r);
    }

    int size() const {
        return N2_;
    }

// protected:
// Modify this part as needed.
    Sum addOp(const Sum& lhs, const Add& rhs) {
        return lhs + rhs;
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

    const int N2_;
    vector<Sum> seg_;
};

///////////////////////////////////////////////////////////////////
// LAZY PROPAGATION SEGMENT TREE
///////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////
// LAZY PROPAGATION SEGMENT TREE w/ DEACTIVATE
///////////////////////////////////////////////////////////////////

template <typename Sum = int, typename Lazy = Sum>
class LazyPropagationSegmentTree {
public:
    LazyPropagationSegmentTree(int size) :
        startidx_(upper2(size)), seg_(startidx_ * 2, kDefaultSum), lazy_(startidx_ * 2, kDefaultLazy), active_(startidx_ * 2) {
        for (int i = startidx_; i < startidx_ + size; ++i) {
            active_[i] = 1;
        }
        for (int i = startidx_ - 1; i >= 1; --i) {
            active_[i] = active_[i * 2] + active_[i * 2 + 1];
        }
    }

    void add(const int l, const int r, const Lazy& lazy) {  // r: right exclusive.
        addHelper(0, startidx_, 1, l, r, lazy);
    }

    Sum sum(const int l, const int r) {  // r: right exclusive.
        return sumHelper(0, startidx_, 1, l, r);
    }

    void deactivate(const int pos) {
        deactivateHelper(0, startidx_, 1, pos);
    }

// protected:
// Modify this part as needed.
    void applyLazy(Sum& seg, const int idx, const int seg_l, const int seg_r, const Lazy& lazy) {
        seg += lazy * active_[idx];
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
        applyLazy(seg_[idx], idx, seg_l, seg_r, lazy);
        if (idx < startidx_) {
            addLazy(lazy_[idx * 2], lazy);
            addLazy(lazy_[idx * 2 + 1], lazy);
        }
        lazy_[idx] = kDefaultLazy;
    }

    void pull(const int idx) {
        seg_[idx] = sumOp(seg_[idx * 2], seg_[idx * 2 + 1]);
        active_[idx] = active_[idx * 2] + active_[idx * 2 + 1];
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
            pull(idx);
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

    void deactivateHelper(const int seg_l, const int seg_r, const int idx, const int pos) {
        propagate(seg_l, seg_r, idx);

        if (pos < seg_l || seg_r <= pos) {
            ; /* No-op */
        } else if (pos <= seg_l && seg_r <= pos + 1) {
            seg_[idx] = active_[idx] = 0;
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            deactivateHelper(seg_l, seg_m, idx * 2, pos);
            deactivateHelper(seg_m, seg_r, idx * 2 + 1, pos);
            pull(idx);
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
    vector<int> active_;
};

///////////////////////////////////////////////////////////////////
// MERGE SORT TREE
///////////////////////////////////////////////////////////////////

template <typename Elt>
class MergeSortTree {
public:
    MergeSortTree(const vector<Elt>& v) : N2_(upper2(v.size())), seg_(N2_ * 2) {
        for (int idx = v.size() + N2_ - 1; idx >= 1; --idx) {
            if (idx >= N2_) {
                seg_[idx].push_back(v[idx - N2_]);
            } else {
                auto& l = seg_[idx * 2];
                auto& r = seg_[idx * 2 + 1];
                seg_[idx].resize(l.size() + r.size());
                merge(begin(l), end(l), begin(r), end(r), begin(seg_[idx]));
            }
        }
    }

// Modify this part as needed.
    int query(const int l, const int r, const int k) {  // right exclusive
        return queryHelper(0, N2_, 1, l, r, k, [](auto& v, auto k) {
            return lower_bound(begin(v), end(v), k) - begin(v);
        });
    }

    template <typename Func>
    int queryHelper(
            const int seg_l, const int seg_r, const int idx,
            const int l, const int r, const int k, const Func& func) {
        if (r <= seg_l || seg_r <= l) {
            return 0;
        } else if (l <= seg_l && seg_r <= r) {
            return func(seg_[idx], k);
        } else {
            const auto seg_m = (seg_l + seg_r) / 2;
            return queryHelper(seg_l, seg_m, idx * 2, l, r, k, func) +
                queryHelper(seg_m, seg_r, idx * 2 + 1, l, r, k, func);
        }
    }

    int upper2(int n, int start = 1) {
        for (; n > 0; start *= 2, n /= 2) {
            ;
        }
        return start;
    }

    const int N2_;
    vector<vector<Elt>> seg_;
};
