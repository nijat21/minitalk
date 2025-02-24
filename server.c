#include "minitalk.h"

// Reassemble bits into a byte and print every byte
void sig_handler(int sig)
{
    static int index = 8;
    static unsigned char res = 0x00;

    index--;
    if (sig == SIGUSR2) // 0
        res = ((res >> index) | 1) << index;

    if (index == 0)
    {
        ft_printf("%c", res);
        if (res == '\0')
            write(1, "\n", 1);
        index = 8;
        res = 0x00;
    }
}

// struct sigaction {
//     void (*sa_handler)(int);
//     void (*sa_sigaction)(int, siginfo_t *, void *);
//     sigset_t sa_mask;
//     int sa_flags;
//     void (*sa_restorer)(void);
// }
int main()
{
    int pid;
    struct sigaction action;

    pid = getpid();
    ft_printf("PID: %d\n", pid);
    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    if (sigaction(SIGUSR1, &action, NULL) == -1)
    {
        ft_printf("Failed to read SIGUSR1");
        exit(EXIT_FAILURE);
    }
    if (sigaction(SIGUSR2, &action, NULL) == -1)
    {
        ft_printf("Failed to read SIGUSR2");
        exit(EXIT_FAILURE);
    }
    while (1)
        pause();
    return (0);
}
