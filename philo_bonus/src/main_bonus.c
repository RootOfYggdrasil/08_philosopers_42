/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:15:41 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/18 17:04:11 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_message(t_philo *ph, char c)
{
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
		kill(core->philo[i].pid, SIGKILL);
		i++;
	}
	sem_post(core->dead);
	return (NULL);
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
		stderr_exit("Error creating thread\n");
	while (i < core->ph_n)
	{
		core->philo[i].pid = fork();
		if (core->philo[i].pid == 0)
			ft_routine(core->philo + i);
		else if (core->philo[i].pid == -1)
			stderr_exit("Error forking\n");
		i++;
	}
	i = 0;
	while (i < core->ph_n)
		waitpid(core->philo[i++].pid, NULL, 0);
	
	pthread_join(handle_death, NULL);
	ft_free_core(core);
	return (0);
}
