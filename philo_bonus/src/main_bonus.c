/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:15:41 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/17 18:15:54 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_message(t_philo *ph, char c)
{
	//wait semp
	//pthread_mutex_lock(ph->core->print);
	sem_wait(ph->core->print);
	if (!ph->core->isdead)
	{
		if (c == 'd')
			printf("%ld %d \e[1;31mdied\e[0m\n", ft_time(ph), ph->id);
		if (c == 'e')
			printf("%ld %d \e[1;35mis eating\e[0m\n", ft_time(ph), ph->id);
		if (c == 's')
			printf("%ld %d \e[1;34mis sleeping\e[0m\n", ft_time(ph), ph->id);
		if (c == 't')
			printf("%ld %d \e[1;32mis thinking\e[0m\n", ft_time(ph), ph->id);
		if (c == 'f')
			printf("%ld %d \e[1;37mhas taken fork\e[0m\n", ft_time(ph), ph->id);
	}
	sem_post(ph->core->print);
	//pthread_mutex_unlock(ph->core->print);
}

void	*ft_kill(void *arg)
{
	t_core	*core;
	int		i;

	core = (t_core *)arg;
	i = 0;
	sem_wait(core->dead);
	while (i < core->ph_n)
	{
		kill(core->philo[i].id, SIGKILL);
		i++;
	}
	sem_post(core->dead);

}

void	*ft_solo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	ft_message(philo, 'f');
	ft_usleep(philo->core->die_t);
	ft_message(philo, 'd');
	return (NULL);
}

int	ft_big(t_core *c, long int lm_cf, int i)
{
	pthread_mutex_lock(c->dead);
	pthread_mutex_lock(&c->check_eat);
	lm_cf = c->philo[i].lm_t;
	pthread_mutex_unlock(&c->check_eat);
	if ((long int)c->die_t < ft_get_time() - lm_cf)
	{
		printf("%ld %d \e[1;31mdied\e[0m\n", ft_time(c->philo), c->philo->id);
		c->isdead = 1;
		pthread_mutex_unlock(c->dead);
		return (1);
	}
	pthread_mutex_unlock(c->dead);
	return (0);
}

void	ft_bigbro_watchingyou(t_core *c)
{
	int			i;
	long int	lm_cf;

	i = 0;
	while (i < c->ph_n)
	{
		pthread_mutex_lock(&c->check_eat);
		if (c->phfull_n == 0)
		{
			pthread_mutex_unlock(&c->check_eat);
			break ;
		}
		lm_cf = c->philo[i].lm_t;
		pthread_mutex_unlock(&c->check_eat);
		if (ft_big(c, lm_cf, i))
			break ;
		if (++i == c->ph_n)
			i = 0;
	}
}

int	main(int ac, char **av)
{
	t_core		*core;
	int			i;
	pthread_t	handle_death;

	i = 0;
	if (ac < 5 || 6 < ac)
		return (stderr_exit("Invalid number of arguments\n"));
	core = (t_core *) malloc(sizeof(t_core));
	if (!core)
		return (stderr_exit("Error on Malloc\n"));
	if (ft_checkargs(ac - 1, av + 1) < 0)
	{
		free(core);
		return (stderr_exit("Invalid arguments\n"));
	}
	ft_init(ac, av, core);
	
	if (pthread_create(&handle_death, NULL, &ft_kill, (void *)core))
		stderr_exit("Error creating thread");

	pthread_join(handle_death, NULL);
	
	/*if (core->ph_n == 1)
		pthread_create(core->thread + i, NULL, &ft_solo, core->philo + i);	
	else
		ft_start_routine(core);
	i = 0;
	while (i < core->ph_n)
		pthread_join(core->thread[i++], NULL);*/
	
	ft_free_core(core);
	return (0);
}
