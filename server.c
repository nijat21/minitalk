#include "minitalk.h"

void receive_len(int sig, int *len, int *len_received, char **str)
{
    static int i = 32;
    static int res = 0;

    --i;
    if (sig == SIGUSR2)
        res |= 1 << i;
    if (i == 0)
    {
        *len = res;
        *str = malloc(res + 1);
        (*str)[res] = '\0';
        *len_received = 1;
        i = 32;
        res = 0;
    }
    return;
}

void sig_handler(int sig)
{
    static unsigned char ch = 0;
    static int i = 8;
    static int len_received = 0;
    static int len;
    static char *str = NULL;
    static int str_i = 0;

    if (!len_received)
        receive_len(sig, &len, &len_received, &str);
    else
    {
        --i;
        if (sig == SIGUSR2)
            ch |= 1 << i;
        if (i == 0)
        {
            str[str_i++] = ch;
            if (ch == '\0')
            {
                ft_printf("%s\n", str);
                free(str);
                str = NULL;
                str_i = 0;
                len_received = 0;
                len = 0;
            }
            ch = 0;
            i = 8;
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
    action.sa_handler = sig_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    sigaction(SIGUSR1, &action, NULL);
    sigaction(SIGUSR2, &action, NULL);
    while (1)
        pause();
    return (0);
}