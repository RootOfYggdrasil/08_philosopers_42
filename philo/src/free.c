/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:33:32 by sdel-gra          #+#    #+#             */
/*   Updated: 2023/11/28 17:40:38 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
	ft_free((void **)&c->fork);
	ft_free((void **)&c->philo);
	ft_free((void **)&c->thread);
	ft_free((void **)&c->print);
	ft_free((void **)&c->dead);
	ft_free((void **)&c);
}
