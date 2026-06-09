# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/26 16:11:09 by muayna            #+#    #+#              #
#    Updated: 2026/06/09 22:34:54 by muayna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = sources/init.c sources/main.c sources/monitor.c sources/routine.c sources/utils.c sources/init_philo.c sources/routine2.c

OBJS = $(SRCS:.c=.o)
GB = libs/garbage_collector
GB_LIB = $(GB)/libgb.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -Ilibs/garbage_collector #-fsanitize=thread -g
RM = rm -rf

all: $(GB_LIB) $(NAME)

$(NAME): $(OBJS) $(GB_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GB_LIB) -lpthread

$(GB_LIB):
	$(MAKE) -C $(GB)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(GB) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(GB) fclean

re: fclean all

.PHONY: all clean fclean re
