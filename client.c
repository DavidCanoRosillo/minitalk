/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcano-ro <dcano-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:35:17 by dcano-ro          #+#    #+#             */
/*   Updated: 2022/05/12 20:42:05 by dcano-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	send_signal(int pid, int signal)
{
	kill(pid, signal);
	return (0);
}

static void	send_byte(char byte, int pid, struct sigaction sa)
{
	static int	i = 7;

	if (!(byte >> i-- & 1))
		send_signal(pid, SIGUSR1);
	else
		send_signal(pid, SIGUSR2);
	if (i == -1)
		i = 7;
	sigaction(SIGUSR2, &sa, NULL);
	usleep(1000);
}

static void	display_comms(int signal, siginfo_t *info, void *context)
{
	static int	bit;

	(void)context;
	signal--;
	info++;
	if (!bit)
		bit = 1;
	write(1, " 💼 ", 5);
	if (bit == 8)
	{
		write(1, "\n", 1);
		bit = 0;
	}
	bit++;
	usleep(100);
}

static void	too_many_lines(int i, char *argv2, int pid, struct sigaction sa)
{
	int	j;

	while (argv2[i])
	{
		j = 0;
		while (j < 8)
		{
			send_byte(argv2[i], pid, sa);
			j++;
		}
		i++;
	}
	j = 0;
	while (j < 8)
	{
		send_byte('\0', pid, sa);
		j++;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					i;
	int					pid;
	
	if (argc == 3)
	{
		argc--;
		pid = ft_atoi(argv[1]);
		i = 0;
		sa.sa_sigaction = display_comms;
		sa.sa_flags = SA_SIGINFO;
		too_many_lines(i, argv[2], pid, sa);
	}
}
