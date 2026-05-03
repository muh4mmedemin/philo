/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 13:30:07 by muayna            #+#    #+#             */
/*   Updated: 2026/05/03 16:22:20 by muayna           ###   ########.fr       */
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

void *print_test(void *arg)
{
    printf("Hi \n");
}

int main(int argc, char **argv)
{
    pthread_t thread;
    
    pthread_create(&thread, NULL, print_test, NULL);
    printf("Main\n");
    pthread_join(thread, NULL);
}