/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ibaali1 <ibaali1@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 11:09:07 by ibaali1           #+#    #+#             */
/*   Updated: 2020/03/14 13:38:35 by ibaali1          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	init_philosopheres(int argc, char **argv, int nb_philo)
{
	int		i;

	i = 0;
	g_thread_id = (pthread_t*)malloc(sizeof(pthread_t) * nb_philo);
	g_die_thread_id = (pthread_t*)malloc(sizeof(pthread_t) * nb_philo);
	g_forks = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * nb_philo);
	while (i < nb_philo)
	{
		g_philo_one[i].number_of_philosophers = ft_atoi(argv[1]);
		g_philo_one[i].time_to_die = ft_atoi(argv[2]);
		g_philo_one[i].time_to_eat = ft_atoi(argv[3]);
		g_philo_one[i].tim_to_sleep = ft_atoi(argv[4]);
		g_philo_one[i].left_fork = MIN(i, i + 1);
		g_philo_one[i].right_fork = MAX(i, i + 1);
		g_philo_one[i].nb_eat = 0;
		g_philo_one[i].nb_philo = i;
		if (argc == 6)
			g_philo_one[i].number_of_times_each_philosopher_must_eat =
			ft_atoi(argv[5]);
		i++;
	}
}

int		main(int argc, char **argv)
{
	int		i;
	int		nb_philo;

	if (argc != 6 && argc != 5)
		return (-1);
	nb_philo = ft_atoi(argv[1]);
	g_philo_one = (t_philo*)malloc(sizeof(t_philo) * nb_philo);
	init_philosopheres(argc, argv, nb_philo);
	i = 0;
	while (i++ < nb_philo)
		pthread_mutex_init(&(g_forks[i - 1]), NULL);
	pthread_mutex_init(&g_message, NULL);
	i = 0;
	while (i++ < nb_philo)
		pthread_create(&(g_thread_id[i - 1]), NULL, (void*)philosophere,
		&(g_philo_one[i - 1]));
	i = 0;
	while (i++ < nb_philo)
		pthread_create(&(g_die_thread_id[i - 1]), NULL, (void*)die,
		&(g_philo_one[i - 1]));
	i = 0;
	while (i++ < nb_philo)
		pthread_join(g_thread_id[i - 1], NULL);
	i = 0;
	while (i++ < nb_philo)
		pthread_join(g_thread_id[i - 1], NULL);
	i = 0;
	while (i++ < nb_philo)
		pthread_mutex_destroy(&(g_forks[i - 1]));
	pthread_mutex_destroy(&g_message);
}

void	*philosophere(void *parametre)
{
	t_philo		*philo;

	philo = parametre;
	while (1)
	{
		msg_print((*philo).nb_philo, THINKING);
		pthread_mutex_lock(&(g_forks[(*philo).left_fork]));
		msg_print((*philo).nb_philo, FORK);
		pthread_mutex_lock(&(g_forks[(*philo).right_fork]));
		msg_print((*philo).nb_philo, FORK);
		(*philo).state = EATING;
		msg_print((*philo).nb_philo, EATING);
		(*philo).last_eat = get_time_in_milisecond();
		(*philo).nb_eat += 1;
		usleep((*philo).time_to_eat * 1000);
		msg_print((*philo).nb_philo, SLEEPING);
		(*philo).state = SLEEPING;
		usleep((*philo).tim_to_sleep * 1000);
		(*philo).state = THINKING;
	}
	return (NULL);
}

void	*die(void *parametre)
{
	t_philo		*philo;

	philo = parametre;
	while (1)
	{
		if (((*philo).last_eat + (*philo).time_to_die) >
		get_time_in_milisecond() && (*philo).state != EATING)
		{
			msg_print((*philo).nb_philo, DIE);
			exit(1);
		}
	}
}
