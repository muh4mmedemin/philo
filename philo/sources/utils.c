/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:04:13 by muayna            #+#    #+#             */
/*   Updated: 2026/06/08 23:30:44 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if(s == NULL)
		return 0;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

long long	ft_atoi(const char *nptr)
{
	int		i;
	int		countnp;
	long	number;

	number = 0;
	countnp = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			countnp = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	return (number * countnp);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

void print_str(unsigned long long time_step, long long philo_id, char *message)
{
	if (message == NULL)
		return ;
	philo_id++;
	printf("%llu %lld %s\n",time_step, philo_id, message);
	return ;
}

int ft_usleep(unsigned long long sleep_time_ms, t_philo *philo)
{
	unsigned long long current_time;
	unsigned long long start_time;
	struct timeval time;

	gettimeofday(&time, NULL);
	start_time = (time.tv_sec * 1000ULL) + (time.tv_usec / 1000);
	current_time = start_time;

	while((current_time - start_time) < sleep_time_ms)
	{
		if(anyone_dead(philo))
		{
			return 1;
		}
		gettimeofday(&time, NULL);
		current_time = (time.tv_sec * 1000ULL) + (time.tv_usec / 1000);
		usleep(300);
	}
	return 0;
}
