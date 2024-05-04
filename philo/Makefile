# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: boel-bou <boel-bou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/22 21:54:59 by boel-bou          #+#    #+#              #
#    Updated: 2024/04/22 22:11:34 by boel-bou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c actions.c check.c destroy.c thread_function.c utils.c

OBJS = $(SRCS:.c=.o)

NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g3

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
