/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_gb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:00:14 by muayna            #+#    #+#             */
/*   Updated: 2026/04/26 16:29:11 by muayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef S_GB_H
# define S_GB_H

typedef struct s_gb
{
	void		*address_pointer;
	struct s_gb	*next;
}	t_gb;

typedef struct s_sort_gb
{
	void				*address_pointer;
	struct s_sort_gb	*next;
}	t_sort_gb;

#endif
