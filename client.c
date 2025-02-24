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

    i = 0;
    while (i++ < 8)
    {
        send_signal(pid, 0);
        usleep(42);
    }
}

int is_numeric(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return 0;
        i++;
    }
    return 1;
}

int main(int ac, char **av)
{
    int pid;

    if (ac == 3)
    {
        pid = ft_atoi(av[1]);
        if (!is_numeric(av[1]) || pid <= 0)
        {
            ft_printf("PID should be a positive number!\n");
            return 1;
        }
        if (pid <= 0)
            split_send(pid, av[2]);
    }
    else
        ft_printf("Too much or too few arguments.\n Enter arguments in following order: ./client <PID> <MESSAGE>");
    return 0;
}
