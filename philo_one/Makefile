# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/30 12:13:31 by ibaali            #+#    #+#              #
#    Updated: 2021/06/03 06:56:00 by ibaali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wextra -Wall -Werror

SRC = 	main.c						\
		helper.c					\
		free_all_and_print_msgs.c	\
		lock_unlock_mutexes.c		\
		threads_manupilation.c

NAME =	philo_one

LIBRARY = -pthread

all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(SRC) $(LIBRARY) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: re all fclean clean

