/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregragu <aregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:05:33 by aregragu          #+#    #+#             */
/*   Updated: 2025/02/10 02:38:02 by aregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

void	ft_confirm(int sig)
{
	if (sig == SIGUSR1)
		write(1, "Message sent successfully\n", 27);
}

static void	send_char(int pid, char c)
{
	int	bit;
	int	i;

	i = 8;
	while (i--)
	{
		bit = (c >> i) & 1;
		if (bit == 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(400);
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	if (argc != 3)
	{
		write(1, "CHKATKHRBA9_BONUS\n", 19);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(1, "\n", 1);
		return (1);
	}
	i = 0;
	while (argv[2][i])
		send_char(pid, argv[2][i++]);
	signal(SIGUSR1, ft_confirm);
	send_char(pid, '\0');
	return (0);
}
