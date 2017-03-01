#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

static void basic_daemon() {
	pid_t pid;

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	if (setsid() < 0) {
		exit(EXIT_FAILURE);
	}

	signal(SIGCHLD, SIG_IGN); // ignore child --> parent
	signal(SIGHUP, SIG_IGN); // ignore controlling terminal closing

	pid = fork();

	if (pid < 0) {
		exit(EXIT_FAILURE);
	}

	if (pid > 0) {
		exit(EXIT_SUCCESS);
	}

	umask(0);

	chdir("/");

	int x;

	for (x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
		close(x);
	}

	openlog("weatherdaemon", LOG_PID, LOG_DAEMON);
}

int main() {
	basic_daemon();

	while (1) {
		syslog(LOG_NOTICE, "Weather daemon started");
		sleep(20);
		break;
	}

	syslog(LOG_NOTICE, "Weather daemon stopped");
}












