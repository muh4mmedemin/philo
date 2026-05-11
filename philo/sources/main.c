/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:07 by muayna            #+#    #+#             */
/*   Updated: 2026/05/11 16:25:12 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"
#include "limits.h"

void exit_program(char *exit_message)
{
    printf("%s\n", exit_message);
    ft_malloc(1, 1);
    exit(1);
}

int main(int argc, char **argv)
{
    t_args *user_input_list;
    t_global_data *global_data;
    int i;

    i = 0;
    user_input_list = init_args(argv, argc);
    global_data = init_philo(user_input_list);
    create_philo(global_data);
    while(i < global_data->user_args->number_of_philo)
    {
        pthread_join(global_data->philo_id_numbers[i], NULL);
        i++;
    }
}
