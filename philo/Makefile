# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/26 16:11:09 by muayna            #+#    #+#              #
#    Updated: 2026/04/26 16:51:33 by muayna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = sources/init.c sources/main.c sources/monitor.c sources/routine.c sources/utils.c

OBJS = $(SRCS:.c=.o)
CC = -Wall -Wextra -Werror -includes 
GB = libs/garbage_collector
GB_LIB = $(GB)/libgb.a

CC = cc
CFLAGS = -I$(CC) -I$(GB)
RM = rm -rf

all: $(GB_LIB) $(NAME)

$(NAME): $(OBJS) $(GB_LIB)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(GB_LIB)

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
