/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:07 by muayna            #+#    #+#             */
/*   Updated: 2026/05/10 16:35:08 by muayna           ###   ########.fr       */
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

    user_input_list = ft_malloc((sizeof(t_args)), 0);
    init_args(&user_input_list, argv, argc);
    init_philo(user_input_list);
}