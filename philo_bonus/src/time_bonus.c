/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 20:05:57 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/19 14:07:29 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

long int	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

long int	ft_time(t_philo *p)
{
	return (ft_get_time() - p->t_start);
}

void	ft_usleep(long int time)
{
	long int	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < time)
		usleep(5);
}
