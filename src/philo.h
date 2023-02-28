/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajari <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 12:58:33 by ajari             #+#    #+#             */
/*   Updated: 2023/02/28 16:54:55 by ajari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_tim
{
	time_t			sec;
	suseconds_t		usec;
}					t_tim;

typedef struct s_philo
{
	unsigned long	last_slp;
	unsigned long	t_die;
	unsigned long	t_eat;
	unsigned long	t_slp;
	unsigned long	last;
	unsigned long	t_c;
	pthread_t		*m;
	pthread_t		j;
	int				n;
	int				id;
	int				n_eat;
	int				evry;
	pthread_mutex_t	g;
	pthread_mutex_t	*forks;
}					t_philo;
unsigned long		get_time(void);
void				*routine(void *data);
void				terminate(t_philo *p);
int					ft_atoi(const char *str);
int					check_str(const char *str);
void				check_die(t_philo *p, int i);
int					check_args(char **av, int ac);
int					check(t_philo *p, int i, int *t);
void				print_state(char *activity, int id, t_philo *t);

#endif
