# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/11 21:31:15 by ibaali            #+#    #+#              #
#    Updated: 2020/03/20 18:25:48 by ibaali           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang

#FLAGS = -Wextra -Wall -Werror -g
FLAGS =

SRC = 	ft_atoi.c 				\
		ft_itoa.c				\
		ft_putstr_fd.c			\
		ft_strcat.c				\
		helped.c				\
		philo_three.c			\
		process_manipulation.c

NAME = philo_three

LIBRARY = -pthread

all: $(NAME)

# you need to remove libft.a
$(NAME) :
	@$(CC) $(FLAGS) $(SRC) libft.a $(LIBRARY) -o $(NAME)

clean:
	@rm -rf $(NAME)

fclean: clean

re: fclean all

.PHONY: re all fclean clean


