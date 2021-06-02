/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 10:27:25 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/01 11:14:47 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

static	void	init_philosopheres(int argc, char **argv, t_philos_args *args)
{
	args->nb_of_philos = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->nb_must_eat = ft_atoi(argv[5]);
	else
		args->nb_must_eat = -1;
}

static	int		open_eat_semaphores(t_philos_args args, t_philos_sem **sem)
{
	int		i;
	char	*str;
	char	*number;

	if (!(str = malloc(BUFFER_SIZE)))
		return (-1);
	str[0] = 0;
	i = -1;
	while (++i < args.nb_of_philos)
	{
		ft_strcat(str, SEM_EAT_NAME);
		number = ft_itoa((uint64_t)i);
		ft_strcat(str, number);
		sem_unlink(str);
		if (((*sem)->eat_sem[i] = sem_open(str, O_CREAT, 0777, 1)) == SEM_FAILED)
			return (-1);
		str[0] = 0;
		free(number);
	}
	free(str);
	return (0);
}

static	int		init_philo_sem(t_philos_sem *sem, t_philos_args args)
{
	if (!(sem->eat_sem = (sem_t**)malloc(sizeof(sem_t*) * args.nb_of_philos)))
		return (-1);
	sem_unlink(SEM_FORK_NAME);
	if ((sem->forks_sem = sem_open(SEM_FORK_NAME, O_CREAT, 0777, args.nb_of_philos)) == SEM_FAILED)
		return (-1);
	if (open_eat_semaphores(args, &sem))
		return (-1);
	sem_unlink(SEM_PRINT_NAME);
	if ((sem->print_sem = sem_open(SEM_PRINT_NAME, O_CREAT, 0777, 1)) == SEM_FAILED)
		return (-1);
	sem_unlink(SEM_DOOR_NAME);
	if ((sem->door = sem_open(SEM_DOOR_NAME, O_CREAT, 0777, 1)) == SEM_FAILED)
		return (-1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_philos_args		args;
	t_philos_sem		sem;

	if (argc != 6 && argc != 5)
	{
		put_str("\033[0;31mInvalid Number of Arguments..!\033[0m\n");
		return (-1);
	}
	init_philosopheres(argc, argv, &args);
	if (init_philo_sem(&sem, args))
	{
		put_str("\033[0;31mMalloc Error...!\033[0m\n");
		return (-1);
	}
	if (create_threads(&args, &sem))
	{
		put_str("\033[0;31mThread Creation Error...!\033[0m");
		return (-1);
	}
	return (0);
}