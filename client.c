#include "minitalk.h"

// Send signal to server

// int kill(pid_t pid, int sig);
// pid > 0 -> send
// I no pid match -> errno = ESRCH
// If permission failure | uid mismatch -> errno = EPERM

void send_signal(int pid, int bit)
{
    ft_printf("BIT %i\n", bit);
    if (bit == 0)
    {
        if (kill(pid, SIGUSR1) == -1)
        {
            ft_printf("Error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (kill(pid, SIGUSR2) == -1)
        {
            ft_printf("Error %d\n", errno);
            exit(EXIT_FAILURE);
        }
    }
}

void split_send(int pid, char *str)
{
    char ch;
    int temp;
    int i;

    while (*str)
    {
        i = 7;
        while (i >= 0)
        {
            ch = *str;
            temp = (ch >> i) & 1;
            usleep(42);
            // ft_printf("temp %d\n", temp);
            send_signal(pid, temp);
            i--;
        }
        str++;
    }
}

int main(int ac, char **av)
{
    if (ac == 3)
    {
        split_send(ft_atoi(av[1]), av[2]);
    }
    // return 0;
}
