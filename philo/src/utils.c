/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:43:32 by sdel-gra          #+#    #+#             */
/*   Updated: 2023/11/28 17:33:09 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *nptr)
{
	int	sing;
	int	num;

	num = 0;
	sing = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sing *= -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
		num = num * 10 + (*nptr++ - '0');
	return (num * sing);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_isspace(int c)
{
	return (c == '\f' || c == '\n' || c == '\r' \
	|| c == '\t' || c == '\v' || c == ' ');
}

int	stderr_exit(const char *s)
{
	write(2, s, ft_strlen(s));
	return (1);
}

void	ft_message(t_philo *ph, char c)
{
	pthread_mutex_lock(ph->core->print);
	pthread_mutex_lock(ph->core->dead);
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
	pthread_mutex_unlock(ph->core->dead);
	pthread_mutex_unlock(ph->core->print);
}
