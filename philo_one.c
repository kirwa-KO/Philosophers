/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali1 <ibaali1@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 20:09:43 by ibaali1           #+#    #+#             */
/*   Updated: 2020/03/13 20:22:46 by ibaali1          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_data(int argc, char **argv)
{
	number_of_philosophers = ft_atoi(argv[1]);
	time_to_die = ft_atoi(argv[2]);
	time_to_eat = ft_atoi(argv[3]);
	time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		number_of_times_each_philosopher_must_eat = ft_atoi(argv[6]);
	philo_thread = ()
}

int		main(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (-1);
	init_data(argc, argv);
}
