/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:26:26 by muayna            #+#    #+#             */
/*   Updated: 2026/06/11 13:06:23 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static int	init_global_data(t_global_data **data, t_args **user_input)
{
	(*data)->philo_id_numbers = ft_malloc(sizeof(pthread_t)
			* (*user_input)->number_of_philo, 0);
	(*data)->is_dead = 0;
	(*data)->user_args = (*user_input);
	(*data)->fork = ft_malloc(sizeof(pthread_mutex_t)
			* (*user_input)->number_of_philo, 0);
	(*data)->philos = ft_malloc((sizeof(t_philo)
				* (*user_input)->number_of_philo), 0);
	if ((*data)->philos == NULL || (*data)->fork == NULL
		|| (*data)->philo_id_numbers == NULL)
		return (1);
	return (0);
}

static void	init_mutex(t_global_data **source)
{
	int	i;

	i = 0;
	pthread_mutex_init(&(*source)->print_mutex, NULL);
	pthread_mutex_init(&(*source)->dead_mutex, NULL);
	while (i < (*source)->user_args->number_of_philo)
	{
		pthread_mutex_init(&(*source)->fork[i], NULL);
		i++;
	}
}

t_global_data	*init_philo(t_args *user_input)
{
	int				i;
	t_global_data	*global_data;

	i = 0;
	global_data = ft_malloc(sizeof(t_global_data), 0);
	if (init_global_data(&global_data, &user_input) || global_data == NULL)
		if (exit_program("MALLOC ERROR!"))
			return (NULL);
	init_mutex(&global_data);
	while (i < user_input->number_of_philo)
	{
		global_data->philos[i].last_meal = 0;
		global_data->philos[i].eat_count = 0;
		global_data->philos[i].id = i;
		global_data->philos[i].right_fork
			= (i + 1) % user_input->number_of_philo;
		global_data->philos[i].left_fork = i;
		global_data->philos[i].data = global_data;
		pthread_mutex_init(&global_data->philos[i].safe_lock, NULL);
		i++;
	}
	return (global_data);
}

void	create_philo(t_global_data *global_data)
{
	int	i;

	i = 0;
	while (i < global_data->user_args->number_of_philo)
	{
		pthread_create(&global_data->philo_id_numbers[i], NULL, routuine,
			&global_data->philos[i]);
		i++;
	}
}
