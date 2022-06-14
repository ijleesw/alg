# Returns smallest {gcd, x, y} s.t. $ax + by = gcd(a, b)$.
# > Proof: https://math.stackexchange.com/a/670460
def EEA(a, b):
  r, s, t = [a, b], [1, 0], [0, 1]

  while True:
    q = r[0] // r[1]
    rr = r[0] - q*r[1]
    ss = s[0] - q*s[1]
    tt = t[0] - q*t[1]

    if rr == 0:
      return r[1], s[1], t[1]

    r[0], r[1], s[0], s[1], t[0], t[1] = \
      r[1], rr, s[1], ss, t[1], tt

# Prefer pow(a, -1, mod) to this function.
def inverse(a, mod):
  gcd, x, y = EEA(a, mod)
  assert(gcd == 1)
  return (x + mod) % mod

# Returns the Möbius array.
#   mu[1] = 1
#   mu[2] = mu[3] = mu[5] = ... = -1
#
# Slower in C++, faster in PyPy3.
def mobius(n):  # n: inclusive
  mu = [0, 1] + [-1] * (n)
  for i in range(2, len(mu)):
    if mu[i] == 0:
      continue
    for j in range(i*2, len(mu), i):
      mu[j] -= mu[i]
  return mu

# Returns Möbius array.
# Use when primes are needed.
def mobius(n):  # n: inclusive
  primes = []
  visited = [False] * (n+1)
  mu = [0, 1] + [0] * (n-1)

  for i in range(2, n+1):
    if not visited[i]:
      primes.append(i)
      mu[i] = -1
    for j in range(0, len(primes)):
      if i * primes[j] > n:
        break
      visited[i * primes[j]] = True
      if i % primes[j] == 0:
        break
      mu[i * primes[j]] = mu[i] * mu[primes[j]]
  return mu
