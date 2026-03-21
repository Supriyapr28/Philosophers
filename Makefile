# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: spaipur- <<spaipur-@student.42.fr>>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/04 10:22:53 by spaipur-          #+#    #+#              #
#    Updated: 2026/03/21 18:57:22 by spaipur-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = main.c time.c utils.c init.c routine.c monitor.c status.c

cc = gcc
CFLAGS = -Wall -Wextra -Werror 
all: $(NAME)

$(NAME): $(SRCS)
	$(cc) $(CFLAGS) -o $(NAME) $(SRCS)

clean:
	rm -f $(NAME)

fclean: clean

re: fclean all

.PHONY: all clean fclean re