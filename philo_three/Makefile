# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 21:31:15 by ibaali            #+#    #+#              #
#    Updated: 2021/06/02 09:15:05 by ibaali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wextra -Wall -Werror

SRC = 	main.c						\
		helper.c					\
		process_manipulation.c		\
		ft_strcat_and_sleep.c		\
		free_all_and_exit.c			\
		lock_unlock_semaphors.c

NAME = philo_three

LIBRARY = -pthread

all: $(NAME)

$(NAME) : $(SRC)
	@$(CC) $(FLAGS) $(SRC) $(LIBRARY) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: re all fclean clean


