/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:42:19 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/17 18:24:55 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

int	ft_isdead(t_philo *ph)
{
	int	tmp;

	tmp = 0;
	pthread_mutex_lock(ph->core->dead);
	tmp = ph->core->isdead;
	pthread_mutex_unlock(ph->core->dead);
	return (tmp);
}

void	ft_eat(t_philo *ph)
{
	
	sem_wait(ph->core->fork);
	ft_message(ph, 'f');
	sem_wait(ph->core->fork);
	ft_message(ph, 'f');
	ft_message(ph, 'e');
	if (ph->eat_n > 0)
		ph -> eat_n--;
	ft_usleep(ph->eat_t);
	sem_wait(&ph->core->check_eat);	
	ph->lm_t = ft_get_time();
	if (ph->eat_n == 0)
		ph->core->phfull_n--;
	sem_post(&ph->core->check_eat);
	sem_post(ph->core->fork);
	sem_post(ph->core->fork);
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
