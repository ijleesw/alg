template <typename Val = int>
class FenwickTree {
public:
  FenwickTree(int n) : arr_(n + 1) {}

  void add(int idx, Val val) {
    ++idx;
    while (idx < (int)arr_.size()) {
      arr_[idx] = accumOp(arr_[idx], val);
      idx += (idx & -idx);
    }
  }

  Val accumLeading(int idx) {
    Val ret = kDefaultVal;
    while (idx >= 1) {
      ret = accumOp(ret, arr_[idx]);
      idx -= (idx & -idx);
    }
    return ret;
  }

// protected:
// Modify this part as needed.
  static const Val kDefaultVal = 0;
  Val accumOp(const Val& lhs, const Val& rhs) {
    return lhs + rhs;
  }

// private:
  vector<Val> arr_;
};
