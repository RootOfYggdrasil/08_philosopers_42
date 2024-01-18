/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdel-gra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:43:32 by sdel-gra          #+#    #+#             */
/*   Updated: 2024/01/18 19:48:06 by sdel-gra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo_bonus.h"

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

void	stderr_exit(const char *s)
{
	write(2, s, ft_strlen(s));
	exit (1);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}
