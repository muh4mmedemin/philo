/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:35:09 by muayna            #+#    #+#             */
/*   Updated: 2026/05/11 16:42:31 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void take_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->left_fork]);
	pthread_mutex_lock(&philo->data->fork[philo->right_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("MS %d taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

void *routuine(void *arg)
{
	t_philo *philo;

	philo = ((t_philo*)arg);
	if(philo->id % 2 != 0)
		usleep(10);
	take_fork(philo);
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