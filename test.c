#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void signal_handler(int signum, siginfo_t *si, void *context)
{
	(void)context;

  printf("Received signal %d, value = %d\n", signum, *(int *)si->si_value.sival_ptr);
  *(int *)si->si_value.sival_ptr = !*(int *)si->si_value.sival_ptr;
  printf("Changed value to %d\n", *(int *)si->si_value.sival_ptr);
}

int main() {
  struct sigaction sa;
  sa.sa_sigaction = signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_SIGINFO;
  sigaction(SIGINT, &sa, NULL);

  //int bool_var = 1;
  static signal handler change variable segmentation faultint *bool_var;

  bool_var = malloc(sizeof(int));
  *bool_var = 1;

  union sigval value;
  value.sival_ptr = bool_var;
  sigqueue(getpid(), SIGINT, value);

  // Wait for a signal
  pause();

  return 0;
}

