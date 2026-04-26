/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:29:50 by muayna            #+#    #+#             */
/*   Updated: 2026/04/26 16:10:57 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void init_args(t_args **args_list, char **argv, int argc)
{
    (*args_list)->number_of_phil = ft_atoi(argv[1]);
    (*args_list)->time_to_die = ft_atoi(argv[2]);
    (*args_list)->time_to_eat = ft_atoi(argv[3]);
    (*args_list)->time_to_sleep = ft_atoi(argv[4]);
    if(argc == 6)
        (*args_list)->eat_count = ft_atoi(argv[5]);
    else
        (*args_list)->eat_count = -1;
}
