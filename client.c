#include "minitalk.h"

int	send_signal(int pid, int signal)
{
	int	ret;

	ret = kill(pid, signal);
	return (0);
}

void	send_byte(char byte, int pid, struct sigaction sa)
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

void	display_comms(int signal, siginfo_t *info, void *context)
{
	static int	bit;

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
#include <stdio.h>
int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					i;
	int					j;
	int					pid;

	pid = ft_atoi(argv[1]);
	i = 0;
	sa.sa_sigaction = display_comms;
	sa.sa_flags = SA_SIGINFO;
	while (argv[2][i])
	{
		j = 0;
		while (j < 8)
		{
			send_byte(argv[2][i], pid, sa);
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
