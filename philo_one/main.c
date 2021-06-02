/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 12:13:35 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 18:22:08 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

/*
 ** initialize all philosophers informtion
 ** from argv and argc
*/
static	int	init_philosopheres(int argc, char **argv, t_philos_args *args)
{
	args->nb_of_philos = ft_atoi(argv[1]);
	if (args->nb_of_philos <= 0)
		return (-1);
	args->time_to_die = ft_atoi(argv[2]);
	if (args->time_to_die <= 0)
		return (-1);
	args->time_to_eat = ft_atoi(argv[3]);
	if (args->time_to_eat <= 0)
		return (-1);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (args->time_to_sleep <= 0)
		return (-1);
	if (argc == 6)
	{
		args->nb_must_eat = ft_atoi(argv[5]);
		if (args->nb_must_eat <= 0)
			return -1;
	}
	else
		args->nb_must_eat = 0;
	return (0);
}

/*
 ** initialize and allocate the mutexes
*/
static	int	init_philo_mutex(t_philos_mutex *mutex, t_philos_args args)
{
	int		i;

	mutex->forks_mutex = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * args.nb_of_philos);
	if (!(mutex->forks_mutex))
		return (-1);
	mutex->eat_mutex = (pthread_mutex_t *)malloc(
			sizeof(pthread_mutex_t) * args.nb_of_philos);
	if (!(mutex->eat_mutex))
		return (-1);
	i = -1;
	while (++i < args.nb_of_philos)
		if (pthread_mutex_init(&(mutex->forks_mutex[i]), NULL))
			return (-1);
	i = -1;
	while (++i < args.nb_of_philos)
		if (pthread_mutex_init(&(mutex->eat_mutex[i]), NULL))
			return (-1);
	if (pthread_mutex_init(&(mutex->print_mutex), NULL))
		return (-1);
	if (pthread_mutex_init(&(mutex->door), NULL))
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos_args		args;
	t_philos_mutex		mutex;

	if (argc != 6 && argc != 5)
	{
		put_str("\033[1;31mInvalid Number of Arguments..!\033[0m\n");
		return (-1);
	}
	if (init_philosopheres(argc, argv, &args) == -1)
	{
		put_str("\033[1;31mInvalid Arguments..!\033[0m\n");
		return (-1);
	}
	if (init_philo_mutex(&mutex, args))
	{
		put_str("\033[0;31mMalloc Error...!\033[0m\n");
		return (-1);
	}
	if (create_threads(&args, &mutex))
	{
		put_str("\033[0;31mThread Creation Error...!\033[0m");
		return (-1);
	}
	return (0);
}
