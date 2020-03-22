/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali <ibaali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/19 20:46:03 by ibaali            #+#    #+#             */
/*   Updated: 2020/03/22 15:47:26 by ibaali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*philosophere(void	*param)
{
	t_philo_one	*philo;

	philo = (t_philo_one*)param;
	while (1)
	{
		msg_print(philo, THINKING);
		pthread_mutex_lock(&(philo->mutex->forks_mutex[philo->left_fork]));
		msg_print(philo, FORK);
		pthread_mutex_lock(&(philo->mutex->forks_mutex[philo->right_fork]));
		msg_print(philo, FORK);
		msg_print(philo, EATING);
		pthread_mutex_lock(&(philo->mutex->eat_mutex[philo->nb_philo]));
		philo->nb_eat += 1;
		philo->last_eat = get_time_in_milisecond();
		usleep(philo->args->time_to_eat * 1000);
		pthread_mutex_unlock(&(philo->mutex->forks_mutex[philo->right_fork]));
		pthread_mutex_unlock(&(philo->mutex->forks_mutex[philo->left_fork]));
		pthread_mutex_unlock(&(philo->mutex->eat_mutex[philo->nb_philo]));
		msg_print(philo, SLEEPING);
		usleep(philo->args->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*die(void *param)
{
	t_philo_one		*philo;
	uint64_t		time;

	philo = (t_philo_one*)param;
	while (1)
	{
		pthread_mutex_lock(&(philo->mutex->eat_mutex[philo->nb_philo]));
		time = get_time_in_milisecond();
		if (time - philo->last_eat > philo->args->time_to_die &&
		philo->nb_eat >= philo->args->nb_must_eat)
		{
			msg_print(philo, DIE);
		}
		pthread_mutex_unlock(&(philo->mutex->eat_mutex[philo->nb_philo]));
		usleep(8 * 1000);
	}
	return (NULL);
}

int		join_thread_and_destroy_mutex(t_philo_one *philo)
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
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_mutex_destroy(&(philo->mutex->forks_mutex[i])))
			return (-1);
	i = -1;
	while (++i < philo->args->nb_of_philo)
		if (pthread_mutex_destroy(&(philo->mutex->eat_mutex[i])))
			return (-1);
	if (pthread_mutex_destroy(&(philo->mutex->print_mutex)))
		return (-1);
	return (0);
}

int		create_threads(t_philo_args *args, t_philo_mutex *mutex)
{
	t_philo_one		*philo;
	int				i;

	if (!(philo = (t_philo_one*)malloc(sizeof(t_philo_one) * args->nb_of_philo)))
		return (-1);
	i = -1;
	while (++i < args->nb_of_philo)
	{
		philo[i] = (t_philo_one) { .args = args, .mutex = mutex,
		.last_eat = get_time_in_milisecond(),
		.left_fork = MIN(i, (i + 1) % args->nb_of_philo), .right_fork =
		MAX(i, (i + 1) % args->nb_of_philo), .nb_eat = 0, .nb_philo = i };
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
	if (join_thread_and_destroy_mutex(philo))
		return (-1);
	return (0);
}
