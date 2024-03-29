#include "bits/stdc++.h"

#define DEFIN2(x, y) DEFIN(x); DEFIN(y)
#define DEFIN3(x, y, z) DEFIN(x); DEFIN(y); DEFIN(z)
#define DEFIN4(x, y, z, w) DEFIN(x); DEFIN(y); DEFIN(z); DEFIN(w)
#define DEFIN5(x, y, z, w, v) DEFIN(x); DEFIN(y); DEFIN(z); DEFIN(w); DEFIN(v)

#define DEFCIN(type, x) type _##x; ::std::cin >> _##x ; const type x = ::std::move(_##x)
#define DEFLINE(x) \
    ::std::string _##x; ::std::getline(::std::cin, _##x); const ::std::string x = ::std::move(_##x)

#define IN2(x, y) IN(x); IN(y)
#define IN3(x, y, z) IN(x); IN(y); IN(z)
#define IN4(x, y, z, w) IN(x); IN(y); IN(z); IN(w)
#define IN5(x, y, z, w, v) IN(x); IN(y); IN(z); IN(w); IN(v)

#define PRINT(...) ::std::cout << format(__VA_ARGS__);
#define PRINTLN(...) ::std::cout << format(__VA_ARGS__) << "\n";

#define LOOP(x) for (int _loop_macro = 0; _loop_macro < (x); ++_loop_macro)
#define FOR(i, n) for (int i = 0; i < (n); ++i)
#define FOR1(i, n) for (int i = 1; i < (n); ++i)

#define RANGE(x) begin(x), end(x)

#define MP(x, y) ::std::make_pair(x, y)
#define X first
#define Y second
#define TIE ::std::forward_as_tuple

#define ARR(N) ::std::array<int, N>

///////////////////////////////////////////////////////////////////////////////
// macro-like functions & helpers
///////////////////////////////////////////////////////////////////////////////

void ds() {
    ::std::ios::sync_with_stdio(0);
    ::std::cin.tie(0);
    ::std::cout.tie(0);
}

template <typename T = int>
T getInt() {
    T ret;
    ::std::cin >> ret;
    return ret;
}

template <typename T = int>
::std::vector<T> getInts(int N) {
    ::std::vector<T> ret(N);
    for (auto& e : ret) {
        ::std::cin >> e;
    }
    return ret;
}

template <typename T>
void Maxin(T& x, const T& y) { x = ::std::max(x, y); }

template <typename T>
void Minin(T& x, const T& y) { x = ::std::min(x, y); }

template <typename T>
bool Board(const T& x, const T& y, const T& N, const T& M) { return 0 <= x && x < N && 0 <= y && y < M; }

///////////////////////////////////////////////////////////////////////////////
// container sfinae & helper
///////////////////////////////////////////////////////////////////////////////

template <typename> struct _is_container : std::false_type {};
template <typename T, size_t N> struct _is_container<std::array<T, N>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::vector<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::list<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::deque<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::set<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::map<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::multiset<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::multimap<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::unordered_set<T, Alloc>> : std::true_type {};
template <typename T, typename Alloc> struct _is_container<std::unordered_map<T, Alloc>> : std::true_type {};

template <typename> struct _is_pair : std::false_type {};
template <typename T1, typename T2> struct _is_pair<std::pair<T1, T2>> : std::true_type {};

template <typename> struct _is_vector : std::false_type {};
template <typename T, typename Alloc> struct _is_vector<std::vector<T, Alloc>> : std::true_type {};

template <typename> struct _is_string : std::false_type {};
template <> struct _is_string<std::string> : std::true_type {};
template <typename T> using _is_string_decay = _is_string<std::decay_t<T>>;

template <typename Container>
int len(const Container& c) {
    return c.size();
}

///////////////////////////////////////////////////////////////////////////////
// STL ostream
///////////////////////////////////////////////////////////////////////////////

template <typename T, typename std::enable_if_t<_is_pair<T>::value>* = nullptr>
std::ostream& operator<< (std::ostream& out, const T& v) {
    out << "(" << v.first << ", " << v.second << ")";
    return out;
}

