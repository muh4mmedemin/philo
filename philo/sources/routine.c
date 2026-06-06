/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:35:09 by muayna            #+#    #+#             */
/*   Updated: 2026/06/06 11:24:09 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%d MS %d taken a fork\n",calculate_timestep(philo->data, philo), (philo->id));
	pthread_mutex_unlock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%d MS %d taken a fork\n",calculate_timestep(philo->data, philo), (philo->id));
	pthread_mutex_unlock(&philo->data->fork[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void *routuine(void *arg)
{
	if(((t_philo*)arg)->id % 2 != 0)
		usleep(2000000);
	take_fork((t_philo*)arg);
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