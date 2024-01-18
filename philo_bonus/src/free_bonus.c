/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:33:32 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/18 18:28:15 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

void	ft_close_sem(sem_t *sem, char *name)
{
	if (sem != NULL)
	{
		sem_close(sem);
		sem_unlink(name);
	}
}

void	ft_free(void **p)
{
	if (*p)
	{
		free(*p);
		*p = NULL;
	}
}

void	ft_free_core(t_core *c)
{
	ft_close_sem(c->fork, "fork");
	ft_close_sem(c->print, "print");
	ft_close_sem(c->dead, "dead");
	ft_close_sem(c->check_eat, "check_eat");
	ft_close_sem(c->pid_sem, "pid_sem");
	ft_free((void **)&c->philo);
	ft_free((void **)&c);
}
