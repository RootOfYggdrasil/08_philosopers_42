/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:42:19 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/19 14:00:46 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_eat(t_philo *ph)
{
	sem_wait(ph->core->fork);
	ft_message(ph, 'f');
	sem_wait(ph->core->fork);
	ft_message(ph, 'f');
	ft_message(ph, 'e');
	sem_wait(ph->core->check_eat);
	if (ph->eat_n > 0)
		ph -> eat_n--;
	ph->lm_t = ft_get_time();
	sem_post(ph->core->check_eat);
	ft_usleep(ph->eat_t);
	sem_post(ph->core->fork);
	sem_post(ph->core->fork);
}

/*Thread controllo morte dentro philo*/
void	*ft_check_death(void *arg)
{
	t_philo		*philo;

	philo = (t_philo *)arg;
	while (true)
	{
		sem_wait(philo->core->check_eat);
		if (philo->eat_n == 0)
		{
			sem_post(philo->core->check_eat);
			break ;
		}
		if (((long)philo->core->die_t) < ft_get_time() - philo->lm_t)
		{
			ft_message(philo, 'd');
			sem_post(philo->core->check_eat);
			break ;
		}
		sem_post(philo->core->check_eat);
	}
	return (NULL);
}

/*Routine del philosofo*/
void	ft_routine(t_philo	*philo)
{
	pthread_t	check_death;

	pthread_create(&check_death, NULL, ft_check_death, (void *)philo);
	while (philo->eat_n != 0 && !philo->core->isdead)
	{
		ft_eat(philo);
		ft_message(philo, 's');
		ft_usleep(philo->sleep_t);
		ft_message(philo, 't');
		ft_usleep(3);
	}
	pthread_join(check_death, NULL);
	ft_free_core(philo->core);
	exit(0);
}
