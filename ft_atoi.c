/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcano-ro <dcano-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:36:10 by dcano-ro          #+#    #+#             */
/*   Updated: 2022/05/12 20:06:03 by dcano-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int						i;
	int						signo;
	unsigned long long int	n;

	i = 0;
	n = 0;
	signo = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signo = -1;
		i++;
	}
	while (str[i] == '0')
		i++;
	while ('0' <= str[i] && str[i] <= '9')
		n = n * 10 + (str[i++] - 48);
	if (n > 9223372036854775807 && signo < 0)
		return (0);
	else if (n > 9223372036854775807 && signo > 0)
		return (-1);
	return ((int) n * signo);
}

void	duplicate_arr(t_dynamic_array *d_arr)
{
	char	*new_array;
	int		i;

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