// TODO: make it generic
std::ostream& operator<< (std::ostream& out, const std::tuple<int, int, int>& t) {
    auto [a, b, c] = t;
    out << "(" << a << ", " << b << ", " << c << ")";
    return out;
}

// TODO: make it generic
std::ostream& operator<< (std::ostream& out, const std::tuple<int, int, int, int>& t) {
    auto [a, b, c, d] = t;
    out << "(" << a << ", " << b << ", " << c << ", " << d << ")";
    return out;
}

template <typename T, typename std::enable_if_t<_is_container<T>::value>* = nullptr>
std::ostream& operator<< (std::ostream& out, const T& v) {
    if (v.empty()) {
        out << "[]";
    } else {
        out << "[";
        for (const auto& e : v) {
            out << e << ", ";
        }
        out << "\b\b]";
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////////
// matrix printer
///////////////////////////////////////////////////////////////////////////////

template <typename T>
void printMatrix(const T& mm) {
  for (const auto& row : mm) {
    std::cout << row << '\n';
  }
}

///////////////////////////////////////////////////////////////////////////////
// string formatter
///////////////////////////////////////////////////////////////////////////////

std::string format() {
    return {};
}

template <typename T>
std::string format(const T& arg) {
    std::stringstream ss;
    ss << arg;
    return ss.str();
}

template <typename T>
std::string format(const char* fmt, T&& arg) {
    bool substituted = false;
    std::string res;
    while (*fmt != 0) {
        if (!substituted && *fmt == '{' && *(fmt + 1) == '}') {
            std::stringstream ss;
            ss << arg;
            res.append(ss.str());
            substituted = true;
            fmt += 2;
        } else {
            res.push_back(*fmt);
            ++fmt;
        }
    }
    return res;
}

template <typename T, typename... Args>
std::string format(const char* fmt, T&& arg, Args&&... args) {
    std::string res;
    while (*fmt != 0) {
        if (*fmt == '{' && *(fmt + 1) == '}') {
            std::stringstream ss;
            ss << arg;
            res.append(ss.str());
            res.append(format(fmt + 2, std::forward<Args>(args)...));
            break;

        } else {
            res.push_back(*fmt);
            ++fmt;
        }
    }
    return res;
}

///////////////////////////////////////////////////////////////////////////////
// improved pair
///////////////////////////////////////////////////////////////////////////////

template <typename T1, typename T2>
std::pair<T1, T2> operator+(const std::pair<T1, T2>& a,
                            const std::pair<T1, T2>& b) {
	return {a.first + b.first, a.second + b.second};
}

template <typename T1, typename T2>
std::pair<T1, T2>& operator+=(std::pair<T1, T2>& a, const std::pair<T1, T2>& b) {
	a.first += b.first, a.second += b.second;
	return a;
}

template <typename T1, typename T2>
std::pair<T1, T2> operator-(const std::pair<T1, T2>& a,
                            const std::pair<T1, T2>& b) {
  return {a.first - b.first, a.second - b.second};
}

template <typename T1, typename T2>
std::pair<T1, T2>& operator-=(std::pair<T1, T2>& a, const std::pair<T1, T2>& b) {
	a.first -= b.first, a.second -= b.second;
	return a;
}

namespace std {

template <typename T1, typename T2>
struct hash<std::pair<T1, T2>> {
public:
    size_t operator()(const std::pair<T1, T2>& p) const
    {
        auto hash1 = std::hash<T1>{}(p.first);
        auto hash2 = std::hash<T2>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

}   // namespace std

///////////////////////////////////////////////////////////////////////////////
// utils
///////////////////////////////////////////////////////////////////////////////

template <typename T, typename std::enable_if_t<_is_vector<std::remove_reference_t<T>>::value>* = nullptr>
auto zipIndex(T&& arr) {
    std::sort(begin(arr), end(arr));
    arr.resize(std::unique(begin(arr), end(arr)) - begin(arr));

    std::unordered_map<typename std::remove_reference_t<T>::value_type, int> mm;
    int cnt = 0;
    for (auto e : arr) {
        mm[e] = cnt++;
    }
    return mm;
}

///////////////////////////////////////////////////////////////////////////////
// end of prelude
///////////////////////////////////////////////////////////////////////////////
