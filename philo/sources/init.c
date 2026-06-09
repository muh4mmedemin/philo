/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:29:50 by muayna            #+#    #+#             */
/*   Updated: 2026/06/09 22:04:07 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	isbiggerint(char **argv)
{
	unsigned long	i;

	i = 1;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) > 10)
			exit_program("Max Int Value");
		else if (ft_atoi(argv[i]) > 2147483647)
			exit_program("Max Int Value");
		else if (ft_atoi(argv[i]) == 0)
			exit_program("You can't just type ZERO!!! FİX IN NOW!!");
		i++;
	}
}

static void	check_all_digit(char **argv, int argc)
{
	unsigned int	i;
	unsigned int	a;

	a = 1;
	i = 0;
	while (a != (unsigned int)argc)
	{
		i = 0;
		while (argv[a][i])
		{
			if (!ft_isdigit(argv[a][i]))
				exit_program("Just type number");
			i++;
		}
		a++;
	}
}

static void	check_error(char **argv, int argc)
{
	if (argc != 5 && argc != 6)
		exit_program("Missing or excessive values ​​were entered.");
	check_all_digit(argv, argc);
	isbiggerint(argv);
}

t_args	*init_args(char **argv, int argc)
{
	t_args	*user_input_list;

	user_input_list = ft_malloc((sizeof(t_args)), 0);
	if (user_input_list == NULL)
		exit_program("MALLOC ERROR!!!!");
	check_error(argv, argc);
	user_input_list->number_of_philo = ft_atoi(argv[1]);
	user_input_list->time_to_die = ft_atoi(argv[2]);
	user_input_list->time_to_eat = ft_atoi(argv[3]);
	user_input_list->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		user_input_list->eat_count = ft_atoi(argv[5]);
	else
		user_input_list->eat_count = -1;
	return (user_input_list);
}
