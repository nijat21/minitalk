/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nismayil <nismayil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 15:16:39 by nismayil          #+#    #+#             */
/*   Updated: 2025/03/04 15:18:54 by nismayil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_mess(int pid, int ch, int bit_count)
{
	while (--bit_count >= 0)
	{
		if ((ch >> bit_count & 1) == 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
	}
}

int	is_numeric(char *str)
{
	while (*str)
	{
		if (!(*str >= '0' && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	int		pid;
	int		i;
	char	*mes;

	i = 0;
	if (ac == 3)
	{
		pid = ft_atoi(av[1]);
		if (!pid || !is_numeric(av[1]))
		{
			ft_printf("PID should be an unsigned integer!\n");
			return (1);
		}
		mes = av[2];
		send_mess(pid, ft_strlen(av[2]), 32);
		while (mes[i])
			send_mess(pid, mes[i++], 8);
		send_mess(pid, '\0', 8);
	}
	else
	{
		ft_printf("All arguments should be given as: \n");
		ft_printf("./client <PID> <MESSAGE>");
	}
	return (0);
}
