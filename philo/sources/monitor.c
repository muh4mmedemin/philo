/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:25:03 by muayna            #+#    #+#             */
/*   Updated: 2026/06/08 16:52:27 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/philo.h"

void *check_philo_health(void *arg)
{
    int i = 0;
    unsigned long long test;
    unsigned long long s;
    unsigned long long kill_time;
    unsigned long long last_meal;
    t_global_data *data;

    data = (t_global_data*)arg;
    kill_time = data->user_args->time_to_die;
    while(anyone_dead(&data->philos[i]) != 1)
    {
        usleep(200);
        s = 0;
        pthread_mutex_lock(&data->philos[i].safe_lock);
        last_meal = data->philos[i].last_meal;
        pthread_mutex_unlock(&data->philos[i].safe_lock);
        test = calculate_timestep(data);
        s = test - last_meal;
        if (s > kill_time)
        {
            pthread_mutex_lock(&data->dead_mutex);
            data->is_dead = 1;
            pthread_mutex_unlock(&data->dead_mutex);
            pthread_mutex_lock(&data->print_mutex);
            print_str(calculate_timestep(data), i, "died");
            pthread_mutex_unlock(&data->print_mutex);
            break;
        }
        if ((data->user_args->number_of_philo - 1) == i)
            i = 0;
        else
            i++;
    }
    return NULL;
}
