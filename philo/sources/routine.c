/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:35:09 by muayna            #+#    #+#             */
/*   Updated: 2026/05/11 15:55:29 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void *say_hello(void *arg)
{
    static int i = 0;
    t_global_data *global_data = (t_global_data*)arg;
    pthread_mutex_lock(&global_data->print_mutex);
    i++;
    printf("oluştum%d\n", i);
    pthread_mutex_unlock(&global_data->print_mutex);
    return NULL;
}

void create_philo(t_global_data *global_data)
{
    int i;

    i = 0;
    while(i < global_data->user_args->number_of_philo)
    {
        pthread_create(&global_data->philo_id_numbers[i], NULL, say_hello, global_data);
        i++;
    }
}