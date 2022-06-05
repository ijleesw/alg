template <typename T = int>
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
        if (size(ra) < size(rb)) {
            swap(ra, rb);
        }
        // now size(ra) >= size(rb).
        arr_[ra] -= size(rb);
        arr_[rb] = ra;
        return true;
    }

// private:
    T size(int n) {
        return -arr_[root(n)];
    }

    // Positive: parent idx
    // Negative: -(subtree size)
    vector<T> arr_;
};
