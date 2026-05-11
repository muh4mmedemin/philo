/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:16 by muayna            #+#    #+#             */
/*   Updated: 2026/05/11 15:41:40 by muayna           ###   ########.fr       */
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
    long long number_of_philo;
    long long time_to_die;
    long long time_to_eat;
    long long time_to_sleep;
    long long eat_count;
}t_args;



typedef struct s_global_data t_global_data;

typedef struct s_philo
{
    long long id;
    long long last_meal;
    long long eat_count;
    long long right_fork;
    long long left_fork;
    t_global_data *data;
    pthread_mutex_t safe_lock;
}t_philo;


typedef struct s_global_data
{
    t_args *user_args;
    long long start_time;
    long long is_dead;
    pthread_t *philo_id_numbers;
    pthread_mutex_t *forks;
    pthread_mutex_t dead_mutex;
    pthread_mutex_t print_mutex;
    t_philo *philos;
}t_global_data;

void exit_program(char *exit_message);
t_args *init_args(char **argv, int argc);
t_global_data *init_philo(t_args *user_input);
void create_philo(t_global_data *global_data);

#endif

