#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

volatile sig_atomic_t	g_timeout;
pid_t	g_pid;

void	reset_signals(struct sigaction *sa_default)
{
	sigaction(SIGTERM, sa_default, NULL);
	sigaction(SIGQUIT, sa_default, NULL);
	sigaction(SIGINT, sa_default, NULL);
	sigaction(SIGALRM, sa_default, NULL);
}

void	alarm_handler(int signal)
{
	if (signal == SIGALRM)
	{
		g_timeout = 1;
		if (g_pid > 0)
			kill(g_pid, SIGKILL);
	}
}
int	sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
	struct sigaction	sa_default;
	struct sigaction	sa_ignore;
	struct sigaction	sa_alarm;
	int	code;
	int status;

	sigemptyset(&sa_default.sa_mask);
	sa_default.sa_flags = SA_RESTART;
	sa_default.sa_handler = SIG_DFL;
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_flags = SA_RESTART;
	sa_ignore.sa_handler = SIG_IGN;
	sigemptyset(&sa_alarm.sa_mask);
	sa_alarm.sa_flags = SA_RESTART;
	sa_alarm.sa_handler = alarm_handler;

	if (sigaction(SIGTERM, &sa_ignore, NULL) < 0
	||	sigaction(SIGINT, &sa_ignore, NULL) < 0
	||	sigaction(SIGQUIT, &sa_ignore, NULL) < 0)
		return (reset_signals(&sa_default), 1);
	g_pid = fork();
	if (g_pid < 0)
		return (reset_signals(&sa_default), 1);
	if (g_pid == 0)
	{
		if (sigaction(SIGTERM, &sa_default, NULL) < 0
		||	sigaction(SIGQUIT, &sa_default, NULL) < 0
		|| 	sigaction(SIGINT, &sa_default, NULL) < 0)
			exit(1);
		(*f)();
		exit(0);
	}
	g_timeout = 0;
	if(sigaction(SIGALRM, &sa_alarm, NULL) < 0)
		return (reset_signals(&sa_default), 1);
	alarm(timeout);
	if (waitpid(g_pid, &status, 0) < 0)
		return (reset_signals(&sa_default), 1);
	alarm(0);
	if (g_timeout  == 1)
	{
		if (verbose)
			printf("Timeout\n");
		return (reset_signals(&sa_default), 1);
	}
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		if (!code)
		{
			if (verbose)
				printf("Success\n");
			return (reset_signals(&sa_default), 0);
		}
		else
		{
			if (verbose)
				printf("Fail\n");
			return (reset_signals(&sa_default), 1);
		}
	}
	if (WIFSIGNALED(status))
	{
		if (verbose)
			printf("Signal: %s\n", strsignal(WTERMSIG(status)));
		return (reset_signals(&sa_default), 1);
	}
	return (reset_signals(&sa_default), 1);
}

void	case_normal()
{
	exit(0);
}
void	case_bad()
{
	exit(1);
}
void	case_sigsev()
{
	char *a = NULL;
	a[0] = 'a';
}
void	case_timeout()
{
	while (1)
	{
		printf("child running\n");
		sleep(1);
	}
}
int main(void)
{
	sandbox(&case_normal, 5, 1);
	sandbox(&case_bad, 5, 1);
	sandbox(&case_sigsev, 5, 1);
	sandbox(&case_timeout, 5, 1);
}