// Krzysztof Małysa
// Program to test text structures/functions speed
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define FOR(i,a,n) for (int i = (a), __n ## i = n; i < __n ## i; ++i)
#define REP(i,n) FOR(i,0,n)
#define FORD(i,a,n) for (int i = (a), __n ## i = n; i >= __n ## i; --i)
#define LET(x,a) __typeof(a) x = (a)
#define FOREACH(i,x) for (LET(i, x.begin()), __n##i = x.end(); i != __n##i; ++i)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define ST first
#define ND second
#define MP make_pair
#define PB push_back
#define O(...) ostream& operator <<(ostream& os, const __VA_ARGS__& x)
#define OO(...) O(__VA_ARGS__) { return __out(os, ALL(x)); }
#define T template
#define CL class

typedef unsigned uint;
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<LL> VLL;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef vector<VPII> VVPII;
typedef pair<LL, LL> PLLLL;
typedef vector<PLLLL> VPLLLL;
typedef vector<bool> VB;
typedef vector<char> VC;

T<CL A>
inline A abs(const A& a) { return a < A() ? -a : a; }

T<CL A, CL B>
inline void mini(A& a, const B& b) {
	if (b < a)
		a = b;
}

T<CL A, CL B>
inline void maxi(A& a, const B& b) {
	if (b > a)
		a = b;
}

T<CL Iter>
ostream& __out(ostream& os, Iter a, Iter b, const string& s = ", ");

T<CL A, CL B>
O(pair<A, B>);

T<CL A>
OO(vector<A>)

T<CL A>
OO(deque<A>)

T<CL A>
OO(list<A>)

T<CL A, CL B>
OO(set<A, B>)

T<CL A, CL B, CL C>
OO(map<A, B, C>)

T<CL A, CL B>
OO(multiset<A, B>)

T<CL A, CL B, CL C>
OO(multimap<A, B, C>)

T<CL Iter>
ostream& __out(ostream& os, Iter a, Iter b, const string& s) {
	os << "{";
	if (a != b) {
		os << *a;
		while (++a != b)
			os << s << *a;
	}
	return os << "}";
}

T<CL A, CL B>
O(pair<A, B>) {
	return os << "(" << x.ST << ", " << x.ND << ")";
}

CL Input {
	static const int BUFF_SIZE = 1 << 16;
	unsigned char buff[BUFF_SIZE], *pos, *end;

	void grabBuffer() {
		pos = buff;
		end = buff + read(0, buff, BUFF_SIZE);
	}

public:
	Input() : pos(buff), end(buff) {}

	int peek() {
		if (pos == end)
			grabBuffer();
		return pos != end ? *pos : -1;
	}

	int getChar() {
		if (pos == end)
			grabBuffer();
		return pos != end ? *pos++ : -1;
	}

	void skipWhiteSpaces() {
		while (isspace(peek()))
			++pos;
	}

	T<CL A>
	A get();

	void operator()(char* s) {
		skipWhiteSpaces();
		while (!isspace(peek()))
			*s++ = *pos++;
		*s = '\0';
	}

	T<CL A>
	void operator()(A& x) { x = get<A>(); }

	T<CL A, CL B>
	void operator()(A& a, B& b) { operator()(a), operator()(b); }

	T<CL A, CL B, CL C>
	void operator()(A& a, B& b, C& c) { operator()(a, b), operator()(c); }

	T<CL A, CL B, CL C, CL D>
	void operator()(A& a, B& b, C& c, D& d) {
		operator()(a, b, c);
		operator()(d);
	}

	T<CL A, CL B, CL C, CL D, CL E>
	void operator()(A& a, B& b, C& c, D& d, E& e) {
		operator()(a, b, c, d);
		operator()(e);
	}

	T<CL A, CL B, CL C, CL D, CL E, CL F>
	void operator()(A& a, B& b, C& c, D& d, E& e, F& f) {
		operator()(a, b, c, d, e);
		operator()(f);
	}

	Input& operator>>(char *s) {
		operator()(s);
		return *this;
	}

	T<CL A>
	Input& operator>>(A& a) {
		operator()(a);
		return *this;
	}
} input;

T<> char Input::get<char>() {
	skipWhiteSpaces();
	return *pos++;
}

T<> uint Input::get<uint>() {
	skipWhiteSpaces();
	uint x = 0;
	while (isdigit(peek()))
		x = x * 10 + *pos++ - '0';
	return x;
}

T<> int Input::get<int>() {
	skipWhiteSpaces();
	return peek() == '-' ? (++pos, -get<uint>()) : get<uint>();
}

T<> ULL Input::get<ULL>() {
	skipWhiteSpaces();
	ULL x = 0;
	while (isdigit(peek()))
		x = x * 10 + *pos++ - '0';
	return x;
}

T<> LL Input::get<LL>() {
	skipWhiteSpaces();
	return peek() == '-' ? (++pos, -get<ULL>()) : get<ULL>();
}

T<> string Input::get<string>() {
	skipWhiteSpaces();
	string x;
	while (!isspace(peek()))
		x += *pos++;
	return x;
}

#undef T
#undef CL
#ifdef DEBUG
# define D(...) __VA_ARGS__
# define E(...) eprintf(__VA_ARGS__)
# define OUT(a,b) cerr << #a ":", __out(cerr, a, b), E("\n")
# define LOG(x) cerr << #x ": " << (x)
# define LOG2(x, y) cerr << x ": " << (y)
# define LOGN(x) LOG(x) << endl
# define LOGN2(x, y) LOG2(x, y) << endl
#else
# define D(...)
# define E(...)
# define OUT(...)
# define LOG(...)
# define LOG2(...)
# define LOGN(...)
# define LOGN2(...)
#endif
/// End of templates

struct xxx {
	int p;
	char t[200];

	xxx(): p(0) {}

	void clear() { p = 0; }

	xxx& operator <<(const char *str) {
		// while (*str) {
		// 	t[p] = *str;
		// 	++p;
		// 	++str;
		// }
		int k = strlen(str);
		strcpy(t + p, str);
		p += k;
		// t[p += k] = '\0';

		return *this;
	}
};

class Cstring {
private:
	size_t len_, real_len_;
public:
	char *p;

	explicit Cstring(size_t len = 0, char c = '\0'): len_(len),
			real_len_(len + 1), p((char*)malloc(real_len_)) {
		if (p == NULL)
			throw std::bad_alloc();

		memset(p, c, len);
		p[len] = '\0';
	}

	Cstring(const char* str, size_t len = -1)
			: len_(min(len, strlen(str))), real_len_(len_ + 1),
			p((char*)malloc(real_len_)) {
		if (p == NULL)
			throw std::bad_alloc();

		strcpy(p, str);
	}

	Cstring(const Cstring& x): len_(x.len_), real_len_(len_ + 1),
			p((char*)malloc(real_len_)) {
		if (p == NULL)
			throw std::bad_alloc();

		strcpy(p, x.p);
	}

	~Cstring() { free(p); }

	void clear() { len_ = 0; }

	void reserve(size_t len) {
		if (len + 1 > real_len_) {
			size_t new_real_len = std::max(len + 1, real_len_ << 1);
			if (NULL == realloc(p, new_real_len))
				throw std::bad_alloc();

			real_len_ = new_real_len;
		}
	}

	void append(const char* str, size_t len) {
		reserve(len_ + len);
		strncpy(p + len_, str, len);
		p[len_ += len] = '\0';
	}

	Cstring& operator<<(const Cstring& x) {
		append(x.p, x.len_);
		return *this;
	}

	Cstring& operator<<(const char* str) {
		append(str, strlen(str));
		return *this;
	}

	size_t size() { return len_; }
};

inline std::string const& to_string(std::string const& s) { return s; }

inline size_t size(const std::string& str) { return str.size(); }

inline size_t size(const char* str) { return strlen(str); }

constexpr inline size_t size(char) { return 1; }

template<typename... Args>
inline std::string stringer(Args const&... args)
{
	std::string result;
	size_t len = 0;
	bool t[] = { (len += size(args), false)... };
	(void)t;
	result.reserve(len);
	bool x[100] = {(result += args, false)...};
	(void)x;
	return result;
}

template<class T>
inline string& operator<<(const string& s, const T& x) {
	return const_cast<string&>(s) += x;
}

int main() {
	char t[200];
	string s;
	s.reserve(100);
	xxx x;
	Cstring str;
	str.reserve(100);

#define WHICH 1 // SET THIS TO CHOOSE WHICH TEST WILL BE RUN

	REP (i, 20000000) {
#if WHICH == 1
		// std::string::append()
		s.clear();
		s.append("12312948").append(": + ").append("askfhkas").append(" - ").append("iuqwruiuwiq");

#elif WHICH == 2
		// std::string operator<<()
		s.clear();
		s << "12312948" << ": + " << "askfhkas" << " - " << "iuqwruiuwiq";

#elif WHICH == 3
		// std::string + stringer
		s = stringer("12312948", ": + ", "askfhkas", " - ", "iuqwruiuwiq");

#elif WHICH == 4
		// snprintf
		snprintf(t, 200, "%s: + %s - %s", "12312948", "askfhkas", "iuqwruiuwiq");

#elif WHICH == 5
		// raw copy function calls
		int a = strlen("12312948");
		int b = a + strlen(": + ");
		int c = b + strlen("askfhkas");
		int d = c + strlen(" - ");
		strcpy(t, "12312948");
		strcpy(t + a, ": + ");
		strcpy(t + b, "askfhkas");
		strcpy(t + c, " - ");
		strcpy(t + d, "iuqwruiuwiq");

#elif WHICH == 6
		// sample class to operate on raw copy function calls
		x.clear(); x << "12312948" << ": + " << "askfhkas" << " - " << "iuqwruiuwiq";

#elif WHICH == 6
		// Cstring
		str.clear(); str << "12312948" << ": + " << "askfhkas" << " - " << "iuqwruiuwiq";
#endif
	}

	printf("%s\n", t);
	printf("%s\n", s.c_str());
	printf("%s\n", x.t);
	printf("%s\n", str.p);
	return 0;
}
