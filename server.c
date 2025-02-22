#include "minitalk.h"

// Wait for signal
int main()
{
    int pid = getpid();

    ft_printf("%d\n", pid);
}