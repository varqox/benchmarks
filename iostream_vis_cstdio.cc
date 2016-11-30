// Krzysztof Małysa
// cin + cout vis printf + scanf benchmark
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define FOR(i,a,n) for (int i = (a), __n ## i = n; i <= __n ## i; ++i)
#define REP(i,n) FOR(i,0,n)
#define FORD(i,a,n) for (int i = (a), __n ## i = n; i >= __n ## i; --i)
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) (int(x.size()))
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define ST first
#define ND second
#define MP make_pair
#define PB push_back
#define EB emplace_back
#define O(...) ostream& operator <<(ostream& os, const __VA_ARGS__& x)
#define OO(...) O(__VA_ARGS__) { return __out(os, ALL(x)); }
#define T template
#define CL class

typedef unsigned uint;
typedef long long LL;
typedef unsigned long long ULL;
typedef vector<int> VI;
typedef vector<VI> VVI;
typedef pair<int, int> PII;
typedef vector<PII> VPII;
typedef pair<LL, LL> PLL;

T<CL A> inline A abs(const A& a) { return a < A() ? -a : a; }
T<CL A, CL B> inline void mini(A& a, const B& b) { if (b < a) a = b; }
T<CL A, CL B> inline void maxi(A& a, const B& b) { if (b > a) a = b; }

T<CL Iter> ostream& __out(ostream& os, Iter a, Iter b, const string& s = ", ");
T<CL A, CL B> O(pair<A, B>);

T<CL A> OO(vector<A>)
T<CL A> OO(deque<A>)
T<CL A> OO(list<A>)
T<CL A, CL B> OO(set<A, B>)
T<CL A, CL B> OO(multiset<A, B>)
T<CL A, CL B, CL C> OO(map<A, B, C>)
T<CL A, CL B, CL C> OO(multimap<A, B, C>)

T<CL Iter> ostream& __out(ostream& os, Iter a, Iter b, const string& s) {
	os << "{";
	if (a != b) {
		os << *a;
		while (++a != b)
			os << s << *a;
	}
	return os << "}";
}

T<CL Iter> ostream& __dump(ostream& os, Iter a, Iter b) {
	os << "{\n";
	Iter beg = a;
	while (a != b) {
		os << " " << a - beg << ": " << *a << "\n";
		++a;
	}
	return os << "}";
}

T<CL A, CL B> O(pair<A, B>) { return os << "(" << x.ST << ", " << x.ND << ")"; }

#undef LIKELY
#undef UNLIKELY

#if defined(__GNUC__) && __GNUC__ >= 4
# define LIKELY(x)   (__builtin_expect((x), 1))
# define UNLIKELY(x) (__builtin_expect((x), 0))
#else
# define LIKELY(x)   (x)
# define UNLIKELY(x) (x)
#endif

CL Input {
	static const int BUFF_SIZE = 1 << 16;
	const int fd;
	unsigned char buff[BUFF_SIZE], *pos, *end;

	void grabBuffer() { end = (pos = buff) + read(fd, buff, BUFF_SIZE); }

public:
	explicit Input(int x) : fd(x), pos(buff), end(buff) {}

	int peek() {
		if (UNLIKELY(pos == end))
			grabBuffer();
		return LIKELY(pos != end) ? *pos : -1;
	}

	int getChar() {
		if (UNLIKELY(pos == end))
			grabBuffer();
		return LIKELY(pos != end) ? *pos++ : -1;
	}

	void skipWhiteSpaces() {
		while (isspace(peek()))
			++pos;
	}

	Input& operator>>(char *s) {
		skipWhiteSpaces();
		while (!isspace(peek()))
			*s++ = *pos++;
		*s = '\0';
		return *this;
	}

	T<CL A>
	Input& operator>>(A& a);
} fin(0);

T<> Input& Input::operator>> <char>(char& x) {
	skipWhiteSpaces();
	x = *pos++;
	return *this;
}

T<> Input& Input::operator>> <uint>(uint& x) {
	skipWhiteSpaces();
	x = 0;
	while (isdigit(peek()))
		x = x * 10 + *pos++ - '0';
	return *this;
}

