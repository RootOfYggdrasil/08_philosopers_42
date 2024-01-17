/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:42:19 by sdel-gra          #+#    #+#             */
/*   Updated: 2023/11/28 17:47:54 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_isdead(t_philo *ph)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(ph->core->dead);
	tmp = ph->core->isdead;
	pthread_mutex_unlock(ph->core->dead);
	return (tmp);
}

void	ft_lock_fork(t_philo *ph)
{
	if (ph->id == ph->core->ph_n - 1)
	{
		pthread_mutex_lock(ph->fork_l);
		ft_message(ph, 'f');
		pthread_mutex_lock(ph->fork_r);
	}
	else
	{
		pthread_mutex_lock(ph->fork_r);
		ft_message(ph, 'f');
		pthread_mutex_lock(ph->fork_l);
	}
}

void	ft_eat(t_philo *ph)
{
	ft_lock_fork(ph);
	ft_message(ph, 'f');
	ft_message(ph, 'e');
	if (ph->eat_n > 0)
		ph -> eat_n--;
	ft_usleep(ph->eat_t);
	pthread_mutex_lock(&ph->core->check_eat);
	ph->lm_t = ft_get_time();
	if (ph->eat_n == 0)
		ph->core->phfull_n--;
	pthread_mutex_unlock(&ph->core->check_eat);
	if (ph->id == ph->core->ph_n - 1)
	{
		pthread_mutex_unlock(ph->fork_l);
		pthread_mutex_unlock(ph->fork_r);
	}
	else
	{
		pthread_mutex_unlock(ph->fork_r);
		pthread_mutex_unlock(ph->fork_l);
	}
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		usleep(1000);
	if (philo->id % philo->core->ph_n && philo->id != 0)
		usleep(2000);
	while (!ft_isdead(philo) && philo->eat_n != 0)
	{
		ft_eat(philo);
		ft_message(philo, 's');
		ft_usleep(philo->sleep_t);
		ft_message(philo, 't');
	}
	return (NULL);
}

void	ft_start_routine(t_core *c)
{
	int	i;

	i = 0;
	while (i < c->ph_n)
	{
		pthread_create(c->thread + i, NULL, &ft_routine, c->philo + i);
		i++;
	}
	ft_usleep(1);
	ft_bigbro_watchingyou(c);
}
