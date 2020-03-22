# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/20 13:28:05 by ibaali            #+#    #+#              #
#    Updated: 2020/03/20 13:28:30 by ibaali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wextra -Wall -Werror

SRC = 	ft_atoi.c 				\
		ft_itoa.c				\
		ft_putstr_fd.c			\
		ft_strcat.c				\
		helped.c				\
		philo_one.c				\
		thread_manipulation.c

NAME = philo_one

LIBRARY = -pthread

all: $(NAME)

$(NAME) :
	$(CC) $(FLAGS) $(SRC) $(LIBRARY) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: re all fclean clean

