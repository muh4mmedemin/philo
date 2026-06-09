/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:07 by muayna            #+#    #+#             */
/*   Updated: 2026/06/09 22:23:16 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned long long	calculate_timestep(t_global_data *global_data)
{
	struct timeval		current_time;
	unsigned long long	time_ms;

	gettimeofday(&current_time, NULL);
	time_ms = ((current_time.tv_sec - global_data->app_start_time.tv_sec)
			* 1000ULL) + ((current_time.tv_usec
				- global_data->app_start_time.tv_usec) / 1000);
	return (time_ms);
}

void	exit_program(char *exit_message)
{
	if (exit_message != NULL)
		printf("%s\n", exit_message);
	ft_malloc(1, 1);
	exit(1);
}

int	main(int argc, char **argv)
{
	t_args			*user_input_list;
	t_global_data	*global_data;
	pthread_t		monitor;
	int				i;

	i = 0;
	user_input_list = init_args(argv, argc);
	global_data = init_philo(user_input_list);
	gettimeofday(&global_data->app_start_time, NULL);
	create_philo(global_data);
	pthread_create(&monitor, NULL, check_philo_health, global_data);
	while (i < global_data->user_args->number_of_philo)
	{
		pthread_join(global_data->philo_id_numbers[i], NULL);
		i++;
	}
	pthread_join(monitor, NULL);
	ft_malloc(1, 1);
}
