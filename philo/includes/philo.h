/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:16 by muayna            #+#    #+#             */
/*   Updated: 2026/04/26 21:46:36 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "string.h"
# include "stdio.h"
# include "stdlib.h"
# include "pthread.h"
# include "unistd.h"
# include "utils.h"

/*
eat_count value is a optinal value, it can be empty.
Others value is requaried, Must not empty.
*/

typedef struct s_args
{
    long number_of_phil;
    long time_to_die;
    long time_to_eat;
    long time_to_sleep;
    long eat_count;
}t_args;




void init_args(t_args **args_list, char **argv, int argc);
void exit_program(char *exit_message);

#endif

