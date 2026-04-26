/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:07 by muayna            #+#    #+#             */
/*   Updated: 2026/04/26 16:36:39 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int argc, char **argv)
{
    t_args *args;

    args = ft_malloc(sizeof(t_args) * 1, 0);
    init_args(&args, argv, argc);
    printf("%d\n",args->eat_count);
    printf("%d\n",args->number_of_phil);
    printf("%d\n",args->time_to_die);
    printf("%d\n",args->time_to_eat);
    printf("%d\n", args->time_to_sleep);
}