/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:04:24 by muayna            #+#    #+#             */
/*   Updated: 2026/06/08 23:31:35 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "philo.h"
# include "../libs/garbage_collector/gb.h"

typedef struct s_philo t_philo;

long long   ft_atoi(const char *nptr);
int     ft_isdigit(int c);
size_t  ft_strlen(const char *s);
void print_str(unsigned long long time_step, long long philo_id, char *message);
int ft_usleep(unsigned long long sleep_time_ms, t_philo *philo);

#endif