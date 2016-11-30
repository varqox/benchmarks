// Krzysztof Małysa
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,n) for (int i = (a), i##__ = (n); i <= i##__; ++i)
#define REP(i,n) FOR(i,0,n-1)
#define FORD(i,a,n) for (int i = (a), i##__ = (n); i >= i##__; --i)
#define ALL(x) x.begin(), x.end()
#define EB emplace_back
#define ST first
#define ND second
#define OO(A) template<class... T> ostream& operator<<(ostream& os, const A<T...>& x) { return __o(os, ALL(x)); }
#define SZ(x) ((int)x.size())

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef vector<PII> VPII;

template<class A, class B> ostream& operator<<(ostream&, const pair<A, B>&);
template<class I> ostream& __o(ostream&, I, I);
template<class T, size_t N> ostream& operator<<(ostream& os, const array<T, N>& x) { return __o(os, ALL(x)); }
OO(vector) OO(deque) OO(set) OO(multiset) OO(map) OO(multimap)
template<class A, class B> ostream& operator<<(ostream& os, const pair<A, B>& p) {
	return os << "(" << p.ST << ", " << p.ND << ")";
}
template<class I> ostream& __o(ostream& os, I a, I b) {
	os << "{";
	for (; a != b;)
		os << *a++, cerr << (a == b ? "" : " ");
	return os << "}";
}
template<class I> ostream& __d(ostream& os, I a, I b) {
	os << "{\n";
	for (I c = a; a != b; ++a)
		os << "  " << distance(c, a) << ": " << *a << endl;
	return os << "}";
}
template<class... T> void __e(T&&... a) {
	int t[] = {(cerr << forward<T>(a), 0)...}; (void)t;
	cerr << endl;
}

template<class A, class B> void mini(A& a, B&& b) { if (b < a) a = b; }
template<class A, class B> void maxi(A& a, B&& b) { if (b > a) a = b; }
int ceil2(int x) { return 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)); }

#ifdef DEBUG
# define D(...) __VA_ARGS__
#else
# define D(...)
#endif

#define LOG(x) D(cerr << #x ": " << x)
#define LOGN(x) D(LOG(x) << endl)
#define DUMP(x) D(cerr << #x ": ", __d(cerr, ALL(x)) << endl)
#define E(...) D(__e(__VA_ARGS__))
#define endl '\n'
constexpr char nl = '\n';
// End of templates

#include <sys/time.h>

class Timer {
	struct timeval begin;

public:
	Timer() { restart(); }

	void restart() { gettimeofday(&begin, NULL); }

	long long microtime() {
		struct timeval end;
		gettimeofday(&end, NULL);
		return (end.tv_sec - begin.tv_sec) * 1000000LL + end.tv_usec -
			begin.tv_usec;
	}

	double time() { return microtime() * 0.000001; }
};

template<size_t N>
array<char, N> make_concat(const string& a, const string& b, const string& c) {
	size_t sz = a.size() + b.size() + c.size();
	assert(sz < N);
	array<char, N> res;
	memcpy(res.data(), a.data(), a.size());
	memcpy(res.data() + a.size(), b.data(), b.size());
	memcpy(res.data() + a.size() + b.size(), c.data(), c.size());
	res[sz] = '\0';
	return res;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n = 10000000;
	string a = "219489840124";
	string b = "rdhfhoisdfusd9f97";
	string c = ";[;];];[][;;];;";
	// cin >> a >> b >> c;

	Timer t;
	REP (i, n) {
		char buff[4096];
		size_t sz = 0;
		memcpy(buff, a.data(), a.size()); sz += a.size();
		memcpy(buff + sz, b.data(), b.size()); sz += b.size();
		memcpy(buff + sz, c.data(), c.size()); sz += c.size();
		assert(sz < sizeof(buff));
		__asm__ __volatile__ ("" :: "m" (buff)); // disable optimizing it out
		__asm__ __volatile__ ("" :: "m" (sz)); // disable optimizing it out
	}
	cout << "char[]: " << t.time() << nl << flush;

	t.restart();
	REP (i, n) {
		auto x = make_concat<4096>(a, b, c);
		__asm__ __volatile__ ("" :: "m" (x)); // disable optimizing it out
	}
	cout << "array<>: " << t.time() << nl << flush;

	t.restart();
	REP (i, n) {
		string buff;
		buff.reserve(a.size() + b.size() + c.size());
		buff += a;
		buff += b;
		buff += c;
		__asm__ __volatile__ ("" :: "m" (buff)); // disable optimizing it out
	}
	cout << "string: " << t.time() << nl << flush;
	return 0;
}
