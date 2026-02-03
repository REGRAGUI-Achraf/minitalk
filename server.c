/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aregragu <aregragu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 00:05:35 by aregragu          #+#    #+#             */
/*   Updated: 2025/02/10 01:55:39 by aregragu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	ft_putchar(char c)
{
	write(1, &c, 1);
}

static void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

static void	handle_signal(int sig)
{
	static char	c = 0;
	static int	bits = 0;

	c = c << 1;
	if (sig == SIGUSR1)
		c = c | 1;
	bits++;
	if (bits == 8)
	{
		ft_putchar(c);
		bits = 0;
		c = 0;
	}
}

int	main(void)
{
	write(1, "Server PID: ", 11);
	ft_putnbr(getpid());
	write(1, "\n", 1);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
