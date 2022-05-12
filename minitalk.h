/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcano-ro <dcano-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 19:37:32 by dcano-ro          #+#    #+#             */
/*   Updated: 2022/05/12 20:01:14 by dcano-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct monke
{
	int		i;
	int		size;
	int		nbit;
	char	*array;
}	t_dynamic_array;
int		ft_atoi(const char *str);
int		ft_putnbr_fd(int n, int fd);
void	duplicate_arr(t_dynamic_array *d_arr);
#endif