#include "minitalk.h"

// Send signal to server

// int kill(pid_t pid, int sig);
// pid > 0 -> send
// I no pid match -> errno = ESRCH
// If permission failure | uid mismatch -> errno = EPERM
