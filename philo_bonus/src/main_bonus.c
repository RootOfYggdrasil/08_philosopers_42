/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:15:41 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/18 22:13:49 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_message(t_philo *ph, char c)
{
	sem_wait(ph->core->print);
	if (!ph->core->isdead)
	{
		if (c == 'd')
		{
			printf("%ld %d \e[1;31mdied\e[0m\n", ft_time(ph), ph->id);
			sem_post(ph->core->dead);
			return ;
		}
		if (c == 'e')
			printf("%ld %d \e[1;35mis eating\e[0m\n", ft_time(ph), ph->id);
		if (c == 's')
			printf("%ld %d \e[1;34mis sleeping\e[0m\n", ft_time(ph), ph->id);
		if (c == 't')
			printf("%ld %d \e[1;32mis thinking\e[0m\n", ft_time(ph), ph->id);
		if (c == 'f')
			printf("%ld %d \e[1;37mhas taken a fork\e[0m\n",
				ft_time(ph), ph->id);
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
	sem_wait(core->pid_sem);
	while (i < core->ph_n)
	{
		kill(core->philo[i].pid, SIGKILL);
		i++;
	}
	sem_post(core->pid_sem);
	sem_post(core->dead);
	return (NULL);
}

void	ft_norminette_main(t_core *core)
{
	int	i;

	i = 0;
	while (i < core->ph_n)
	{
		sem_wait(core->pid_sem);
		core->philo[i].pid = fork();
		sem_post(core->pid_sem);
		if (core->philo[i].pid == 0)
			ft_routine(core->philo + i);
		else if (core->philo[i].pid == -1)
			stderr_exit("Error forking\n");
		i++;
		ft_usleep(10);
	}
}

int	main(int ac, char **av)
{
	t_core		*core;
	int			i;
	pthread_t	handle_death;

	i = 0;
	core = (t_core *) malloc(sizeof(t_core));
	ft_init(ac, av, core);
	if (pthread_create(&handle_death, NULL, &ft_kill, (void *)core))
		stderr_exit("Error creating thread\n");
	ft_norminette_main(core);
	while (i < core->ph_n)
	{
		waitpid(core->philo[i].pid, NULL, 0);
		i++;
	}
	sem_post(core->dead);
	pthread_join(handle_death, NULL);
	ft_free_core(core);
	return (0);
}
