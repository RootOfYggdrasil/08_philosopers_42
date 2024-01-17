/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:39:14 by sdel-gra          #+#    #+#             */
/*   Updated: 2023/11/28 17:24:19 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_assign_fork(t_philo *p)
{
	p->fork_r = p->core->fork + p->id;
	p->fork_l = p->core->fork + ((p->id + 1) % p->core->ph_n);
}

void	ft_setenv(int ac, char **av, t_core *c)
{
	int	i;

	i = 0;
	c->ph_n = ft_atoi(av[1]);
	c->die_t = ft_atoi(av[2]);
	c->eat_t = ft_atoi(av[3]);
	c->sleep_t = ft_atoi(av[4]);
	c->eat_n = -1;
	if (ac == 6)
		c->eat_n = ft_atoi(av[5]);
	c->fork = (pthread_mutex_t *)malloc(c->ph_n * sizeof(pthread_mutex_t));
	c->philo = (t_philo *) malloc(c->ph_n * sizeof(t_philo));
	c->thread = (pthread_t *) malloc(c->ph_n * sizeof(pthread_t));
	c->print = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	c->dead = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	c->isdead = 0;
	c->phfull_n = c->ph_n;
	while (i < c->ph_n)
		pthread_mutex_init(c->fork + i++, NULL);
	pthread_mutex_init(c->print, NULL);
	pthread_mutex_init(c->dead, NULL);
	pthread_mutex_init(&c->check_eat, NULL);
	c->t_start = ft_get_time();
	c->ut_start = ft_get_time();
}

void	ft_allocate_philo(t_core *c)
{
	int	i;

	i = 0;
	while (i < c->ph_n)
	{
		c->philo[i].id = i;
		c->philo[i].eat_n = c->eat_n;
		c->philo[i].sleep_t = c->sleep_t;
		c->philo[i].core = c;
		ft_assign_fork(c->philo + i);
		c->philo[i].t_start = c->t_start;
		c->philo[i].lm_t = c->t_start;
		c->philo[i].eat_t = c->eat_t;
		i++;
	}
}

int	ft_checkargs(int ac, char **av)
{
	int	i;
	int	out;

	i = 0;
	while (i < ac)
	{
		out = ft_atoi(av[i]);
		if (out < 0)
			return (out);
		i++;
	}
	return (out);
}

void	ft_init(int ac, char **av, t_core *c)
{
	ft_setenv(ac, av, c);
	ft_allocate_philo(c);
}
