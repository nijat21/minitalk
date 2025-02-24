#include "minitalk.h"

// For communication between handler and main
// static volatile sig_atomic_t signal_bit = 0;
// static volatile sig_atomic_t signal_received = 0;

// void sig_handler(int sig)
// {
//     signal_bit = (sig == SIGUSR2) ? 1 : 0;
//     signal_received = 1;
// }

void process_message(int sig)
{
    static int count = 0;
    static int size_i = 32;
    static int size = 0;
    static int index = 8;
    static unsigned char res = 0x00;
    static unsigned char *str = NULL;
    static int str_i = 0;

    if (count <= 32)
    {
        size_i--;
        if (sig == SIGUSR2) // 1
            size |= 1 << size_i;

        count++;
    }
    if (!str)
        str = malloc(size + 1);
    if (count > 32)
    {
        index--;
        if (sig == SIGUSR2) // 1
            res |= 1 << index;

        if (index == 0)
        {
            str[str_i] = res;
            str_i++;
            if (res == '\0')
            {
                ft_printf("%s\n", str);
                free(str);
                str = NULL;
                str_i = 0;
                count = 0;
                size_i = 32;
            }
            index = 8;
            res = 0x00;
        }
    }
}

void receive_sigs(void)
{
    int pid;
    struct sigaction action;

    pid = getpid();
    ft_printf("PID: %d\n", pid);
    action.sa_handler = process_message;
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
}

int main()
{
    // Handle errors for when some arguments are passed
    receive_sigs();
    return (0);
}
