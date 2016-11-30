// Krzysztof Małysa
// Speed test of memory copying functions
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
} input;


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

#ifdef DEBUG
# define D(...) __VA_ARGS__
# define E(...) eprintf(__VA_ARGS__)
# define OUT(a,b) cerr << #a ":", __out(cerr, a, b), E("\n")
# define LOG(x) cerr << #x ": " << x
# define LOG2(x, y) cerr << x ": " << y
# define LOGN(x) cerr << #x ": " << x << endl
# define LOGN2(x, y) cerr << x ": " << y << endl
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
	string a(NULL);
	cout << a << endl;

	srand(10101029);

	const int LEN = 10e3 + 1, OPER = 1e6;
	printf("LEN: %i\n", LEN);
	printf("OPER: %i\n", OPER);
	char t[LEN];
	char t2[LEN];
	// Fill t
	REP (i, LEN - 1)
		t[i] = rand() % 26 + 'a';
	t[LEN - 1] = '\0';

	// Benchmark
	Timer timer;
/*
	// iterate
	timer.start();
	REP (i, OPER) {
		t2 = new char[LEN];
		REP (j, LEN)
			t2[j] = t[j];
		free(t2);
	}
	printf("iterate: %4.4f s\n", timer.time());*/

	// memcpy
	timer.start();
	REP (i, OPER) {
		// t2 = new char[LEN];
		memcpy(t2, t, LEN);
		// free(t2);
	}
	printf("memcpy(): %4.4f s\n", timer.time());

	// strlen + memcpy
	timer.start();
	REP (i, OPER) {
		// t2 = new char[LEN];
		memcpy(t2, t, strlen(t));
		// free(t2);
	}
	printf("strlen() + memcpy(): %4.4f s\n", timer.time());

	// strcpy
	timer.start();
	REP (i, OPER) {
		// t2 = new char[LEN];
		strcpy(t2, t);
		// free(t2);
	}
	printf("strcpy(): %4.4f s\n", timer.time());

	// strncpy
	timer.start();
	REP (i, OPER) {
		// t2 = new char[LEN];
		strncpy(t2, t, LEN);
		// free(t2);
	}
	printf("strncpy(): %4.4f s\n", timer.time());

	// strdup
	char *res = NULL;
	timer.start();
	REP (i, OPER) {
		res = strdup(t);
		free(res);
	}
	printf("strdup(): %4.4f s\n", timer.time());

	// strndup
	res = NULL;
	timer.start();
	REP (i, OPER) {
		res = strndup(t, LEN);
		free(res);
	}
	printf("strndup(): %4.4f s\n", timer.time());
	return 0;
}
