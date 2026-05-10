/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 16:26:26 by muayna            #+#    #+#             */
/*   Updated: 2026/05/10 16:57:32 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_global_data *init_philo(t_args *user_input)
{
    int i;
    t_global_data *global_data;

    i = 0;
    global_data = ft_malloc(sizeof(t_global_data), 0);
    global_data->philos = ft_malloc((sizeof(t_philo) * user_input->number_of_philo), 0);
    while(i < user_input->number_of_philo)
    {
        global_data->philos[i].id = i + 1;
        global_data->philos[i].right_fork = (i + 1) % user_input->number_of_philo;
        global_data->philos[i].left_fork = i;
        global_data->philos[i].data = global_data;
        i++;
    }
}
