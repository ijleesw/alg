///////////////////////////////////////
// Fenwick Tree
///////////////////////////////////////

template <typename Val = int>
class FenwickTree {
public:
  FenwickTree(int n) : arr_(n + 1, kDefaultVal) {}

  void add(int idx, Val val) {
    ++idx;
    while (idx < (int)arr_.size()) {
      arr_[idx] = accumOp(arr_[idx], val);
      idx += (idx & -idx);
    }
  }

  // Accumulation of leading cnt elements.
  Val accumLeading(int cnt) {
    Val ret = kDefaultVal;
    while (cnt >= 1) {
      ret = accumOp(ret, arr_[cnt]);
      cnt -= (cnt & -cnt);
    }
    return ret;
  }

// protected:
// Modify this part as needed.
  const Val kDefaultVal = 0;
  Val accumOp(const Val& lhs, const Val& rhs) {
    return lhs + rhs;
  }

// private:
  vector<Val> arr_;
};


///////////////////////////////////////
// Fenwick Tree 2D
///////////////////////////////////////

template <typename Val = int>
class FenwickTree2D {
public:
  FenwickTree2D(int n, int m) : arr_(n + 1, vector<Val>(m + 1, kDefaultVal)) {}

  void add(int x, int y, Val val) {
    ++x;
    ++y;
    while (x < (int)arr_.size()) {
      auto& row = arr_[x];
      int yy = y;
      while (yy < (int)row.size()) {
        row[yy] = accumOp(row[yy], val);
        yy += (yy & -yy);
      }
      x += (x & -x);
    }
  }

  // Accumulation of leading y elements of leading x rows.
  Val accumLeading(int x, int y) {
    Val ret = kDefaultVal;
    while (x >= 1) {
      auto& row = arr_[x];
      int yy = y;
      while (yy >= 1) {
        ret = accumOp(ret, row[yy]);
        yy -= (yy & -yy);
      }
      x -= (x & -x);
    }
    return ret;
  }

// protected:
// Modify this part as needed.
  const Val kDefaultVal = 0;

  Val accumOp(const Val& lhs, const Val& rhs) {
    return lhs + rhs;
  }

// private:
  vector<vector<Val>> arr_;
};