T<> Input& Input::operator>> <int>(int& x) {
	skipWhiteSpaces();
	if (peek() != '-')
		return operator>> <uint>((uint&)x);
	++pos; operator>> <uint>((uint&)x); x = -x;
	return *this;
}

T<> Input& Input::operator>> <unsigned short>(unsigned short& x) {
	skipWhiteSpaces();
	x = 0;
	while (isdigit(peek()))
		x = x * 10 + *pos++ - '0';
	return *this;
}

T<> Input& Input::operator>> <short>(short& x) {
	skipWhiteSpaces();
	if (peek() != '-')
		return operator>> <unsigned short>((unsigned short&)x);
	++pos; operator>> <unsigned short>((unsigned short&)x); x = -x;
	return *this;
}

T<> Input& Input::operator>> <ULL>(ULL& x) {
	skipWhiteSpaces();
	x = 0;
	while (isdigit(peek()))
		x = x * 10 + *pos++ - '0';
	return *this;
}

T<> Input& Input::operator>> <LL>(LL& x) {
	skipWhiteSpaces();
	if (peek() != '-')
		return operator>> <ULL>((ULL&)x);
	++pos; operator>> <ULL>((ULL&)x); x = -x;
	return *this;
}

T<> Input& Input::operator>> <string>(string& x) {
	skipWhiteSpaces();
	x.clear();
	while (!isspace(peek()))
		x += *pos++;
	return *this;
}

inline int ceil2(int x) { return 1 << (sizeof(x) * 8 -__builtin_clz(x - 1)); }

#undef T
#undef CL
#ifdef DEBUG
# define D(...) __VA_ARGS__
#else
# define D(...)
#endif

#define E(...) D(eprintf(__VA_ARGS__))
#define OUT(a,b) D(cerr << #a ": ", __out(cerr, a, b), E("\n"))
#define DUMP(x) D(cerr << #x ": ", __dump(cerr, ALL(x)), E("\n"))
#define LOG(x) D(cerr << #x ": " << (x))
#define LOG2(x, y) D(cerr << x << ": " << (y))
#define LOGN(x) D(LOG(x) << endl)
#define LOGN2(x, y) D(LOG2(x, y) << endl)
/// End of templates

template<class A, class B>
inline int fastMod(A x, B mod) { return x < mod ? x : x % mod; }

class Stopwatch {
	std::chrono::steady_clock::time_point begin;

public:
	Stopwatch() noexcept { restart(); }

	void restart() noexcept { begin = std::chrono::steady_clock::now(); }

	long long microtime() const noexcept {
		using namespace std::chrono;
		return duration_cast<microseconds>(steady_clock::now() - begin).count();
	}

	double time() const noexcept {
		using namespace std::chrono;
		return duration<double>(steady_clock::now() - begin).count();
	}
};

#include <sys/stat.h>
#include <sys/wait.h>

int getUnlinkedTmpFile(int flags = 0) noexcept {
	int fd;
#ifdef O_TMPFILE
	fd = open("/tmp", O_TMPFILE | O_RDWR | flags, S_0600);
	if (fd != -1)
		return fd;

	if (errno != EINVAL)
		return -1;
#endif

	char name[] = "/tmp/tmp_unlinked_file.XXXXXX";
	umask(077); // Only owner can access this temporary file
	fd = mkostemp(name, flags);
	if (fd == -1)
		return -1;

	(void)unlink(name);
	return fd;
}

inline int sclose(int fd) noexcept {
	while (close(fd) == -1)
		if (errno != EINTR)
			return -1;

	return 0;
}

mt19937 _r_gen(chrono::system_clock::now().time_since_epoch().count());
int getRandom(int a, int b) {
	return uniform_int_distribution<int>(a, b)(_r_gen);
}

#define BENCHMARK(...)

void benchCinInt(int n) {
	int x = 0;
	REP (i, n - 1)
		cin >> x;
	cout << x << endl;
}

void benchFinInt(int n) {
	int x = 0;
	REP (i, n - 1)
		fin >> x;
	cout << x << endl;
}

