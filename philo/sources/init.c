/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:29:50 by muayna            #+#    #+#             */
/*   Updated: 2026/04/26 21:59:36 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void isbiggerint(char **argv)
{
    unsigned long i;

    i = 0;
    while(argv[i])
    {
        if(ft_strlen(argv[i]) > 10)
            exit_program("Max Int Value");
        else if(ft_atoi(argv[i]) > 2147483647)
            exit_program("Max Int Value");
        i++;
    }
}

void check_all_digit(char **argv, int argc)
{
    unsigned int i;
    unsigned int a;

    a = 1;
    i = 0;
    while(a != argc)
    {
        i = 0;
        while(argv[a][i])
        {
            if(!ft_isdigit(argv[a][i]))
                exit_program("Just type number");
            i++;
        }
        a++;
    }
}

void check_error(char **argv, int argc)
{
    if(argc != 5 && argc != 6)
        exit_program("Missing or excessive values ​​were entered.");
    check_all_digit(argv, argc);
    isbiggerint(argv);
}

void init_args(t_args **args_list, char **argv, int argc)
{
    check_error(argv, argc);
    (*args_list)->number_of_phil = ft_atoi(argv[1]);
    (*args_list)->time_to_die = ft_atoi(argv[2]);
    (*args_list)->time_to_eat = ft_atoi(argv[3]);
    (*args_list)->time_to_sleep = ft_atoi(argv[4]);
    if(argc == 6)
        (*args_list)->eat_count = ft_atoi(argv[5]);
    else
        (*args_list)->eat_count = -1;
}
