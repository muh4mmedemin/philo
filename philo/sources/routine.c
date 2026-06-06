/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:35:09 by muayna            #+#    #+#             */
/*   Updated: 2026/06/06 12:35:11 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%zu %d is sleeping\n",calculate_timestep(philo->data, philo), (philo->id));
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->user_args->time_to_sleep * 1000);
}

void eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->safe_lock);
	philo->last_meal = calculate_timestep(philo->data, philo);
	pthread_mutex_unlock(&philo->safe_lock);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%zu %d is eating\n",calculate_timestep(philo->data, philo), (philo->id));
	pthread_mutex_unlock(&philo->data->print_mutex);
	usleep(philo->data->user_args->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
}

void take_fork(t_philo *philo)
{
	printf("%zu %d is thinking\n",calculate_timestep(philo->data, philo), (philo->id));
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%zu %d has taken a fork\n",calculate_timestep(philo->data, philo), (philo->id));
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%zu %d has taken a fork\n",calculate_timestep(philo->data, philo), (philo->id));
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void *routuine(void *arg)
{
	if(((t_philo*)arg)->id % 2 != 0)
		usleep(200);
	take_fork((t_philo*)arg);
	eat_meal((t_philo*)arg);
	sleep_philo((t_philo*)arg);
	routuine(arg);
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