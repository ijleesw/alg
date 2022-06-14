class SegmentTree:
  def __init__(self, N):
    self._N = N
    self._arr = [0 for _ in range(N*2)]

  def op(self, lhs, rhs):
    return lhs + rhs

  def add(self, idx, val):
    idx += self._N
    while idx > 0:
      self._arr[idx] = self.op(self._arr[idx], val)
      idx = idx // 2

  def sum(self, lidx, ridx):  # ridx: exclusive
    lidx, ridx = lidx + self._N, ridx + self._N
    ret = 0
    while lidx < ridx:
      if lidx % 2 == 1:
        ret = self.op(ret, self._arr[lidx])
        lidx += 1
      if ridx % 2 == 1:
        ridx -= 1
        ret = self.op(ret, self._arr[ridx])
      lidx, ridx = lidx // 2, ridx // 2
    return ret
