/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 16:25:03 by muayna            #+#    #+#             */
/*   Updated: 2026/07/01 11:22:18 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	check_eat_count_for_norm(pthread_mutex_t *philo_safe_lock
			, long long *b)
{
	pthread_mutex_unlock(philo_safe_lock);
	(*b)++;
}

static void	check_eat_count(t_global_data **data)
{
	long long	b;

	if ((*data)->user_args->eat_count != -1 && (*data)->user_args->number_of_philo != 1)
	{
		b = 0;
		while (b <= ((*data)->user_args->number_of_philo - 1))
		{
			if (b == (*data)->user_args->number_of_philo - 1)
			{
				pthread_mutex_lock(&(*data)->dead_mutex);
				(*data)->is_dead = 1;
				pthread_mutex_unlock(&(*data)->dead_mutex);
				break ;
			}
			pthread_mutex_lock(&(*data)->philos[b].safe_lock);
			if ((*data)->philos[b].eat_count >= (*data)->user_args->eat_count)
				check_eat_count_for_norm(&(*data)->philos[b].safe_lock, &b);
			else
			{
				pthread_mutex_unlock(&(*data)->philos[b].safe_lock);
				break ;
			}
		}
	}
}

static int	opearate_philo_dead(t_global_data **data,
		unsigned long long kill_time, unsigned long long i)
{
	unsigned long long	s;
	unsigned long long	test;
	unsigned long long	last_meal;

	s = 0;
	pthread_mutex_lock(&(*data)->philos[i].safe_lock);
	last_meal = (*data)->philos[i].last_meal;
	pthread_mutex_unlock(&(*data)->philos[i].safe_lock);
	test = calculate_timestep((*data));
	s = test - last_meal;
	if (s > kill_time)
	{
		pthread_mutex_lock(&(*data)->dead_mutex);
		(*data)->is_dead = 1;
		pthread_mutex_unlock(&(*data)->dead_mutex);
		pthread_mutex_lock(&(*data)->print_mutex);
		print_str(calculate_timestep((*data)), i, "died");
		pthread_mutex_unlock(&(*data)->print_mutex);
		return (1);
	}
	return (0);
}

void	*check_philo_health(void *arg)
{
	long long		i;
	long long		kill_time;
	t_global_data	*data;

	i = 0;
	data = (t_global_data *)arg;
	kill_time = data->user_args->time_to_die;
	while (anyone_dead(&data->philos[i]) != 1)
	{
		/* ONEMLI DUZELTME:
		** check_eat_count() tum philolari (0..N-1) tek tek safe_lock
		** ile kilitleyip O(N) tarama yapiyor. Eskiden bu fonksiyon
		** monitor dongusunun HER adiminda cagriliyordu (yani philo
		** index'i 1 arttikca tekrar tekrar), bu da tam bir monitor
		** turunda O(N*N) mutex lock/unlock demekti. Buyuk N'lerde
		** (orn. 198-199 philo) bu, saniyede on binlerce gereksiz
		** kilitlemeye yol aciyor, bu da gercek philo thread'lerinin
		** fork/print_mutex/safe_lock alma suresini geciktiriyor ve
		** zamaninda yiyen bir philo bile time_to_die siniri asilmis
		** gibi yanlislikla "died" olarak isaretlenebiliyordu.
		**
		** Duzeltme: check_eat_count() sadece tam bir tur tamamlanip
		** basa donuldugunde (i == 0) cagriliyor. Boylece is O(N)
		** yerine O(N) kaliyor ama artik dongu basina bir kere,
		** N kat daha az kilit trafigi olusuyor. */
		if (i == 0)
			check_eat_count(&data);
		if (anyone_dead(&data->philos[i]))
			break ;
		if (opearate_philo_dead(&data, kill_time, i))
			break ;
		if ((data->user_args->number_of_philo - 1) == i)
			i = 0;
		else
			i++;
	}
	return (NULL);
}