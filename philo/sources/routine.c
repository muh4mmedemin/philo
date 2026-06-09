/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 15:35:09 by muayna            #+#    #+#             */
/*   Updated: 2026/06/09 21:39:25 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int one_philo_handle(t_philo *philo)
{
	if (philo->data->user_args->number_of_philo == 1)
	{
		if (ft_usleep(philo->data->user_args->time_to_die + 3, philo))
		{
			return 1;
		}	
	}
	return 0;
}

int anyone_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_mutex);
	if(philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_mutex);
		return 1;
	}
	pthread_mutex_unlock(&philo->data->dead_mutex);
	return 0;
}

int sleep_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		pthread_mutex_unlock(&philo->data->print_mutex);
		return 1;
	}
	print_str(calculate_timestep(philo->data), philo->id, "is sleeping");
	pthread_mutex_unlock(&philo->data->print_mutex);
	if (ft_usleep(philo->data->user_args->time_to_sleep, philo))
		return 1;
	return 0;
}

void unlock_mutexes(pthread_mutex_t *first, pthread_mutex_t *sec, pthread_mutex_t *third, pthread_mutex_t *forth)
{
	if(first != NULL)
		pthread_mutex_unlock(first);
	if(sec != NULL)
		pthread_mutex_unlock(sec);
	if(third != NULL)
		pthread_mutex_unlock(third);
	if(forth != NULL)
		pthread_mutex_unlock(forth);
}

int eat_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->safe_lock);
	philo->last_meal = calculate_timestep(philo->data);
	pthread_mutex_unlock(&philo->safe_lock);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		unlock_mutexes(&philo->data->fork[philo->left_fork], &philo->data->fork[philo->right_fork], &philo->data->print_mutex, NULL);
		return 1 ;
	}
	print_str(calculate_timestep(philo->data), philo->id, "is eating");
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->safe_lock);
	if(philo->data->user_args->eat_count != -1)
		philo->eat_count += 1;
	pthread_mutex_unlock(&philo->safe_lock);
	if(ft_usleep(philo->data->user_args->time_to_eat, philo))
	{
		unlock_mutexes(&philo->data->fork[philo->left_fork], &philo->data->fork[philo->right_fork], NULL, NULL);
		return 1;
	}
	unlock_mutexes(&philo->data->fork[philo->left_fork], &philo->data->fork[philo->right_fork], NULL, NULL);
	return 0;
}

static void init_fork_variable(long long *first_fork, long long *sec_fork, t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		(*first_fork) = philo->left_fork;
		(*sec_fork) = philo->right_fork;
		usleep(2000);
	}
	else
	{
		(*first_fork) = philo->right_fork;
		(*sec_fork) = philo->left_fork;
	}
}

int take_fork(t_philo *philo)
{
	long long first_fork;
	long long sec_fork;

	init_fork_variable(&first_fork, &sec_fork, philo);
	pthread_mutex_lock(&philo->data->fork[first_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		unlock_mutexes(&philo->data->fork[first_fork], NULL, &philo->data->print_mutex, NULL);
		return 1;
	}
	print_str(calculate_timestep(philo->data), philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_mutex);
	if(one_philo_handle(philo))
		return 1;
	pthread_mutex_lock(&philo->data->fork[sec_fork]);
	pthread_mutex_lock(&philo->data->print_mutex);
	if (anyone_dead(philo))
	{
		unlock_mutexes(&philo->data->fork[first_fork], &philo->data->fork[sec_fork], &philo->data->print_mutex, NULL);
		return 1;
	}
	print_str(calculate_timestep(philo->data), philo->id, "has taken a fork");
	pthread_mutex_unlock(&philo->data->print_mutex);
	return 0;
}

void *routuine(void *arg)
{
	t_philo *philo;

	philo = ((t_philo*)arg);
	if(((t_philo*)arg)->id % 2 != 0)
		usleep(2000);
	while(1)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		if (anyone_dead(philo))
		{
			pthread_mutex_unlock(&philo->data->print_mutex);
			break ;
		}
		print_str(calculate_timestep(philo->data), philo->id, "is thinking");
		pthread_mutex_unlock(&philo->data->print_mutex);
		if (take_fork(philo) == 1)
			break ;
		if (eat_meal(philo))
			break ;
		if (sleep_philo(philo))
			break ;
	}
	return NULL;
}

void create_philo(t_global_data *global_data)
{
    int i;

    i = 0;
    while(i < global_data->user_args->number_of_philo)
    {
        pthread_create(&global_data->philo_id_numbers[i], NULL, routuine, &global_data->philos[i]);
        i++;
    }
}
