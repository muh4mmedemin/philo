/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:35:09 by muayna            #+#    #+#             */
/*   Updated: 2026/06/07 21:32:30 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int anyone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if(philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return 1;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return 0;
}

int sleep_philo(t_philo *philo)
{
	if (anyone_dead(philo))
		return 1;
	pthread_mutex_lock(&philo->data->print_mutex);
	print_str(calculate_timestep(philo->data), philo->id, "is sleeping");
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (ft_usleep(philo->data->user_args->time_to_sleep, philo, SLEEP))
		return 1;
	return 0;
}

int eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->safe_lock);
	philo->last_meal = calculate_timestep(philo->data);
	pthread_mutex_unlock(&philo->safe_lock);
	if (anyone_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		return 1 ;
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	print_str(calculate_timestep(philo->data), philo->id, "is eating");
	pthread_mutex_unlock(&philo->data->print_mutex);
	if(ft_usleep(philo->data->user_args->time_to_eat, philo, EAT))
		return 1;
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	return 0;
}

int take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	if (anyone_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		return 1;
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	print_str(calculate_timestep(philo->data), philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	if (anyone_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
		return 1;
	}
	pthread_mutex_lock(&philo->data->print_mutex);
	print_str(calculate_timestep(philo->data), philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_mutex);
	return 0;
}

void *routuine(void *arg)
{
	t_philo *philo;

	philo = ((t_philo*)arg);
	if(((t_philo*)arg)->id % 2 != 0)
		usleep(200);
	while(1)
	{
		if (anyone_dead(philo))
			break ;
		pthread_mutex_lock(&philo->data->print_mutex);
		print_str(calculate_timestep(philo->data), philo->id, "is thinking");
		pthread_mutex_unlock(&philo->data->print_mutex);
		if (take_fork(philo) == 1)
			break ;
		if (eat_meal(philo))
			break ;
		if (sleep_philo(philo))
			break ;
	}
	return NULL;
}

void create_philo(t_global_data *global_data)
{
    int i;

    i = 0;
    while(i < global_data->user_args->number_of_philo)
    {
        pthread_create(&global_data->philo_id_numbers[i], NULL, routuine, &global_data->philos[i]);
        i++;
    }
}
