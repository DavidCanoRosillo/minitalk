#include "minitalk.h"
#include <stdio.h>

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

static void duplicate_arr(dynamic_array *d_arr)
{
	char *new_array;
	int i;

	new_array = malloc(d_arr->size * 2);
	i = 0;
	while (i < d_arr->size)
	{
		new_array[i] = d_arr->array[i];
		i++;
	}
	d_arr->size = d_arr->size * 2;
	free(d_arr->array);
	d_arr->array = new_array;
}

static dynamic_array *new_arr(int n)
{
	dynamic_array *arr = malloc(sizeof(dynamic_array));
	arr->i = 0;
	arr->size = n;
	arr->array = malloc(n);
	return (arr);
}

static void	sig_received(int sig, siginfo_t *info, void *context)
{
	static int	nbit;
	static char	data;
	static dynamic_array *d_arr;
	(void)context;
	
	if (!d_arr)
	{
		nbit = 1;
		data = 0;
		d_arr = new_arr(64);
	}
	if (sig == SIGUSR2)
		data = data | power(8 - nbit);
	if (nbit == 8)
	{
		d_arr->array[d_arr->i] = data;
		if (!data)
		{
			write(1, d_arr->array, d_arr->i);
			free(d_arr->array);
			free(d_arr);
			d_arr = NULL;
			kill(info->si_pid, SIGUSR2);
			return;
		}

		d_arr->i = d_arr->i + 1;
		if (d_arr->i > d_arr->size - 8)
			duplicate_arr(d_arr);
		data = 0;
		nbit = 0;
	}
	nbit++;
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;	
	
	write(1, "SERVER PID ", 11);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);

	sa.sa_sigaction = sig_received;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
