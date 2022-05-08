////////////////////////////////////////////////////////
// Complex FFT
////////////////////////////////////////////////////////

using cplx = complex<double>;
using cvec = vector<cplx>;

namespace FFT {
  namespace {
    const double PI = acos(-1);

    void FFT(cvec& f, bool inv = false) {
      int n = f.size();
      // Bit reversal.
      // Given a bitset,
      //   we push it to the first half if even and to the second half if odd.
      //   It means that the leading bit is set by (equals to) the trailing bit.
      //   (ref. https://tistory.joonhyung.xyz/6)
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
  cvec convRef(cvec& a, cvec& b) {
    int n = 1;
    while (n < a.size() + b.size()) {
      n *= 2;
    }
    a.resize(n);
    b.resize(n);

    FFT(a);
    FFT(b);

    cvec c(n);
    for (int i = 0; i < n; ++i) {
      c[i] = a[i] * b[i];
    }
    FFT(c, /*inv=*/true);
    return c;
  }

  cvec conv(cvec a, cvec b) {
    return convRef(a, b);
  }
}  // namespace FFT


////////////////////////////////////////////////////////
// Z_n FFT (https://www.acmicpc.net/source/19425849)
////////////////////////////////////////////////////////

// constexpr int powmod(long long a, long long b, int mod) {
//     a %= mod; a += mod; a %= mod;
//     int r = 1 % mod;
//     for ( ; b > 0; b /= 2) {
//         if (b % 2) r = r * a % mod;
//         a = a * a % mod;
//     }
//     return r;
// }
//
// constexpr int invmod(long long a, int mod) {
//     return powmod(a, mod - 2, mod);
// }
//
// template <int prime, int primitive_root>
// struct FFT {
//     static const int P = prime;
//     static const int PR = primitive_root;
//     static const int PRI = invmod(PR, P);
//     static const int MSZ = (P - 1) & (1 - P);
//     static const int W = powmod(PR, (P - 1) / MSZ, P);
//     static const int WI = powmod(PRI, (P - 1) / MSZ, P);
//
//     static void fft(int sz, int* a, bool inv) {
//         int w = powmod(inv ? WI : W, MSZ / sz, P);
//         for (int ssz = sz / 2; ssz; ssz /= 2) {
//             for (int i = 0; i < sz; i += ssz * 2) {
//                 long long wt = 1;
//                 for (int j = 0; j < ssz; ++j) {
//                     int &lft = a[i + j];
//                     int &rgh = a[i + j + ssz];
//                     int lftold = lft;
//                     lft = (lft + rgh) % P;
//                     rgh = (lftold + (P - rgh)) * wt % P;
//                     wt = wt * w % P;
//                 }
//             }
//             w = 1LL * w * w % P;
//         }
//         if (inv) {
//             long long invsz = invmod(sz, P);
//             for (int i = 0; i < sz; ++i) a[i] = a[i] * invsz % P;
//         }
//         for (int j = 0, i = 1; i < sz; ++i) {
//             int dg = sz / 2;
//             for (; j & dg; dg >>= 1) j ^= dg;
//             j ^= dg;
//             if (i < j) {
//                 int tmp = a[i]; a[i] = a[j]; a[j] = tmp;
//             }
//         }
//     }
//
//     static vector<int> convolution(const vector<int>& a, const vector<int>& b) {
//         int sz = a.size() + b.size();
//         int fftsz = sz;
//         while (fftsz & (fftsz - 1)) fftsz += fftsz & -fftsz;
//         vector<int> av(fftsz);
//         vector<int> bv(fftsz);
//         for (int i = 0, ilim = a.size(); i < ilim; ++i) av[i] = a[i];
//         for (int i = 0, ilim = b.size(); i < ilim; ++i) bv[i] = b[i];
//         fft(fftsz, av.data(), false);
//         fft(fftsz, bv.data(), false);
//         for (int i = 0; i < fftsz; ++i) av[i] = 1LL * av[i] * bv[i] % P;
//         fft(fftsz, av.data(), true);
//         return av;
//     }
// };
