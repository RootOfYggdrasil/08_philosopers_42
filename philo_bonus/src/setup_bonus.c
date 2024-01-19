/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 19:39:14 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/19 11:24:13 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_init_sem(t_core *c)
{
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("fork");
	sem_unlink("check_eat");
	sem_unlink("pid_sem");
	c->pid_sem = sem_open("pid_sem", O_CREAT, 0660, 1);
	c->print = sem_open("print", O_CREAT, 0660, 1);
	c->dead = sem_open("dead", O_CREAT, 0660, 0);
	c->fork = sem_open("fork", O_CREAT, 0660, c->ph_n);
	c->check_eat = sem_open("check_eat", O_CREAT, 0660, 1);
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
	ft_init_sem(c);
	c->isdead = 0;
	c->phfull_n = c->ph_n;
	c->t_start = ft_get_time();
}

void	ft_allocate_philo(t_core *c)
{
	int	i;

	i = 0;
	sem_wait(c->pid_sem);
	c->philo = malloc(c->ph_n * sizeof(t_philo));
	sem_post(c->pid_sem);
	if (!c->philo)
		stderr_exit("Error on Malloc\n");
	while (i < c->ph_n)
	{
		c->philo[i].id = i;
		c->philo[i].eat_n = c->eat_n;
		c->philo[i].sleep_t = c->sleep_t;
		c->philo[i].core = c;
		c->philo[i].t_start = c->t_start;
		c->philo[i].lm_t = c->t_start;
		c->philo[i].eat_t = c->eat_t;
		i++;
	}
}

int	ft_checkargs(int ac, char **av)
{
	int	i;
	int	j;
	int	out;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != '\0')
		{
			if (ft_isdigit(av[i][j]))
				j++;
			else
				return (-1);
		}
		out = ft_atoi(av[i]);
		if (out < 0)
			return (out);
		i++;
	}
	return (out);
}

void	ft_init(int ac, char **av, t_core *c)
{
	if (ac < 5 || 6 < ac)
		return (stderr_exit("Invalid number of arguments\n"));
	if (!c)
		return (stderr_exit("Error on Malloc\n"));
	if (ft_checkargs(ac - 1, av + 1) < 0)
	{
		free(c);
		return (stderr_exit("Invalid arguments\n"));
	}
	ft_setenv(ac, av, c);
	ft_allocate_philo(c);
}
