/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:09:07 by ibaali1           #+#    #+#             */
/*   Updated: 2020/03/20 13:09:22 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	init_philosopheres(int argc, char **argv, t_philo_args *args)
{
	args->nb_of_philo = ft_atoi2(argv[1]);
	args->time_to_die = ft_atoi2(argv[2]);
	args->time_to_eat = ft_atoi2(argv[3]);
	args->time_to_sleep = ft_atoi2(argv[4]);
	args->nb_must_eat = (argc == 6) ? ft_atoi2(argv[5]) : 0;
}

int		open_eat_semaphores(t_philo_args args, t_philo_sem **sem)
{
	int		i;
	char	*str;
	char	*number;

	if (!(str = malloc(4096)))
		return (-1);
	str[0] = 0;
	i = -1;
	while (++i < args.nb_of_philo)
	{
		ft_strcat(str, SEM_EAT_NAME);
		number = ft_itoa2((uint64_t)i);
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

int		init_philo_sem(t_philo_sem *sem, t_philo_args args)
{
	if (!(sem->eat_sem = (sem_t**)malloc(
								sizeof(sem_t*) * args.nb_of_philo)))
		return (-1);
	sem_unlink(SEM_FORK_NAME);
	if ((sem->forks_sem = sem_open(SEM_FORK_NAME,
	O_CREAT, 0777, args.nb_of_philo)) == SEM_FAILED)
		return (-1);
	if (open_eat_semaphores(args, &sem))
		return (-1);
	sem_unlink(SEM_PRINT_NAME);
	if ((sem->print_sem = sem_open(SEM_PRINT_NAME,
	O_CREAT, 0777, 1)) == SEM_FAILED)
		return (-1);
	return (0);
}

int		main(int argc, char **argv)
{
	t_philo_args	args;
	t_philo_sem	sem;

	if (argc != 6 && argc != 5)
	{
		ft_putstr_fd2("Invalid Number of Arguments..!", 1);
		return (-1);
	}
	g_time = get_time_in_milisecond();
	init_philosopheres(argc, argv, &args);
	if (init_philo_sem(&sem, args))
	{
		ft_putstr_fd2("Sem Creation Error...!", 1);
		return (-1);
	}
	if (create_threads(&args, &sem))
	{
		ft_putstr_fd2("Thread Creation Error...!", 1);
		return (-1);
	}
	return (0);
}
