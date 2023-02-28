/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 13:14:25 by ajari             #+#    #+#             */
/*   Updated: 2023/02/28 16:57:52 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *t)
{
	print_state("has taken a fork", t->id, t);
	print_state("has taken a fork", t->id, t);
	print_state("is eating", t->id, t);
	pthread_mutex_lock(&t->g);
	if (t->n_eat != -1)
		t->n_eat--;
	t->last = get_time();
	pthread_mutex_unlock(&t->g);
}

void	*routine(void *p)
{
	t_philo	*t;

	t = (t_philo *)p;
	if (!((t->id) % 2))
		usleep(1000);
	while (t->n_eat)
	{
		pthread_mutex_lock(&t->forks[t->id - 1]);
		pthread_mutex_lock(&t->forks[t->id % t->n]);
		eating(t);
		while (get_time() - t->last < t->t_eat)
			usleep(200);
		pthread_mutex_unlock(&t->forks[t->id % t->n]);
		pthread_mutex_unlock(&t->forks[t->id - 1]);
		print_state("is thinking", t->id, t);
		print_state("is sleeping", t->id, t);
		t->last_slp = get_time();
		while (get_time() - t->last_slp < t->t_slp)
			usleep(200);
	}
	return (NULL);
}

void	fill_all(char **av, t_philo *t)
{
	int	i;

	i = 0;
	while (i < ft_atoi(av[1]))
	{
		if (i)
			t[i].forks = t[0].forks;
		t[i].id = i + 1;
		t[i].n = ft_atoi(av[1]);
		t[i].t_die = ft_atoi(av[2]);
		t[i].t_eat = ft_atoi(av[3]);
		t[i].t_slp = ft_atoi(av[4]);
		t[i].n_eat = ft_atoi(av[5]);
		pthread_mutex_init(&t[i].g, NULL);
		pthread_mutex_init(&t[0].forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&t[0].forks[i], NULL);
}

t_philo	*fill_arg(char **av)
{
	t_philo	*t;

	t = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	t[0].forks = malloc(sizeof(pthread_mutex_t) * (ft_atoi(av[1]) + 1));
	if (!t || !t[0].forks)
	{
		printf("Error\nallocation !!");
		return (0);
	}
	fill_all(av, t);
	t[0].m = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	if (!t[0].m)
	{
		printf("Error\nallocation !!");
		return (0);
	}
	return (t);
}

int	main(int ac, char **av)
{
	t_philo	*p;
	int		i;

	i = 0;
	if ((ac == 5 || ac == 6) && check_args(av, ac))
	{
		p = fill_arg(av);
		if (p)
		{
			p[0].t_c = get_time();
			while (i < ft_atoi(av[1]))
			{
				p[i].t_c = p[0].t_c;
				p[i].last = p[0].t_c;
				p[i].last_slp = 0;
				if (pthread_create(&p[0].m[i], NULL, &routine, &p[i]) == -1)
					return (printf("error duren the creation of treads\n"), 0);
				i++;
			}
			check_die(p, 0);
			terminate(p);
		}
		return (0);
	}
}
