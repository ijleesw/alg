template <typename Integer = int>
class SegmentTree {
public:
    SegmentTree(int size) : N2(upper2(size)), seg(N2 * 2, 0) {}

    void add(const Integer val) {
        int idx = N2 + val;
        while (idx > 0) {
            ++seg[idx];
            idx /= 2;
        }
    }

    Integer sum(const int l, const int r) {  // right exclusive
        return sumHelper(0, N2, 1, l, r);
    }

// private:
    Integer sumHelper(const int seg_l, const int seg_r, const int idx, const int l, const int r) {
        if (r <= seg_l || seg_r <= l) {
            return 0;
        } else if (l <= seg_l && seg_r <= r) {
            return seg[idx];
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

    const int N2;
    vector<Integer> seg;
};

