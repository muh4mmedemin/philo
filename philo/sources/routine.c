/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:35:09 by muayna            #+#    #+#             */
/*   Updated: 2026/06/09 22:35:22 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	one_philo_handle(t_philo *philo)
{
	if (philo->data->user_args->number_of_philo == 1)
	{
		if (ft_usleep(philo->data->user_args->time_to_die + 3, philo))
		{
			return (1);
		}
	}
	return (0);
}

int	anyone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return (0);
}

int	sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return (1);
	}
	print_str(calculate_timestep(philo->data), philo->id, "is sleeping");
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (ft_usleep(philo->data->user_args->time_to_sleep, philo))
		return (1);
	return (0);
}

void	lock_mutexes(pthread_mutex_t *first, pthread_mutex_t *sec)
{
	if (first != NULL)
		pthread_mutex_lock(first);
	if (sec != NULL)
		pthread_mutex_lock(sec);
}

void	*routuine(void *arg)
{
	t_philo	*philo;

	philo = ((t_philo *)arg);
	if (((t_philo *)arg)->id % 2 != 0)
		usleep(2000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (anyone_dead(philo))
		{
			pthread_mutex_unlock(&philo->data->print_mutex);
			break ;
		}
		print_str(calculate_timestep(philo->data), philo->id, "is thinking");
		pthread_mutex_unlock(&philo->data->print_mutex);
		if (take_fork(philo) == 1)
			break ;
		if (eat_meal(philo))
			break ;
		if (sleep_philo(philo))
			break ;
	}
	return (NULL);
}
