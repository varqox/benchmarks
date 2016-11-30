// Krzysztof Małysa
// Interprocess communication speed test: pipe, shared memory + semaphores, sockets
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

CL Input {
	static const int BUFF_SIZE = 1 << 16;
	const int fd;
	unsigned char buff[BUFF_SIZE], *pos, *end;

	void grabBuffer() { end = (pos = buff) + read(fd, buff, BUFF_SIZE); }

public:
	explicit Input(int x) : fd(x), pos(buff), end(buff) {}

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
#define OUT(a,b) D(cerr << #a ":", __out(cerr, a, b), E("\n"))
#define DUMP(x) D(cerr << #x ":", __dump(cerr, ALL(x)), E("\n"))
#define LOG(x) D(cerr << #x ": " << (x))
#define LOG2(x, y) D(cerr << x << ": " << (y))
#define LOGN(x) D(LOG(x) << endl)
#define LOGN2(x, y) D(LOG2(x, y) << endl)
/// End of templates

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

#include <sys/shm.h>
#include <sys/stat.h>

class SharedMemorySegment {
private:
	int id_;
	void* addr_;
	SharedMemorySegment(const SharedMemorySegment&);
	SharedMemorySegment& operator=(const SharedMemorySegment&);

public:
	SharedMemorySegment(size_t size) : id_(shmget(IPC_PRIVATE, size,
				IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR)),
			addr_(nullptr) {

		if (id_ != -1) {
			if ((addr_ = shmat(id_, nullptr, 0)) == (void*)-1)
				addr_ = nullptr;
			shmctl(id_, IPC_RMID, nullptr);
		}
	}

	~SharedMemorySegment() {
		if (addr_)
			shmdt(addr_);
	}

	int key() const { return id_; }

	void* addr() const { return addr_; }
};

double testPipe(long long data_length) {
	constexpr int BUFF_SIZE = (1 << 12) - 1;
	char buff[BUFF_SIZE];
	int fd[2];
	pipe(fd);

	int cpid = fork();
	if (cpid == -1)
		abort();

	else if (cpid == 0) {
		long long x;
		memset(buff, '7', BUFF_SIZE);

		while (data_length && (x = write(fd[1], buff, std::min<LL>(BUFF_SIZE, data_length))) >= 0)
			data_length -= x;

		_exit(0);
	}

	Stopwatch sw;
	long long got = 0, x;
	while (got < data_length && (x = read(fd[0], buff, std::min<LL>(data_length - got, BUFF_SIZE))) >= 0)
		got += x;

	if (got < data_length)
		return -1;

	return sw.time();
}

union semun {
	int              val;    /* Value for SETVAL */
	struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
	unsigned short  *array;  /* Array for GETALL, SETALL */
	struct seminfo  *__buf;  /* Buffer for IPC_INFO
	                               (Linux-specific) */
};

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

/* Obtain a binary semaphore’s ID, allocating if necessary. */
int binary_semaphore_allocation(key_t key, int sem_flags) {
	return semget(key, 1, sem_flags);
}

/* Deallocate a binary semaphore. All users must have finished their
use. Returns -1 on failure. */
int binary_semaphore_deallocate(int semid) {
	union semun ignored_argument;
	return semctl(semid, 1, IPC_RMID, ignored_argument);
}

/* Initialize a binary semaphore with a value of 1. */
int binary_semaphore_initialize(int semid, int x = 1) {
	union semun argument;
	unsigned short values[1];
	values[0] = x;
	argument.array = values;
	return semctl(semid, 0, SETALL, argument);
}

/* Wait on a binary semaphore. Block until the semaphore value is positive, then
decrement it by 1. */
int binary_semaphore_wait(int semid) {
	struct sembuf operations[1];
	/* Use the first (and only) semaphore. */
	operations[0].sem_num = 0;
	/* Decrement by 1. */
	operations[0].sem_op = -1;
	/* Permit undoing. */
	operations[0].sem_flg = SEM_UNDO;
	return semop(semid, operations, 1);
}

/* Post to a binary semaphore: increment its value by 1.
This returns immediately. */
int binary_semaphore_post(int semid) {
	struct sembuf operations[1];
	/* Use the first (and only) semaphore. */
	operations[0].sem_num = 0;
	/* Increment by 1. */
	operations[0].sem_op = 1;
	/* Permit undoing. */
	operations[0].sem_flg = SEM_UNDO;
	return semop(semid, operations, 1);
}

/* Post to a binary semaphore: increment its value by 1.
This returns immediately. */
int binary_semaphore_oper(int semid, int x) {
	struct sembuf operations[1];
	/* Use the first (and only) semaphore. */
	operations[0].sem_num = 0;
	/* Increment by 1. */
	operations[0].sem_op = x;
	/* Permit undoing. */
	operations[0].sem_flg = 0;
	return semop(semid, operations, 1);
}

double testSharedMemory(long long data_length) {
	constexpr int BUFF_SIZE = 1 << 16;

	struct xxx {
		int size;
		char buff[BUFF_SIZE];
	};

	SharedMemorySegment sms(sizeof(xxx));
	char buff[BUFF_SIZE];
	memset(sms.addr(), 0, sizeof(xxx));

	int sem = binary_semaphore_allocation(IPC_PRIVATE, IPC_CREAT | S_IRWXU);
	// if (sem < 0)
	// 	eprintf("Error: semget() - %s\n", strerror(errno));
	binary_semaphore_initialize(sem, 0);

	int cpid = fork();
	if (cpid == -1)
		abort();
	else if (cpid == 0) {
		memset(buff, '7', BUFF_SIZE);
		xxx *x = (xxx*)sms.addr();

		while (data_length) {
			x->size = std::min<LL>(data_length, BUFF_SIZE);
			// copy(buff, buff+BUFF_SIZE, x->buff);
			memcpy(x->buff, buff, x->size);
			data_length -= x->size;
			binary_semaphore_oper(sem, 1);
			binary_semaphore_oper(sem, -2);
		}
		x->size = BUFF_SIZE-1;

		(void)binary_semaphore_deallocate(sem);
		_exit(0);
	}

	// binary_semaphore_initialize(sem, 2);
	Stopwatch sw;
	long long got = 0;
	xxx *x = (xxx*)sms.addr();
	while (got < data_length) {
		binary_semaphore_oper(sem, -1);
		if (x->size <= 0) {
			cerr << "x->size: error!\n";
			break;
		}
		memcpy(buff, x->buff, x->size);
		got += x->size;
		// cerr << x->size << endl;
		binary_semaphore_oper(sem, 2);
	}

	(void)binary_semaphore_deallocate(sem);

	if (got < data_length)
		return -1;

	return sw.time();
}

#include <sys/socket.h>
#include <sys/un.h>

double testSocket(long long data_length) {
	constexpr int BUFF_SIZE = 1 << 16;
	char buff[BUFF_SIZE];

	int fd[2];
	if (socketpair(AF_LOCAL, SOCK_STREAM, 0, fd))
		return -1;

	int cpid = fork();
	if (cpid == -1)
		abort();

	else if (cpid == 0) {
		long long x;
		memset(buff, '7', BUFF_SIZE);

		while (data_length &&
				(x = write(fd[1], buff, std::min<LL>(BUFF_SIZE, data_length))) >= 0)
			data_length -= x;

		_exit(0);
	}

	Stopwatch sw;
	long long got = 0, x;
	while (got < data_length &&
			(x = read(fd[0], buff, std::min<LL>(data_length - got, BUFF_SIZE))) >= 0)
		got += x;

	close(fd[0]);
	close(fd[1]);

	if (got < data_length)
		return -1;

	return sw.time();
}

int main(int argc, char **argv) {
	long long bytes = 1LL << 30;
	if (argc > 1)
		bytes = atoll(argv[1]);

	double tm = testPipe(bytes);
	cout << "Pipe: " << bytes << " bytes in " << tm << " s\n"
		<< "Speed: " << fixed << setprecision(4) << bytes / tm / (1 << 30) << " GB/s\n";

	tm = testSharedMemory(bytes);
	cout << "SHM: " << bytes << " bytes in " << tm << " s\n"
		<< "Speed: " << fixed << setprecision(4) << bytes / tm / (1 << 30) << " GB/s\n";

	tm = testSocket(bytes);
	cout << "Socket: " << bytes << " bytes in " << tm << " s\n"
		<< "Speed: " << fixed << setprecision(4) << bytes / tm / (1 << 30) << " GB/s\n";
	return 0;
}
