class UnionFind:
  def __init__(self, N):
    self._arr = [-1 for _ in range(N)]

  def root(self, i):
    if self._arr[i] < 0:
      return i
    self._arr[i] = self.root(self._arr[i])
    return self._arr[i]

  def size(self, i):
    return -self._arr[self.root(i)]

  def merge(self, a, b):
    ra, rb = self.root(a), self.root(b)
    if ra == rb:
      return
    if self.size(ra) < self.size(rb):
      ra, rb = rb, ra   # now self.size(ra) >= self.size(rb).
    self._arr[ra] += self._arr[rb]
    self._arr[rb] = ra
