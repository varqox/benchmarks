// Krzysztof Małysa
#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,n) for (auto i ## __ = (n), i = (a); i <= i ## __; ++i)
#define FORD(i,a,n) for (auto i = (a), i ## __ = (n); i >= i ## __; --i)
#define REP(i,n) FOR(i, 0, n - 1)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int(x.size()))
#define EB emplace_back
#define ST first
#define ND second
#define tpv typedef vector<

typedef long long LL;
typedef pair<int, int> PII;
tpv int> VI;
tpv VI> VVI;
tpv PII> VPII;
tpv LL> VLL;

constexpr char nl = '\n';
#define endl nl

#define ris return *this
#define tem template<class T

tem, class B> inline void mini(T&& a, B&& b) { if (b < a) a = b; }
tem, class B> inline void maxi(T&& a, B&& b) { if (b > a) a = b; }
int ceil2(int x) { return x < 2 ? 1 : 1 << (sizeof(x) * 8 - __builtin_clz(x - 1)); }

tem> struct Dump { T a, b; };
tem> auto dump(T&& x) -> Dump<decltype(x.begin())> { return {ALL(x)}; }
struct Debug {
	~Debug() { cerr << endl; }
	tem> auto operator<<(T x) -> decltype(cerr << x, *this) { cerr << boolalpha << x; return *this; }
	tem> auto operator<<(T x) -> decltype(x.begin(), *this) {
		auto a = x.begin(), b = x.end();
		*this << "{";
		for (; a != b;)
			*this << *a++, *this << (a == b ? "" : " ");
		return *this << "}";
	}
	tem, class B> Debug& operator<<(pair<T, B> p) { ris << "(" << p.ST << ", " << p.ND << ")"; }
	tem> Debug& operator<<(Dump<T> d) {
		*this << "{\n";
		for (T a = d.a, c = a; a != d.b; ++a)
			*this << "  " << distance(c, a) << ": " << *a << '\n';
		ris << "}";
	}
};
struct Foo {tem>Foo& operator<<(T&&) {ris;}};

#ifdef DEBUG
# define DEB(x...) x
# define deb Debug()
#else
# define DEB(...)
# define deb Foo()
#endif
#define imie(x...) #x ": " << (x) << " "
#define LOG(x...) deb << imie(x)
#define DOG(x...) deb << #x ": " << dump(x) << " "

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

inline void foo1() noexcept { cout << "foo1" << endl; }
inline void foo2() noexcept { cout << "foo2" << endl; }
inline void foo3() noexcept { cout << "foo3" << endl; }
inline void foo4() noexcept { cout << "foo4" << endl; }
inline void foo5() noexcept { cout << "foo5" << endl; }
inline void foo6() noexcept { cout << "foo6" << endl; }

