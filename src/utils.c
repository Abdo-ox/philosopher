/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 21:10:39 by ajari             #+#    #+#             */
/*   Updated: 2023/02/28 17:05:14 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_strcmp(char *s, char *s1)
{
	int	i;

	i = 0;
	while (s[i] || s1[i])
	{
		if (s[i] != s1[i])
			return (s[i] - s1[i]);
		i++;
	}
	return (0);
}

void	print_state(char *activity, int id, t_philo *t)
{
	(void)id;
	pthread_mutex_lock(&t->forks[t->n]);
	printf("%lums %d %s\n", (get_time() - t->t_c), id, activity);
	if (ft_strcmp("die", activity))
		pthread_mutex_unlock(&t->forks[t->n]);
}

int	check(t_philo *p, int i, int *t)
{
	if (!p[i].n_eat)
		t[i] = 1;
	else if ((get_time() - p[i].last) >= p[0].t_die)
	{
		print_state("die", p[i].id, &p[i]);
		return (0);
	}
	return (1);
}

void	terminate(t_philo *p)
{
	int	i;

	i = 0;
	while (i <= p[0].n)
	{
		if (i < p[0].n)
			pthread_mutex_destroy(&p[i].g);
		pthread_mutex_destroy(&p[0].forks[i]);
		i++;
	}
}

int	ft_atoi(const char *str)
{
	unsigned long	v;
	int				i;

	i = 0;
	v = 0;
	if (!str)
		return (-1);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (!check_str(str + i))
		return (-10);
	while (str[i] >= '0' && str[i] <= '9')
	{
		v = v * 10 + (str[i++] - 48);
		if (v > INT_MAX)
		{
			printf("error out of range number\n");
			return (-10);
		}
	}
	if (!v)
		return (-10);
	return (v);
}
