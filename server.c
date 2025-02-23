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
        ft_printf("%c\n", res);
        index = 8;
        res = 0x00;
    }
}

// Wait for signal
int main()
{
    int pid;
    struct sigaction action;
    // struct sigaction {
    //     void (*sa_handler)(int);
    //     void (*sa_sigaction)(int, siginfo_t *, void *);
    //     sigset_t sa_mask;
    //     int sa_flags;
    //     void (*sa_restorer)(void);
    // }

    // Get PID and print
    pid = getpid();
    ft_printf("%d\n", pid);

    // Create a set to combine all signals
    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    // action.sa_flags = SA_RESTART;

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

    // Keep it active
    while (1)
        pause();

    return (0);
}