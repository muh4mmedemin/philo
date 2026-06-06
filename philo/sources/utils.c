/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:04:13 by muayna            #+#    #+#             */
/*   Updated: 2026/06/06 11:27:52 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	if(s == NULL)
		return 0;
	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_atoi(const char *nptr)
{
	int		i;
	int		countnp;
	long	number;

	number = 0;
	countnp = 1;
	i = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
	{
		i++;
	}
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			countnp = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		number = number * 10 + (nptr[i] - '0');
		i++;
	}
	return (number * countnp);
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else
		return (0);
}

void write_str(char *str)
{
	if (str == NULL)
		return ;
	write(1, str, ft_strlen(str));
}