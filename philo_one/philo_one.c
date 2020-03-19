/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:09:07 by ibaali1           #+#    #+#             */
/*   Updated: 2020/03/19 21:05:23 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_philosopheres(int argc, char **argv, t_philo_args *args)
{
	args->nb_of_philo = ft_atoi2(argv[1]);
	args->time_to_die = ft_atoi2(argv[2]);
	args->time_to_eat = ft_atoi2(argv[3]);
	args->time_to_sleep = ft_atoi2(argv[4]);
	args->nb_must_eat = (argc == 6) ? ft_atoi2(argv[5]) : 0;
}

int		init_philo_mutex(t_philo_mutex *mutex, t_philo_args args)
{
	int		i;

	if (!(mutex->forks_mutex = (pthread_mutex_t*)malloc(
								sizeof(pthread_mutex_t) * args.nb_of_philo)))
		return (-1);
	if (!(mutex->eat_mutex = (pthread_mutex_t*)malloc(
								sizeof(pthread_mutex_t) * args.nb_of_philo)))
		return (-1);
	i = -1;
	while (++i < args.nb_of_philo)
		if (pthread_mutex_init(&(mutex->forks_mutex[i]), NULL))
			return (-1);
	i = -1;
	while (++i < args.nb_of_philo)
		if (pthread_mutex_init(&(mutex->eat_mutex[i]), NULL))
			return (-1);
	if (pthread_mutex_init(&(mutex->print_mutex), NULL))
		return (-1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_philo_args	args;
	t_philo_mutex	mutex;

	if (argc != 6 && argc != 5)
	{
		ft_putstr_fd2("Invalid Number of Arguments..!", 1);
		return (-1);
	}
	g_time = get_time_in_milisecond();
	init_philosopheres(argc, argv, &args);
	if (init_philo_mutex(&mutex, args))
	{
		ft_putstr_fd2("Malloc Error...!", 1);
		return (-1);
	}
	if (create_threads(&args, &mutex))
	{
		ft_putstr_fd2("Thread Creation Error...!", 1);
		return (-1);
	}
	return (0);
}
