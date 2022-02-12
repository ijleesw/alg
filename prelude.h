#include "bits/stdc++.h"

#define DEFIN(x) int _##x; scanf("%d", &_##x); const int x = _##x
#define DEFIN2(x, y) DEFIN(x); DEFIN(y)
#define DEFIN3(x, y, z) DEFIN(x); DEFIN(y); DEFIN(z)
#define DEFIN4(x, y, z, w) DEFIN(x); DEFIN(y); DEFIN(z); DEFIN(w)
#define DEFIN5(x, y, z, w, v) DEFIN(x); DEFIN(y); DEFIN(z); DEFIN(w); DEFIN(v)
#define DEFCIN(type, x) type _##x; ::std::cin >> _##x ; const type x = ::std::move(_##x)
#define IN(x) scanf("%d", &x)
#define CIN(x) ::std::cin >> x
#define OUT(x) printf("%d ", x)
#define COUT(x) ::std::cout << x << " "
#define OUTLN(x) printf("%d\n", x)
#define COUTLN(x) ::std::cout << x << "\n"
#define LN() printf("\n")
#define PRINT(...) ::std::cout << format(__VA_ARGS__);
#define PRINTLN(...) ::std::cout << format(__VA_ARGS__) << "\n";

#define LOOP(x) for (int _loop_macro = 0; _loop_macro < (x); ++_loop_macro)
#define MP(x, y) ::std::make_pair(x, y)
#define BOARD(x, y, N, M) (0 <= x && x < N && 0 <= y && y < M)

///////////////////////////////////////////////////////////////////////////////
// container sfinae
///////////////////////////////////////////////////////////////////////////////

template <typename> struct _is_vector : std::false_type {};
template <typename T, typename Alloc> struct _is_vector<std::vector<T, Alloc>> : std::true_type {};

template <typename> struct _is_pair : std::false_type {};
template <typename T1, typename T2> struct _is_pair<std::pair<T1, T2>> : std::true_type {};

template <typename> struct _is_string : std::false_type {};
template <> struct _is_string<std::string> : std::true_type {};
template <typename T> using _is_string_decay = _is_string<std::decay_t<T>>;

///////////////////////////////////////////////////////////////////////////////
// string formatter
///////////////////////////////////////////////////////////////////////////////

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
// for debug
///////////////////////////////////////////////////////////////////////////////

template <typename T, typename std::enable_if_t<_is_pair<T>::value>* = nullptr>
std::ostream& operator<< (std::ostream& out, const T& v) {
    out << format("({}, {})", v.first, v.second);
    return out;
}

template <typename T, typename std::enable_if_t<_is_vector<T>::value>* = nullptr>
std::ostream& operator<< (std::ostream& out, const T& v) {
    if (v.empty()) {
        out << "[]";
    } else {
        out << "[";
        for (const auto& e : v) {
            out << e << " ";
        }
        out << "\b]";
    }
    return out;
}

///////////////////////////////////////////////////////////////////////////////
// hash pair
///////////////////////////////////////////////////////////////////////////////

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
// end of file
///////////////////////////////////////////////////////////////////////////////

