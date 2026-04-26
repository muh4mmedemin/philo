# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: muayna <muayna@student.42istanbul.com.t    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/26 16:11:09 by muayna            #+#    #+#              #
#    Updated: 2026/04/26 16:13:47 by muayna           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRCS = sources/init.c sources/main.c sources/monitor.c sources/routine.c sources/utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
#CFLAGS = -Wall -Wextra -Werror
ARFLAGS = -rcs
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) 

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)


re: fclean all

.PHONY: all clean fclean re