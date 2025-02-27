#include "minitalk.h"

// Send signal to server
void split_to_bits(int pid, int ch, int bit_count)
{
    int bit;
    bit_count--;
    while (bit_count >= 0)
    {
        bit = (ch >> bit_count) & 1;
        ft_printf("bit %d\n", bit);
        if (bit == 0)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        bit_count--;
        usleep(200);
    }
}

// First send length of the message
// Send the message
// Send the null terminator
void split_send(int pid, char *str)
{
    int i;
    int len;

    len = ft_strlen(str);
    split_to_bits(pid, len, 32);
    while (*str)
    {
        split_to_bits(pid, *str, 8);
        str++;
    }
    i = 0;
    while (i++ < 8)
    {
        kill(pid, SIGUSR1);
        usleep(200);
    }
}

// void sig_handle(int sig)
// {
//     int temp = 0;

//     if (sig == SIGUSR2)
//         temp = 1;
//     ft_printf("Bit received %d\n", temp);
// }

// void receive_ack(void)
// {
//     struct sigaction ack;

//     ack.sa_handler = sig_handle;
//     sigemptyset(&ack.sa_mask);
//     ack.sa_flags = 0;
//     sigaction(SIGUSR1, &ack, NULL);
//     sigaction(SIGUSR2, &ack, NULL);
// }

int main(int ac, char **av)
{
    int pid;

    ft_printf("Pid check: %d\n", getpid());
    if (ac == 3)
    {
        pid = ft_atoi(av[1]);
        if (!pid)
        {
            ft_printf("PID should be a positive number!\n");
            return 1;
        }
        else
            split_send(pid, av[2]);
    }
    else
        ft_printf("Too much or too few arguments.\n Enter arguments in following order: ./client <PID> <MESSAGE>");
    return 0;
}
