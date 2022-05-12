/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcano-ro <dcano-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 18:42:32 by dcano-ro          #+#    #+#             */
/*   Updated: 2022/05/12 20:16:34 by dcano-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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

static t_dynamic_array	*new_arr(int n)
{
	t_dynamic_array	*d_arr;

	d_arr = malloc(sizeof(t_dynamic_array));
	d_arr->i = 0;
	d_arr->size = n;
	d_arr->array = malloc(n);
	d_arr->nbit = 1;
	return (d_arr);
}

static int	too_many_lines2(siginfo_t *info, t_dynamic_array *d_arr)
{
	write(1, d_arr->array, d_arr->i);
	free(d_arr->array);
	free(d_arr);
	d_arr = NULL;
	kill(info->si_pid, SIGUSR2);
	return (1);
}

static void	sig_received(int sig, siginfo_t *info, void *context)
{
	static char				data = 0;
	static t_dynamic_array	*d_arr;

	(void)context;
	if (!d_arr)
		d_arr = new_arr(64);
	if (sig == SIGUSR2)
		data = data | power(8 - d_arr->nbit);
	if (d_arr->nbit == 8)
	{
		d_arr->array[d_arr->i] = data;
		if (!data && too_many_lines2(info, d_arr))
		{
			d_arr = NULL;
			return ;
		}
		d_arr->i = d_arr->i + 1;
		if (d_arr->i > d_arr->size - 8)
			duplicate_arr(d_arr);
		data = 0;
		d_arr->nbit = 0;
	}
	d_arr->nbit = d_arr->nbit + 1;
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
