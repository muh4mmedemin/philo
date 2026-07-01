/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 22:32:04 by muayna            #+#    #+#             */
/*   Updated: 2026/07/01 14:54:46 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	unlock_mutexes(pthread_mutex_t *first, pthread_mutex_t *sec,
		pthread_mutex_t *third, pthread_mutex_t *forth)
{
	if (first != NULL)
		pthread_mutex_unlock(first);
	if (sec != NULL)
		pthread_mutex_unlock(sec);
	if (third != NULL)
		pthread_mutex_unlock(third);
	if (forth != NULL)
		pthread_mutex_unlock(forth);
}

static void	update_last_meal_variable(t_philo **philo)
{
	pthread_mutex_lock(&(*philo)->safe_lock);
	(*philo)->last_meal = calculate_timestep((*philo)->data);
	pthread_mutex_unlock(&(*philo)->safe_lock);
}

int	eat_meal(t_philo *philo)
{
	update_last_meal_variable(&philo);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		unlock_mutexes(&philo->data->fork[philo->left_fork],
			&philo->data->fork[philo->right_fork], &philo->data->print_mutex,
			NULL);
		return (1);
	}
	print_str(calculate_timestep(philo->data), philo->id, "is eating");
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->safe_lock);
	if (philo->data->user_args->eat_count != -1)
		philo->eat_count += 1;
	pthread_mutex_unlock(&philo->safe_lock);
	if (ft_usleep(philo->data->user_args->time_to_eat, philo))
	{
		unlock_mutexes(&philo->data->fork[philo->left_fork],
			&philo->data->fork[philo->right_fork], NULL, NULL);
		return (1);
	}
	unlock_mutexes(&philo->data->fork[philo->left_fork],
		&philo->data->fork[philo->right_fork], NULL, NULL);
	return (0);
}

static void	init_fork_variable(long long *first_fork, long long *sec_fork,
		t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		(*first_fork) = philo->left_fork;
		(*sec_fork) = philo->right_fork;
		//usleep(2000);
	}
	else
	{
		(*first_fork) = philo->right_fork;
		(*sec_fork) = philo->left_fork;
	}
}

int	take_fork(t_philo *philo)
{
	long long	first_fork;
	long long	sec_fork;

	init_fork_variable(&first_fork, &sec_fork, philo);
	lock_mutexes(&philo->data->fork[first_fork], &philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		unlock_mutexes(&philo->data->fork[first_fork], NULL,
			&philo->data->print_mutex, NULL);
		return (1);
	}
	print_str(calculate_timestep(philo->data), philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (one_philo_handle(philo))
		return (1);
	lock_mutexes(&philo->data->fork[sec_fork], &philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		unlock_mutexes(&philo->data->fork[first_fork],
			&philo->data->fork[sec_fork], &philo->data->print_mutex, NULL);
		return (1);
	}
	print_str(calculate_timestep(philo->data), philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (0);
}
