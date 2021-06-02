/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 14:23:44 by ibaali            #+#    #+#             */
/*   Updated: 2021/06/02 11:34:57 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_theree.h"

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

static	int	open_eat_semaphores(t_philos_args args, t_philos_sem **sem)
{
	int		i;
	char	*str;
	char	*number;

	str = malloc(BUFFER_SIZE);
	if (!(str))
		return (-1);
	str[0] = 0;
	i = -1;
	while (++i < args.nb_of_philos)
	{
		ft_strcat(str, SEM_EAT_NAME);
		number = ft_itoa((uint64_t)i);
		ft_strcat(str, number);
		sem_unlink(str);
		(*sem)->eat_sem[i] = sem_open(str, O_CREAT, 0777, 1);
		if (((*sem)->eat_sem[i]) == SEM_FAILED)
			return (-1);
		str[0] = 0;
		free(number);
	}
	free(str);
	return (0);
}

static int	init_philo_sem(t_philos_sem *sem, t_philos_args args)
{
	sem->eat_sem = (sem_t **)malloc(sizeof(sem_t *) * args.nb_of_philos);
	if (!(sem->eat_sem))
		return (-1);
	sem_unlink(SEM_FORK_NAME);
	sem->forks_sem = sem_open(SEM_FORK_NAME, O_CREAT, 0777, args.nb_of_philos);
	if ((sem->forks_sem) == SEM_FAILED)
		return (-1);
	if (open_eat_semaphores(args, &sem))
		return (-1);
	sem_unlink(SEM_PRINT_NAME);
	sem->print_sem = sem_open(SEM_PRINT_NAME, O_CREAT, 0777, 1);
	if ((sem->print_sem) == SEM_FAILED)
		return (-1);
	sem_unlink(SEM_DOOR_NAME);
	sem->door = sem_open(SEM_DOOR_NAME, O_CREAT, 0777, 1);
	if ((sem->door) == SEM_FAILED)
		return (-1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philos_args		args;
	t_philos_sem		sem;

	if (argc != 6 && argc != 5)
	{
		put_str("\033[1;31mInvalid Number of Arguments..!\033[0m\n");
		return (-1);
	}
	init_philosopheres(argc, argv, &args);
	if (init_philo_sem(&sem, args))
	{
		put_str("\033[1;31mMalloc Error...!\033[0m\n");
		return (-1);
	}
	if (create_process(&args, &sem))
	{
		put_str("\033[1;31mProccess Creation Error...!\033[0m");
		return (-1);
	}
	return (0);
}
