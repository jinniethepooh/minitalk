/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchetana <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:12:26 by cchetana          #+#    #+#             */
/*   Updated: 2022/06/25 14:12:49 by cchetana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

static void	error_msg(int code)
{
	write(1, "[ERROR: Client] ", 16);
	if (code == 1)
	{
		write(1, "invalid arguments ", 18);
		write(1, "[./client <server_pid> <msg>]\n", 30);
	}
	else if (code == 2)
		write(1, "invalid PID\n", 12);
	else if (code == 3)
		write(1, "Error on sending signal\n", 24);
	exit (EXIT_FAILURE);
}

static int	ft_atoi(char *s)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (s[i] && ((9 <= s[i] && s[i] <= 13) || s[i] == 32))
		i++;
	while (s[i] && ('0' <= s[i] && s[i] <= '9'))
	{
		nbr = (nbr * 10) + (s[i] - '0');
		i++;
	}
	if (s[i] != '\0')
		return (0);
	return (nbr);
}

static void	respond_sig(int signum, siginfo_t *info, void *context)
{
	(void) context;
	(void) info;
	if (signum == SIGUSR1)
		write(1, "Message successfully sent!\n", 27);
	exit (EXIT_SUCCESS);
}

static void	send_sig(unsigned char c, int pid)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (c % 2)
		{
			if (kill(pid, SIGUSR2) == -1)
				error_msg(3);
		}
		else
		{
			if (kill(pid, SIGUSR1) == -1)
				error_msg(3);
		}
		c /= 2;
		i++;
		usleep(100);
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sact;
	int					i;

	if (argc != 3)
		error_msg(1);
	if (!argv[1] || ft_atoi(argv[1]) <= 0)
		error_msg(2);
	sigemptyset(&sact.sa_mask);
	sact.sa_sigaction = &respond_sig;
	sact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sact, NULL);
	i = -1;
	while (argv[2][++i])
		send_sig(argv[2][i], ft_atoi(argv[1]));
	send_sig(argv[2][i], ft_atoi(argv[1]));
	while (1)
		pause();
	return (0);
}
