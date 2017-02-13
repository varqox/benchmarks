// Krzysztof Małysa
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,n) for (decltype(a) i = (a), i##__ = (n); i <= i##__; ++i)
#define REP(i,n) FOR(i,0,(n)-1)
#define FORD(i,a,n) for (decltype(n) i = (a), i##__ = (n); i >= i##__; --i)
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
		os << *a++, os << (a == b ? "" : " ");
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

template<class A, class B> inline void mini(A& a, B&& b) { if (b < a) a = b; }
template<class A, class B> inline void maxi(A& a, B&& b) { if (b > a) a = b; }
inline int ceil2(int x) {
	return (x < 2 ? 1 : 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)));
}

#ifdef DEBUG
# define D(...) __VA_ARGS__
#else
# define D(...)
#endif

#define LOG(x) D(cerr << #x ": " << x)
#define LOGN(x) D(LOG(x) << endl)
#define DUMP(x) D(cerr << #x ": ", __d(cerr, ALL(x)) << endl)
#define E(...) D(__e(__VA_ARGS__))
constexpr char nl = '\n';
// End of templates

struct treap {
	treap* left = nullptr;
	treap* right = nullptr;
	int val;
	int sz = 1;
	int rank = rand();

	treap(int x = 0) : val(x) {}
};

inline int sz(treap* x) { return (x ? x->sz : 0); }

inline void update(treap* a) {
	a->sz = 1 + sz(a->left) + sz(a->right);
}

inline treap* merge(treap* a, treap* b) {
	if (!a)
		return b;
	if (!b)
		return a;

	if (a->rank > b->rank) {
		a->right = merge(a->right, b);
		update(a);
		return a;
	} else {
		b->left = merge(a, b->left);
		update(b);
		return b;
	}
}

inline pair<treap*, treap*> split(treap* a, int k) {
	if (!a)
		return {nullptr, nullptr};

	int sl = sz(a->left);
	if (sl >= k) {
		auto p = split(a->left, k);
		a->left = p.ND;
		update(a);
		return {p.ST, a};

	} else {
		auto p = split(a->right, k - sl - 1);
		a->right = p.ST;
		update(a);
		return {a, p.ND};
	}
}

inline treap* insert(treap* a, int pos, int val) {
	auto p = split(a, pos);
	return merge(p.ST, merge(new treap(val), p.ND));
}

inline treap* erase(treap* a, int pos) {
	auto p = split(a, pos);
	auto p1 = split(p.ND, 1);
	delete p1.ST;
	return merge(p.ST, p1.ND);
}

inline void _print(treap* a) {
	if (a) {
		_print(a->left);
		cerr << a->val << ' ';
		_print(a->right);
	}
}

inline void print(treap* a) {
	cerr << "{", _print(a), cerr << "}\n";
}

inline int find(treap* a, int val) {
	if (!a)
		return -0x3f3f3f3f;
	if (a->val == val)
		return sz(a->left);
	else if (a->val > val)
		return find(a->left, val);
	else
		return sz(a->left) + 1 + find(a->right, val);
}

inline int upper_bound(treap* a, int val) {
	if (!a)
		return 0;
	if (a->val <= val)
		return sz(a->left) + 1 + upper_bound(a->right, val);
	else
		return upper_bound(a->left, val);
}

inline treap* insertVal(treap* a, int val) {
	return insert(a, upper_bound(a, val), val);
}

inline treap* eraseVal(treap* a, int val) {
	int pos = find(a, val);
	return (pos >= 0 ? erase(a, pos) : a);
}

#include <sys/time.h>

class Timer {
	struct timeval begin;

public:
	Timer() { start(); }

	void start() { gettimeofday(&begin, NULL); }

	long long microtime() {
		struct timeval end;
		gettimeofday(&end, NULL);
		return (end.tv_sec - begin.tv_sec) * 1000000LL + end.tv_usec -
			begin.tv_usec;
	}

	double time() { return microtime() * 0.000001; }
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	srand(10101029);
	constexpr int N = 1e6;
	VI v(N);
	for (int& x : v)
		x = rand();

	VI v1 = v;
	random_shuffle(ALL(v1));

	// Benchmark
	Timer timer;

	treap *t = nullptr;
	timer.start();
	for (int x : v)
		t = insertVal(t, x);
	cout << "Treap - insert: " << fixed << setprecision(4) << timer.time() << " s" << endl;

	timer.start();
	for (int x : v1)
		t = eraseVal(t, x);
	cout << "Treap - erase: " << fixed << setprecision(4) << timer.time() << " s" << endl;

	multiset<int> S;
	timer.start();
	for (int x : v)
		S.insert(x);
	cout << "Multiset - insert: " << fixed << setprecision(4) << timer.time() << " s" << endl;

	timer.start();
	for (int x : v1)
		S.erase(x);
	cout << "Multiset - erase: " << fixed << setprecision(4) << timer.time() << " s" << endl;
	return 0;
}