inline auto get_foo() noexcept {
	switch (rand() % 6) {
		case 0: return foo1;
		case 1: return foo2;
		case 2: return foo3;
		case 3: return foo4;
		case 4: return foo5;
		case 5: return foo6;
	}

	return foo1;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	vector<void(*)()> u;
	vector<function<void()>> v;
	map<int, void(*)()> l;
	map<int, function<void()>> m;

	constexpr int N = 300;
	auto fillu = [&] {
		u = {};
		u.resize(N);
		REP (i, N)
			u[i] = get_foo();
	};

	auto fillv = [&] {
		v = {};
		v.resize(N);
		REP (i, N)
			v[i] = get_foo();
	};

	auto filll = [&] {
		l = {};
		REP (i, N)
			l[i] = get_foo();
	};

	auto fillm = [&] {
		m = {};
		REP (i, N)
			m[i] = get_foo();
	};

	auto useu = [&] {
		REP (i, N / 3) {
			int k = rand() % N;
			if (k < N) // Real life check
				u[k]();
		}
	};

	auto usev = [&] {
		REP (i, N / 3) {
			int k = rand() % N;
			if (k < N) // Real life check
				v[k]();
		}
	};

	auto usel = [&] {
		REP (i, N / 3)
			l[rand() % N]();
	};

	auto usem = [&] {
		REP (i, N / 3)
			m[rand() % N]();
	};

	auto useif = [&] {
		static_assert(N <= 300, "");
		REP (i, N / 3)
			switch (rand() % N) {
				case 0: foo4(); break;
				case 1: foo4(); break;
				case 2: foo6(); break;
				case 3: foo6(); break;
				case 4: foo1(); break;
				case 5: foo2(); break;
				case 6: foo5(); break;
				case 7: foo1(); break;
				case 8: foo4(); break;
				case 9: foo4(); break;
				case 10: foo5(); break;
				case 11: foo6(); break;
				case 12: foo2(); break;
				case 13: foo4(); break;
				case 14: foo5(); break;
				case 15: foo6(); break;
				case 16: foo6(); break;
				case 17: foo2(); break;
				case 18: foo2(); break;
				case 19: foo6(); break;
				case 20: foo1(); break;
				case 21: foo4(); break;
				case 22: foo4(); break;
				case 23: foo1(); break;
				case 24: foo2(); break;
				case 25: foo5(); break;
				case 26: foo6(); break;
				case 27: foo5(); break;
				case 28: foo4(); break;
				case 29: foo6(); break;
				case 30: foo1(); break;
				case 31: foo3(); break;
				case 32: foo2(); break;
				case 33: foo3(); break;
				case 34: foo3(); break;
				case 35: foo4(); break;
				case 36: foo1(); break;
				case 37: foo5(); break;
				case 38: foo3(); break;
				case 39: foo3(); break;
				case 40: foo1(); break;
				case 41: foo5(); break;
				case 42: foo4(); break;
				case 43: foo5(); break;
				case 44: foo4(); break;
				case 45: foo2(); break;
				case 46: foo5(); break;
				case 47: foo5(); break;
				case 48: foo3(); break;
				case 49: foo5(); break;
				case 50: foo5(); break;
				case 51: foo3(); break;
				case 52: foo2(); break;
				case 53: foo2(); break;
				case 54: foo2(); break;
				case 55: foo6(); break;
				case 56: foo6(); break;
				case 57: foo6(); break;
				case 58: foo6(); break;
				case 59: foo5(); break;
				case 60: foo1(); break;
				case 61: foo4(); break;
				case 62: foo2(); break;
				case 63: foo1(); break;
				case 64: foo6(); break;
				case 65: foo2(); break;
				case 66: foo2(); break;
				case 67: foo5(); break;
				case 68: foo1(); break;
				case 69: foo2(); break;
				case 70: foo4(); break;
				case 71: foo5(); break;
				case 72: foo5(); break;
				case 73: foo2(); break;
				case 74: foo3(); break;
				case 75: foo3(); break;
				case 76: foo5(); break;
				case 77: foo2(); break;
				case 78: foo6(); break;
				case 79: foo4(); break;
				case 80: foo2(); break;
				case 81: foo4(); break;
				case 82: foo3(); break;
				case 83: foo5(); break;
				case 84: foo5(); break;
				case 85: foo6(); break;
				case 86: foo2(); break;
				case 87: foo1(); break;
				case 88: foo6(); break;
				case 89: foo5(); break;
				case 90: foo5(); break;
				case 91: foo3(); break;
				case 92: foo2(); break;
				case 93: foo2(); break;
				case 94: foo3(); break;
				case 95: foo3(); break;
				case 96: foo5(); break;
				case 97: foo3(); break;
				case 98: foo6(); break;
				case 99: foo6(); break;
				case 100: foo5(); break;
				case 101: foo3(); break;
				case 102: foo2(); break;
				case 103: foo4(); break;
				case 104: foo5(); break;
				case 105: foo5(); break;
				case 106: foo2(); break;
				case 107: foo5(); break;
				case 108: foo5(); break;
				case 109: foo4(); break;
				case 110: foo1(); break;
				case 111: foo4(); break;
				case 112: foo5(); break;
				case 113: foo4(); break;
				case 114: foo5(); break;
				case 115: foo1(); break;
				case 116: foo6(); break;
				case 117: foo5(); break;
				case 118: foo2(); break;
				case 119: foo2(); break;
				case 120: foo4(); break;
				case 121: foo2(); break;
				case 122: foo5(); break;
				case 123: foo3(); break;
				case 124: foo5(); break;
				case 125: foo2(); break;
				case 126: foo6(); break;
				case 127: foo1(); break;
				case 128: foo1(); break;
				case 129: foo5(); break;
				case 130: foo5(); break;
				case 131: foo4(); break;
				case 132: foo6(); break;
				case 133: foo5(); break;
				case 134: foo6(); break;
				case 135: foo1(); break;
				case 136: foo5(); break;
				case 137: foo2(); break;
				case 138: foo2(); break;
				case 139: foo2(); break;
				case 140: foo1(); break;
				case 141: foo4(); break;
				case 142: foo6(); break;
				case 143: foo4(); break;
				case 144: foo5(); break;
				case 145: foo1(); break;
				case 146: foo4(); break;
				case 147: foo5(); break;
				case 148: foo2(); break;
				case 149: foo5(); break;
				case 150: foo1(); break;
				case 151: foo5(); break;
				case 152: foo4(); break;
				case 153: foo4(); break;
				case 154: foo4(); break;
				case 155: foo3(); break;
				case 156: foo3(); break;
				case 157: foo6(); break;
				case 158: foo6(); break;
				case 159: foo4(); break;
				case 160: foo2(); break;
				case 161: foo5(); break;
				case 162: foo4(); break;
				case 163: foo6(); break;
				case 164: foo6(); break;
				case 165: foo6(); break;
				case 166: foo6(); break;
				case 167: foo1(); break;
				case 168: foo1(); break;
				case 169: foo5(); break;
				case 170: foo1(); break;
				case 171: foo1(); break;
				case 172: foo3(); break;
				case 173: foo6(); break;
				case 174: foo2(); break;
				case 175: foo3(); break;
				case 176: foo6(); break;
				case 177: foo2(); break;
				case 178: foo3(); break;
				case 179: foo5(); break;
				case 180: foo4(); break;
				case 181: foo6(); break;
				case 182: foo1(); break;
				case 183: foo3(); break;
				case 184: foo5(); break;
				case 185: foo2(); break;
				case 186: foo6(); break;
				case 187: foo1(); break;
				case 188: foo1(); break;
				case 189: foo6(); break;
				case 190: foo5(); break;
				case 191: foo6(); break;
				case 192: foo1(); break;
				case 193: foo1(); break;
				case 194: foo5(); break;
				case 195: foo1(); break;
				case 196: foo3(); break;
				case 197: foo3(); break;
				case 198: foo2(); break;
				case 199: foo5(); break;
				case 200: foo5(); break;
				case 201: foo3(); break;
				case 202: foo5(); break;
				case 203: foo2(); break;
				case 204: foo5(); break;
				case 205: foo4(); break;
				case 206: foo5(); break;
				case 207: foo3(); break;
				case 208: foo6(); break;
				case 209: foo6(); break;
				case 210: foo2(); break;
				case 211: foo5(); break;
				case 212: foo1(); break;
				case 213: foo5(); break;
				case 214: foo4(); break;
				case 215: foo3(); break;
				case 216: foo6(); break;
				case 217: foo4(); break;
				case 218: foo5(); break;
				case 219: foo4(); break;
				case 220: foo1(); break;
				case 221: foo5(); break;
				case 222: foo2(); break;
				case 223: foo3(); break;
				case 224: foo5(); break;
				case 225: foo1(); break;
				case 226: foo4(); break;
				case 227: foo2(); break;
				case 228: foo5(); break;
				case 229: foo5(); break;
				case 230: foo5(); break;
				case 231: foo3(); break;
				case 232: foo2(); break;
				case 233: foo1(); break;
				case 234: foo3(); break;
				case 235: foo3(); break;
				case 236: foo1(); break;
				case 237: foo2(); break;
				case 238: foo6(); break;
				case 239: foo6(); break;
				case 240: foo5(); break;
				case 241: foo3(); break;
				case 242: foo6(); break;
				case 243: foo6(); break;
				case 244: foo4(); break;
				case 245: foo2(); break;
				case 246: foo1(); break;
				case 247: foo4(); break;
				case 248: foo3(); break;
				case 249: foo6(); break;
				case 250: foo4(); break;
				case 251: foo6(); break;
				case 252: foo1(); break;
				case 253: foo6(); break;
				case 254: foo4(); break;
				case 255: foo5(); break;
				case 256: foo4(); break;
				case 257: foo3(); break;
				case 258: foo6(); break;
				case 259: foo5(); break;
				case 260: foo2(); break;
				case 261: foo1(); break;
				case 262: foo4(); break;
				case 263: foo3(); break;
				case 264: foo2(); break;
				case 265: foo6(); break;
				case 266: foo1(); break;
				case 267: foo1(); break;
				case 268: foo2(); break;
				case 269: foo6(); break;
				case 270: foo1(); break;
				case 271: foo1(); break;
				case 272: foo5(); break;
				case 273: foo5(); break;
				case 274: foo2(); break;
				case 275: foo5(); break;
				case 276: foo5(); break;
				case 277: foo4(); break;
				case 278: foo2(); break;
				case 279: foo2(); break;
				case 280: foo5(); break;
				case 281: foo4(); break;
				case 282: foo3(); break;
				case 283: foo6(); break;
				case 284: foo1(); break;
				case 285: foo2(); break;
				case 286: foo1(); break;
				case 287: foo6(); break;
				case 288: foo2(); break;
				case 289: foo6(); break;
				case 290: foo3(); break;
				case 291: foo6(); break;
				case 292: foo5(); break;
				case 293: foo4(); break;
				case 294: foo4(); break;
				case 295: foo4(); break;
				case 296: foo3(); break;
				case 297: foo4(); break;
				case 298: foo5(); break;
				case 299: foo1(); break;
			default: cerr << "N is too big!" << nl; abort();
			}
	};

	auto benchmark = [](auto func, auto name, size_t iterations = 1) {
		srand(19472974);
		// cerr << "### " << name << " ###\n" << flush;
		Timer tm;
		REP (i, (int)iterations)
			func();

		cerr << "### " << name << ": " << fixed << tm.time() / iterations << " s (" << iterations << " iterations) ###\n" << flush;
	};

	benchmark(fillu, "fill u", 1);
	benchmark(fillv, "fill v", 1);
	benchmark(filll, "fill l", 1);
	benchmark(fillm, "fill m", 1);
	cerr << nl;
	benchmark(fillu, "fill u", 100);
	benchmark(fillv, "fill v", 100);
	benchmark(filll, "fill l", 100);
	benchmark(fillm, "fill m", 100);
	cerr << nl;
	benchmark(useu, "use u", 10);
	benchmark(usev, "use v", 10);
	benchmark(usel, "use l", 10);
	benchmark(usem, "use m", 10);
	benchmark(useif, "use if", 10);
	cerr << nl;
	benchmark(useu, "use u", 1);
	benchmark(usev, "use v", 1);
	benchmark(usel, "use l", 1);
	benchmark(usem, "use m", 1);
	benchmark(useif, "use if", 1);
	cerr << nl;
	benchmark(useu, "use u", 10000);
	benchmark(usev, "use v", 10000);
	benchmark(usel, "use l", 10000);
	benchmark(usem, "use m", 10000);
	benchmark(useif, "use if", 10000);

	return 0;
}
