/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_manipulation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 20:46:03 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/20 20:46:33 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	debug(t_philo_three *philo, char *str)
{
	sem_wait(philo->sem->print_sem);
	ft_printf("%s\n", str);
	sem_post(philo->sem->print_sem);
}

void	*die(void *param)
{
	t_philo_three	*philo;
	uint64_t		time;

	philo = (t_philo_three*)param;
	while (1)
	{
		sem_wait(philo->sem->eat_sem[philo->nb_philo]);
		time = get_time_in_milisecond();
		if (time - philo->last_eat > philo->args->time_to_die
			&& philo->nb_eat >= philo->args->nb_must_eat)
				msg_print(philo, DIE);
		debug(philo, "I am Here..!\n");
		sem_post(philo->sem->eat_sem[philo->nb_philo]);
		usleep(8 * 1000);
	}
	return (NULL);
}

void	*philosophere(t_philo_three *philo)
{
	pthread_t	monitor;

	if (pthread_create(&monitor, NULL, die, &(philo)))
	{
		debug(philo, "Problem is Here");
		return (NULL);
	}
	while (1)
	{
		msg_print(philo, THINKING);
		sem_wait(philo->sem->forks_sem);
		msg_print(philo, FORK);
		sem_wait(philo->sem->forks_sem);
		msg_print(philo, FORK);
		msg_print(philo, EATING);
		sem_wait(philo->sem->eat_sem[philo->nb_philo]);
		philo->nb_eat += 1;
		philo->last_eat = get_time_in_milisecond();
		usleep(philo->args->time_to_eat * 1000);
		sem_post(philo->sem->forks_sem);
		sem_post(philo->sem->forks_sem);
		sem_post(philo->sem->eat_sem[philo->nb_philo]);
		msg_print(philo, SLEEPING);
		usleep(philo->args->time_to_sleep * 1000);
	}
	return (NULL);
}

int		wait_child_process(t_philo_three *philo)
{
	int		i;

	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (waitpid(philo[i].pid, NULL, 1) == -1)
			return (write(1, "Waitpid Error..!\n", 17) * 0 - 1);
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if ((kill(philo[i].pid, SIGINT)) == -1)
			return (write(1, "kill Error..!\n", 17) * 0 - 1);
	free_all_and_exit(philo);
	exit (0);
}

int		create_process(t_philo_args *args, t_philo_sem *sem)
{
	t_philo_three	*philo;
	int				i;

	if (!(philo = (t_philo_three*)malloc(sizeof(t_philo_three) * args->nb_of_philo)))
		return (write(1, "Malloc Error..!\n", 14) * 0 - 1);
	i = -1;
	while (++i < args->nb_of_philo)
	{

		philo[i] = (t_philo_three) { .args = args, .sem = sem,
		.last_eat = get_time_in_milisecond(), .nb_eat = 0, .nb_philo = i };

		if ((philo[i].pid = fork()) == -1)
			return (write(1, "Fork Error..!\n", 14) * 0 - 1);

		else if (philo[i].pid == 0)
			philosophere(&(philo[i]));
		usleep(10);
	}
	return (0);
}
