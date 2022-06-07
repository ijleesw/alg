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
