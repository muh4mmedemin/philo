/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:26:26 by muayna            #+#    #+#             */
/*   Updated: 2026/06/08 22:22:43 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void init_mutex(t_global_data **source)
{
	int i;

	i = 0;
   	pthread_mutex_init(&(*source)->print_mutex,NULL);
	pthread_mutex_init(&(*source)->dead_mutex,NULL);
   	while(i < (*source)->user_args->number_of_philo)
	{
		pthread_mutex_init(&(*source)->fork[i],NULL);
		i++;
	}
}

t_global_data *init_philo(t_args *user_input)
{
    int i;
    t_global_data *global_data;

    i = 0;
    global_data = ft_malloc(sizeof(t_global_data), 0);
    global_data->philo_id_numbers = ft_malloc(sizeof(pthread_t) * user_input->number_of_philo, 0);
    //global_data->start_time = 0;
    global_data->is_dead = 0;
    global_data->user_args = user_input;
    global_data->fork = ft_malloc(sizeof(pthread_mutex_t) * user_input->number_of_philo, 0);
    global_data->philos = ft_malloc((sizeof(t_philo) * user_input->number_of_philo), 0);
	init_mutex(&global_data);
    while(i < user_input->number_of_philo)
    {
        global_data->philos[i].last_meal = 0;
        global_data->philos[i].eat_count = 0;
        global_data->philos[i].id = i;
        global_data->philos[i].right_fork = (i + 1) % user_input->number_of_philo;
        global_data->philos[i].left_fork = i;
        global_data->philos[i].data = global_data;
		pthread_mutex_init(&global_data->philos[i].safe_lock, NULL);
        i++;
    }
    return global_data;
}
