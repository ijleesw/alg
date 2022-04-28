using cplx = complex<double>;

namespace FFT {
  namespace {
    const double PI = acos(-1);

    void FFT(vector<cplx>& f, bool inv = false) {
      int n = f.size();
      // Bit reversal (ref. https://tistory.joonhyung.xyz/6)
      for (int i = 1, j = 0; i < n; ++i){
        int b = n/2;
        while (!((j ^= b) & b)) {
          b /= 2;
        }
        if (i < j) {
          swap(f[i], f[j]);
        }
      }

      for (int k = 1; k < n; k *= 2){
        double a = (inv ? PI/k : -PI/k);
        cplx w{cos(a), sin(a)};

        for (int i = 0; i < n; i += k * 2){
          cplx wp{1, 0};
          for (int j = 0; j < k; ++j){
            cplx x = f[i + j];
            cplx y = f[i + j + k] * wp;
            f[i + j] = x + y;
            f[i + j + k] = x - y;
            wp *= w;
          }
        }
      }

      if (inv) {
        for (int i = 0; i < n; ++i) {
          f[i] /= n;
        }
      }
    }
  }  // namespace

  // c0 = a0*b0, c1 = a0*b1 + a1*b0, c2 = a0*b2 + a1*b1 + a2*b0, and so on.
  vector<cplx> multiply(vector<cplx> a, vector<cplx> b) {
    int n = 1;
    while (n < a.size() + b.size()) {
      n *= 2;
    }
    a.resize(n);
    b.resize(n);

    FFT(a);
    FFT(b);

    vector<cplx> c(n);
    for (int i = 0; i < n; ++i) {
      c[i] = a[i] * b[i];
    }
    FFT(c, /*inv=*/true);
    return c;
  }
}  // namespace FFT