void benchCinString(int) {
	string s;
	cin >> s;
	cout << s.size() << endl;
}

void benchFinString(int) {
	string s;
	fin >> s;
	cout << s.size() << endl;
}

void benchCinCstring(int n) {
	unique_ptr<char[]> s(new char[n + 1]);
	cin >> s.get();
	cout << strlen(s.get()) << endl;
}

void benchFinCstring(int n) {
	unique_ptr<char[]> s(new char[n + 1]);
	fin >> s.get();
	cout << strlen(s.get()) << endl;
}

void benchScanfInt(int n) {
	int x = 0;
	REP (i, n - 1)
		scanf("%i", &x);
	cout << x << endl;
}

void benchScanfCstring(int n) {
	unique_ptr<char[]> s(new char[n + 1]);
	scanf("%s", s.get());
	cout << strlen(s.get()) << endl;
}

void benchCoutInt(int n) {
	VI t(n);
	for (int& i : t)
		i = _r_gen();
	for (int i : t)
		cout << i << '\n';
	cout << flush;
}

void benchCoutString(int n) {
	string s(n, ' ');
	for (char& c : s)
		c = getRandom('A', 'z');
	cout << s << '\n' << flush;
}

void benchCoutCstring(int n) {
	unique_ptr<char[]> s(new char[n + 1]);
	s[n] = '\0';
	REP (i, n - 1)
		s[i] = getRandom('A', 'z');
	cout << s.get() << '\n' << flush;
}

void benchPrintfInt(int n) {
	VI t(n);
	for (int& i : t)
		i = _r_gen();
	for (int i : t)
		printf("%i\n", i);
}

void benchPrintfCstring(int n) {
	unique_ptr<char[]> s(new char[n + 1]);
	s[n] = '\0';
	REP (i, n - 1)
		s[i] = getRandom('A', 'z');
	printf("%s\n", s.get());
}

template<class Gen, class Func>
void run(Gen gen, Func func, int n, const string& bench_name) {
	int fd = getUnlinkedTmpFile();
	assert(fd != -1);
	FILE *f = fdopen(fd, "rw");
	assert(f);

	gen(f, n);
	lseek(fd, 0, SEEK_SET);

	pid_t pid = fork();
	assert(pid != -1);
	if (pid == 0) {
		dup2(STDOUT_FILENO, STDERR_FILENO);
		dup2(fd, STDIN_FILENO);
		freopen("/tmp/bench-test.txt", "w", stdout);
		Stopwatch st;
		func(n);
		cerr << bench_name << ":\t" << setprecision(6) << fixed << st.time()
			<< endl;
		fflush(stdout);
		_exit(0);
	}

	waitpid(pid, nullptr, 0);

	fclose(f);
}

void genInts(FILE *f, int n) {
	while (n--)
		fprintf(f, "%i\n", (int)_r_gen());
}

void genString(FILE *f, int n) {
	while (n--)
		fputc(getRandom('A', 'z'), f);
	fputc('\n', f);
}

void genNothing(FILE*, int) {}

void benchmark(int n) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << "n: " << n << " (" << (double)n << ")" << endl;

	run(genInts, benchCinInt, n, "cin >> int");
	// run(genInts, benchFinInt, n, "fin >> int");
	run(genInts, benchScanfInt, n, "scanf(int)");
	cout << endl;
	run(genString, benchCinString, n, "cin >> string");
	// run(genString, benchFinString, n, "fin >> string");
	run(genString, benchCinCstring, n, "cin >> char*");
	// run(genString, benchFinCstring, n, "fin >> char*");
	run(genString, benchScanfCstring, n, "scanf(char*)");
	cout << endl;
	run(genNothing, benchCoutInt, n, "cout << int");
	run(genNothing, benchPrintfInt, n, "printf(int)");
	cout << endl;
	run(genNothing, benchCoutString, n, "cout << string");
	run(genNothing, benchCoutCstring, n, "cout << char*");
	run(genNothing, benchPrintfCstring, n, "printf(char*)");
}

int main() {
	constexpr int N = 2e7;
	benchmark(N);
	return 0;
}
