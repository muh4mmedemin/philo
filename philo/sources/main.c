/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:07 by muayna            #+#    #+#             */
/*   Updated: 2026/04/26 16:49:06 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void exit_program(char *exit_message)
{
    printf("%s\n", exit_message);
    ft_malloc(1, 1);
    exit(1);
}

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