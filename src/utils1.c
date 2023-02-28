/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 20:53:52 by ajari             #+#    #+#             */
/*   Updated: 2023/03/01 00:51:07 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, 0);
	return ((t.tv_sec * 1000 + t.tv_usec / 1000));
}

int	check_args(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == -10)
			return (0);
		i++;
	}
	return (1);
}

int	check_eat(int *t, int size)
{
	int	i;

	i = 0;
	while (i < size && t[i] == 1)
		i++;
	if (i == size)
		return (1);
	return (0);
}

void	check_die(t_philo *p, int i)
{
	int	*eat;

	eat = malloc(sizeof(int) * p[0].n);
	while (1)
	{
		i = 0;
		while (i < p[0].n)
		{
			if (check_eat(eat, p[0].n))
			{
				free(eat);
				return ;
			}
			pthread_mutex_lock(&p[i].g);
			if (!check(p, i, eat))
			{
				free(eat);
				pthread_mutex_unlock(&p[i].g);
				return ;
			}
			pthread_mutex_unlock(&p[i].g);
			i++;
		}
	}
}

int	check_str(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("error\n");
			return (0);
		}
		i++;
	}
	return (1);
}
