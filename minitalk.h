#ifndef MINITALK_H
# define MINITALK_H
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>

int	ft_atoi(const char *str);
int	nbit;
int	ft_putnbr_fd(int n, int fd);
typedef struct dynamic_array
{
    int i;
    int size;
    char *array;
}	dynamic_array;
#endif
