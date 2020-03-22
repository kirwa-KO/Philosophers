/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 20:46:03 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/22 15:33:10 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void	*philosophere(void	*param)
{
	t_philo_two	*philo;

	philo = (t_philo_two*)param;
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

void	*die(void *param)
{
	t_philo_two		*philo;
	uint64_t		time;

	philo = (t_philo_two*)param;
	while (1)
	{
		sem_wait(philo->sem->eat_sem[philo->nb_philo]);
		time = get_time_in_milisecond();
		if (time - philo->last_eat > philo->args->time_to_die +
		philo->args->time_to_sleep
			&& philo->nb_eat >= philo->args->nb_must_eat)
			msg_print(philo, DIE);
		sem_post(philo->sem->eat_sem[philo->nb_philo]);
	}
	return (NULL);
}

int		join_thread_and_destroy_sem(t_philo_two *philo)
{
	int		i;

	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_join(philo[i].die, NULL))
			return (-1);
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_join(philo[i].life, NULL))
			return (-1);
	if (sem_close(philo->sem->forks_sem))
			return (-1);
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (sem_close(philo->sem->eat_sem[i]))
			return (-1);
	if (sem_close(philo->sem->print_sem))
		return (-1);
	return (0);
}

int		create_threads(t_philo_args *args, t_philo_sem *sem)
{
	t_philo_two		*philo;
	int				i;

	if (!(philo = (t_philo_two*)malloc(sizeof(t_philo_two) * args->nb_of_philo)))
		return (-1);
	i = -1;
	while (++i < args->nb_of_philo)
	{
		philo[i] = (t_philo_two) { .args = args, .sem = sem,
		.last_eat = get_time_in_milisecond(), .nb_eat = 0, .nb_philo = i };
		if (pthread_create(&(philo[i].life), NULL, philosophere, &philo[i]))
			return (-1);
	}
	i = -1;
	usleep(philo->args->time_to_eat * 1000);
	while (++i < args->nb_of_philo)
	{
		if (pthread_create(&(philo[i].die), NULL, die, &philo[i]))
			return (-1);
	}
	if (join_thread_and_destroy_sem(philo))
		return (-1);
	return (0);
}
