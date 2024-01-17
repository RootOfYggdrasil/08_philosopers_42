/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:43:30 by sdel-gra          #+#    #+#             */
/*   Updated: 2023/11/28 17:42:02 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <semaphore.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <stdbool.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>

# include <sys/types.h>

typedef struct s_philo	t_philo;

typedef struct s_core
{
	int				ph_n;
	int				phfull_n;
	int				isdead;
	size_t			die_t;
	size_t			eat_t;
	size_t			sleep_t;
	size_t			eat_n;
	t_philo			*philo;
	pthread_t		*thread;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print;
	pthread_mutex_t	*dead;
	pthread_mutex_t	check_eat;
	int				stop;
	long int		t_start;
	suseconds_t		ut_start;
}	t_core;

typedef struct s_philo
{
	int				id;
	int				eat_n;
	size_t			eat_t;
	long int		t_start;
	long int		lm_t;
	size_t			sleep_t;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	*fork_l;
	t_core			*core;
}	t_philo;

long int	ft_time(t_philo *p);
long int	ft_get_time(void);
int			ft_atoi(const char *nptr);
size_t		ft_strlen(const char *s);
int			ft_isspace(int c);
void		ft_usleep(long int time);
int			stderr_exit(const char *s);

int			ft_checkargs(int ac, char **av);
void		ft_init(int ac, char **av, t_core *c);

void		*ft_routine(void *arg);
void		ft_message(t_philo *ph, char c);
void		ft_start_routine(t_core *c);

void		ft_free_core(t_core *c);
void		ft_bigbro_watchingyou(t_core *c);

#endif