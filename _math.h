// Returns smallest {gcd, x, y} s.t. $ax + by = gcd(a, b)$.
// > Proof: https://math.stackexchange.com/a/670460
template <typename ed = long long>  // euclidean domain(ring)
tuple<ed, ed, ed> EEA(ed a, ed b) {
  ed r[2] = {a, b};
  ed s[2] = {1, 0};
  ed t[2] = {0, 1};
  while (true) {
    ed q = r[0] / r[1];
    ed rr = r[0] - (q * r[1]);
    ed ss = s[0] - (q * s[1]);
    ed tt = t[0] - (q * t[1]);

    if (rr == 0) {
      return make_tuple(r[1], s[1], t[1]);
    }

    tie(r[0], r[1], s[0], s[1], t[0], t[1]) = 
        forward_as_tuple(r[1], rr, s[1], ss, t[1], tt);
  }
}

template <typename ed = long long>  // euclidean domain(ring)
ed inverse(ed a, ed mod) {
  ed gcd, x, y;
  tie(gcd, x, y) = EEA(a, mod);
  assert(gcd == 1);
  return (x + mod) % mod;
}

//  Returns the Möbius array.
//    mu[1] = 1
//    mu[2] = mu[3] = mu[5] = ... = -1
vector<int> mobius(int n) {  // n: inclusive
  vector<int> primes;
  vector<bool> visited(n + 1, false);
  vector<int> mu(n + 1, 0);
  mu[1] = 1;

  for (int i = 2; i <= n; ++i) {
    if (!visited[i]) {
      primes.push_back(i);
      mu[i] = -1;
    }
    for (int j = 0; j < primes.size() && i * primes[j] <= n; ++j) {
      visited[i * primes[j]] = true;
      if (i % primes[j] == 0) {
        break;
      }
      mu[i * primes[j]] = mu[i] * mu[primes[j]];
    }
  }
  return mu;
}
