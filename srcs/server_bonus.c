/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:13:05 by cchetana          #+#    #+#             */
/*   Updated: 2022/06/25 14:13:20 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	error_msg(void)
{
	write(1, "[ERROR: Server] Error on sending signal\n", 40);
	exit (EXIT_FAILURE);
}

static void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	write(1, &"0123456789"[n % 10], 1);
}

static void	handler_sig(int signum, siginfo_t *info, void *context)
{
	static unsigned char	c = 0;
	static int				bits = 0;

	(void) context;
	if (signum == SIGUSR2)
		c += (1 << bits);
	bits++;
	if (bits == 8)
	{
		write(1, &c, 1);
		bits = 0;
		if (c == 0)
		{
			write(1, "\n", 1);
			if (kill(info->si_pid, SIGUSR1) == -1)
				error_msg();
		}
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sact;
	pid_t				pid;

	pid = getpid();
	write(1, "PID: ", 5);
	ft_putnbr(pid);
	write(1, "\n", 1);
	sigemptyset(&sact.sa_mask);
	sact.sa_sigaction = &handler_sig;
	sact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sact, NULL);
	sigaction(SIGUSR2, &sact, NULL);
	while (1)
		pause();
	return (0);
}
