#include "minitalk.h"

volatile sig_atomic_t ack_received = 0;

void send_mess(int pid, int ch, int bit_count)
{
    ft_printf("Ack %d\n", ack_received);

    while (--bit_count >= 0 && ack_received)
    {
        ack_received = 0;
        if ((ch >> bit_count & 1) == 1)
            kill(pid, SIGUSR2);
        else
            kill(pid, SIGUSR1);
        usleep(500);
    }
    while (!ack_received)
        pause();
}

int is_numeric(char *str)
{
    while (*str)
    {
        if (!(*str >= '0' && *str <= '9'))
            return 0;
        str++;
    }
    return 1;
}

void sig_handle(int sig)
{
    if (sig == SIGUSR2)
        ft_printf("Bit received 1\n");
    else
        ft_printf("Bit received 0\n");
    ack_received = 1;
}

void receive_ack(void)
{
    struct sigaction ack;

    ack.sa_handler = sig_handle;
    sigemptyset(&ack.sa_mask);
    ack.sa_flags = 0;
    sigaction(SIGUSR1, &ack, NULL);
    sigaction(SIGUSR2, &ack, NULL);
}

int main(int ac, char **av)
{
    int pid;
    int i = 0;
    char *mes;

    if (ac == 3)
    {
        pid = ft_atoi(av[1]);
        if (!pid || !is_numeric(av[1]))
        {
            ft_printf("PID should be an unsigned integer!\n");
            return 1;
        }
        mes = av[2];
        receive_ack();
        send_mess(pid, ft_strlen(av[2]), 32);
        while (mes[i])
            send_mess(pid, mes[i++], 8);
        send_mess(pid, '\0', 8);
    }
    else
        ft_printf("All arguments should be given as: \n./client <PID> <MESSAGE>");
    return 0;
}
