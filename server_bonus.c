#include "minitalk.h"

// void update_vars(){}

void process_message(int sig, siginfo_t *info, void *context)
{
    static int size_i = 32;
    static int size = 0;
    static int index = 8;
    static unsigned char res = 0x00;
    static unsigned char *str = NULL;
    static int str_i = 0;

    (void)context;
    kill(info->si_pid, sig);
    ft_printf("Client pid: %d\n", info->si_pid);
    if (--size_i >= 0)
    {
        if (sig == SIGUSR2) // 1
            size |= 1 << size_i;
    }
    if (size_i == -1 && !str)
    {
        str = malloc(size + 1);
        if (!str)
        {
            ft_printf("Error allocating memory\n");
            exit(EXIT_FAILURE);
        }
        str[size] = '\0';
    }
    if (size_i < -1)
    {
        index--;
        if (sig == SIGUSR2) // 1
            res |= 1 << index;

        if (index == 0)
        {
            if (str_i < size)
                str[str_i] = res;
            str_i++;
            if (res == '\0')
            {
                ft_printf("%s\n", str);
                free(str);
                str = NULL;
                str_i = 0;
                size_i = 32;
                size = 0;
            }
            index = 8;
            res = 0x00;
        }
    }
}

int main()
{
    // Handle errors for when some arguments are passed
    int pid;
    struct sigaction action;

    pid = getpid();
    ft_printf("PID: %d\n", pid);
    action.sa_sigaction = process_message;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
        pause();
    return (0);
}
