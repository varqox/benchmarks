#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void fatal(const char* str) {
	perror(str);
	_exit(1);
}

void child() {
	_exit(getpid() & 4);
}

void run_child() {
	pid_t pid = fork();
	if (pid < 0)
		fatal("fork()");

	if (pid == 0)
		child();

	int status;
	do {
		if (waitpid(pid, &status, 0) < 0)
			fatal("waitpid()");

		// if (WIFEXITED(status))
		// 	printf("exited, status=%d\n", WEXITSTATUS(status));
		// else if (WIFSIGNALED(status))
		// 	printf("killed by signal %d\n", WTERMSIG(status));
		// else if (WIFSTOPPED(status))
		// 	printf("stopped by signal %d\n", WSTOPSIG(status));
		// else if (WIFCONTINUED(status))
		// 	printf("continued\n");
	} while (!WIFEXITED(status) && !WIFSIGNALED(status));
}

int main() {
	for (int i = 0; i < 10000; ++i)
		run_child();

	return 0;
}
