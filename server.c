#include "minitalk.h"

static void	usr_1(void)
{
	write(1, "0", 1);
}

static void	usr_2(void)
{
	write(1, "1", 1);
}

static int	power(int nbr)
{
	int	res;

	res = 1;
	if (nbr == 0)
		return (res);
	while (nbr)
	{
		res = res * 2;
		nbr--;
	}
	return (res);
}

static void	sig_received(int sig, siginfo_t *info, void *context)
{
	static int	g_nbit;
	static char	data;
	char		debug;

	if (!data)
		data = 0;
	if (!g_nbit)
		g_nbit = 1;
	if (sig == SIGUSR2)
		data = data | power(8 - g_nbit);
	if (g_nbit == 8)
	{
		write(1, &data, 1);
		data = 0;
		g_nbit = 0;
	}
	g_nbit++;
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;	
	
	write(1, "SERVER PID ", 11);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	//printf("SERVER PID:%d\n", getpid());
	sa.sa_sigaction = sig_received;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
