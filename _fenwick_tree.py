class FenwickTree:
  def __init__(self, N):
    self._N = N
    self._arr = [0 for _ in range(N)]

  def op(self, lhs, rhs):
    return lhs + rhs

  def add(self, idx, val):
    idx += 1
    while idx < self._N:
      self._arr[idx] = self.op(self._arr[idx], val)
      idx += (idx & -idx)

  def accumLeading(self, cnt):
    ret = 0
    while cnt >= 1:
      ret = self.op(ret, self._arr[cnt])
      cnt -= (cnt & -cnt)
    return ret
