# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/03/20 13:27:44 by ibaali            #+#    #+#              #
#    Updated: 2021/06/02 19:00:25 by ibaali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

FLAGS = -Wextra -Wall -Werror

SRC = 	main.c							\
		helper.c						\
		ft_strcat_and_sleep.c			\
		free_all_and_print_msgs.c		\
		thread_manipulation.c			\
		lock_unlock_semaphors.c			\
		control_number_of_eats.c

NAME = philo_two

LIBRARY = -pthread

all: $(NAME)

$(NAME) : $(SRC)
	@#$(CC) $(FLAGS) $(SRC) $(LIBRARY) -o $(NAME)
	@$(CC) $(SRC) $(LIBRARY) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: re all fclean clean


